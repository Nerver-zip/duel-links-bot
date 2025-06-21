#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>
#include <thread>
#include <atomic>
#include <iostream>
#include <queue>
#include <mutex>

#include "Util.h"
#include "GameScreen.h"
#include "GateDuel.h"
#include "GateDuelRush.h"
#include "RaidDuel.h"
#include "GameException.h"
#include "LogStreamBuf.h"

class MyAppWindow : public Fl_Window {
    Fl_Menu_Bar* menuBar;
    Fl_Text_Display* logDisplay;
    Fl_Text_Buffer* logBuffer;
    Fl_Round_Button* radio1;
    Fl_Round_Button* radio2;
    Fl_Round_Button* radio3;
    Fl_Button* runButton;
    Fl_Button* stopButton;
    Fl_Button* clearButton; 

    GateDuel duel;
    GateDuelRush rushDuel;
    RaidDuel raid;

    std::atomic<bool> running;
    std::thread worker;

    Resolution selectedResolution = Resolution::_1280x720;
    float selectedZoom = 1.25f;

    std::mutex logMutex;
    std::queue<std::string> logQueue;

public:
    MyAppWindow(int w, int h, const char* title = nullptr)
        : Fl_Window(w, h, title)
    {
        running = false;

        menuBar = new Fl_Menu_Bar(0, 0, w, 25);
        menuBar->add("File/Exit", 0, menu_cb, this);
        menuBar->add("Options/Resolution/1280x720", 0, options_cb, this);
        menuBar->add("Options/Resolution/1600x900", 0, options_cb, this);
        menuBar->add("Options/Resolution/1920x1080", 0, options_cb, this);
        menuBar->add("Options/Zoom/1.00x", 0, options_cb, this);
        menuBar->add("Options/Zoom/1.25x", 0, options_cb, this);
        menuBar->add("Options/Zoom/1.50x", 0, options_cb, this);

        logDisplay = new Fl_Text_Display(20, 40, w - 40, 150);
        logBuffer = new Fl_Text_Buffer();
        logDisplay->buffer(logBuffer);

        int radioX = 20, radioY = 200, radioW = 150, radioH = 30;

        radio1 = new Fl_Round_Button(radioX, radioY, radioW, radioH, "Gate Duel (SPEED)");
        radio1->type(FL_RADIO_BUTTON);
        radio1->value(1);

        radio2 = new Fl_Round_Button(radioX, radioY + 40, radioW, radioH, "Gate Duel (RUSH)");
        radio2->type(FL_RADIO_BUTTON);

        radio3 = new Fl_Round_Button(radioX, radioY + 80, radioW, radioH, "Raid Duel");
        radio3->type(FL_RADIO_BUTTON);

        runButton = new Fl_Button(w - 280, radioY + 80, 80, 30, "Run");
        runButton->callback(run_cb, this);
            
        stopButton = new Fl_Button(w - 190, radioY + 80, 80, 30, "Stop");
        stopButton->callback(stop_cb, this);
            
        clearButton = new Fl_Button(w - 100, radioY + 80, 80, 30, "Clear");
        clearButton->callback(clear_log_cb, this);

        end();
    }

    ~MyAppWindow() {
        stop_worker();  
    }

    void hide() override {
        stop_worker(); 
        Fl_Window::hide();
    }

    static void menu_cb(Fl_Widget* w, void* data) {
        MyAppWindow* win = static_cast<MyAppWindow*>(data);
        win->hide();
    }

    static void run_cb(Fl_Widget* w, void* data) {
        MyAppWindow* win = (MyAppWindow*)data;
        win->start_worker();
    }

    static void stop_cb(Fl_Widget* w, void* data) {
        MyAppWindow* win = (MyAppWindow*)data;
        win->stop_worker();
    }

    static void clear_log_cb(Fl_Widget* w, void* data);

    static void options_cb(Fl_Widget* w, void* data) {
        MyAppWindow* win = (MyAppWindow*)data;
        Fl_Menu_Bar* menu = (Fl_Menu_Bar*)w;
        const Fl_Menu_Item* m = menu->mvalue();
        if (!m) return;

        const char* label = m->label();

        if (strcmp(label, "1280x720") == 0) {
            win->selectedResolution = Resolution::_1280x720;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Resolution set to 1280x720\n");
            }, win);
        } else if (strcmp(label, "1600x900") == 0) {
            win->selectedResolution = Resolution::_1600x900;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Resolution set to 1600x900\n");
            }, win);
        } else if (strcmp(label, "1920x1080") == 0) {
            win->selectedResolution = Resolution::_1920x1080;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Resolution set to 1920x1080\n");
            }, win);
        } else if (strcmp(label, "1.00x") == 0) {
            win->selectedZoom = 1.00f;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Zoom set to 1.00x\n");
            }, win);
        } else if (strcmp(label, "1.25x") == 0) {
            win->selectedZoom = 1.25f;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Zoom set to 1.25x\n");
            }, win);
        } else if (strcmp(label, "1.50x") == 0) {
            win->selectedZoom = 1.50f;
            Fl::awake([](void* d) {
                ((MyAppWindow*)d)->append_log("Zoom set to 1.50x\n");
            }, win);
        }
    }

    void start_worker() {
        if (running) {
            append_log("Already running.\n");
            return;
        }

        running = true;
        GameScreen::init(selectedResolution, selectedZoom);
        GameScreen::getInstance().resume();
        worker = std::thread([this]() {
        try {
            if (radio1->value()) {
                Fl::awake([](void* d) {
                    ((MyAppWindow*)d)->append_log("Starting Gate Duel (SPEED)...\n");
                }, this);
                while (running && GameScreen::getInstance().isRunning())
                    duel.run(10);
            } else if (radio2->value()) {
                Fl::awake([](void* d) {
                    ((MyAppWindow*)d)->append_log("Starting Gate Duel (RUSH)...\n");
                }, this);
                while (running && GameScreen::getInstance().isRunning())
                    rushDuel.run(10);
            } else if (radio3->value()) {
                Fl::awake([](void* d) {
                    ((MyAppWindow*)d)->append_log("Starting Raid Duel...\n");
                }, this);
                while (running && GameScreen::getInstance().isRunning())
                    raid.run(200000);
            } else {
                Fl::awake([](void* d) {
                    ((MyAppWindow*)d)->append_log("No mode selected!\n");
                }, this);
                running = false;
            }
        } 
        catch (const GameException& e) {
            Fl::awake([](void* data) {
                static_cast<MyAppWindow*>(data)->append_log("Exception occurred.\n");
            }, this);
        }
      });
    }

    void stop_worker() {
        if (running) {
            GameScreen::getInstance().stop();
            running = false;
            if (worker.joinable()) worker.join();
            append_log("Execution stopped.\n");
        } else {
            append_log("No execution is running.\n");
        }
    }

    static void process_log(void* data) {
        MyAppWindow* win = (MyAppWindow*)data;
        std::lock_guard<std::mutex> lock(win->logMutex);
        while (!win->logQueue.empty()) {
            win->logBuffer->append(win->logQueue.front().c_str());
            win->logQueue.pop();
        }
        win->logDisplay->scroll(win->logBuffer->length(), 0);
        win->logDisplay->redraw();
    }

    void append_log(const char* msg) {
        {
            std::lock_guard<std::mutex> lock(logMutex);
            logQueue.emplace(msg);
        }
        Fl::awake(process_log, this);
    }
};

void MyAppWindow::clear_log_cb(Fl_Widget* w, void* data) {
    MyAppWindow* win = static_cast<MyAppWindow*>(data);
    {
        std::lock_guard<std::mutex> lock(win->logMutex);
        while (!win->logQueue.empty()) win->logQueue.pop();
        win->logBuffer->remove(0, win->logBuffer->length());
    }
    win->logDisplay->scroll(0, 0);
    win->logDisplay->redraw();
}


int main() {
    Fl::lock();
    Fl::scheme("plastic");

    MyAppWindow win(400, 350, "Duel Bot");
    win.show();

    LogStreamBuf logBuf([&win](const std::string& msg) {
        win.append_log(msg.c_str());
    });
    std::cout.rdbuf(&logBuf);

    return Fl::run();
}
