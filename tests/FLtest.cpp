#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>
#include <iostream>

class MyAppWindow : public Fl_Window {
    Fl_Menu_Bar* menuBar;
    Fl_Text_Display* logDisplay;
    Fl_Text_Buffer* logBuffer;
    Fl_Round_Button* radio1;
    Fl_Round_Button* radio2;
    Fl_Round_Button* radio3;
    Fl_Button* runButton;

public:
    MyAppWindow(int w, int h, const char* title = nullptr) : Fl_Window(w, h, title) {
        // Menu bar no topo (posição 0,0 e largura da janela, altura ~25)
        menuBar = new Fl_Menu_Bar(0, 0, w, 25);

        // Adiciona itens ao menu
        menuBar->add("Arquivo/Novo", 0, menu_cb, this);
        menuBar->add("Arquivo/Abrir", 0, menu_cb, this);
        menuBar->add("Arquivo/Sair", 0, menu_cb, this);
        menuBar->add("Ajuda/Sobre", 0, menu_cb, this);

        // Criando área de log com barra de rolagem (debaixo da barra do menu)
        logDisplay = new Fl_Text_Display(20, 40, w - 40, 150);
        logBuffer = new Fl_Text_Buffer();
        logDisplay->buffer(logBuffer);

        // Radio buttons (grupo)
        int radioX = 20;
        int radioY = 200;
        int radioW = 150;
        int radioH = 30;

        radio1 = new Fl_Round_Button(radioX, radioY, radioW, radioH, "Opção 1");
        radio1->type(FL_RADIO_BUTTON);
        radio1->value(1); // seleciona padrão

        radio2 = new Fl_Round_Button(radioX, radioY + 40, radioW, radioH, "Opção 2");
        radio2->type(FL_RADIO_BUTTON);

        radio3 = new Fl_Round_Button(radioX, radioY + 80, radioW, radioH, "Opção 3");
        radio3->type(FL_RADIO_BUTTON);

        // Botão Run
        runButton = new Fl_Button(w - 100, radioY + 80, 80, 30, "Run");
        runButton->callback(run_cb, this);

        end();
    }

    static void menu_cb(Fl_Widget* w, void* data) {
        Fl_Menu_Bar* menu = (Fl_Menu_Bar*)w;
        const Fl_Menu_Item* m = menu->mvalue();
        if (!m) return;

        MyAppWindow* win = (MyAppWindow*)data;
        const char* label = m->label();

        if (strcmp(label, "Arquivo/Sair") == 0) {
            win->hide(); // Fecha janela
        } else {
            // Só adiciona log para mostrar qual menu foi clicado
            char buf[256];
            snprintf(buf, sizeof(buf), "Menu selecionado: %s\n", label);
            win->logBuffer->append(buf);
            win->logDisplay->scroll(win->logBuffer->length(), 0);
        }
    }

    static void run_cb(Fl_Widget* w, void* data) {
        MyAppWindow* win = (MyAppWindow*)data;
        win->run_action();
    }

    void run_action() {
        const char* selectedOption = nullptr;
        if (radio1->value()) selectedOption = "Opção 1";
        else if (radio2->value()) selectedOption = "Opção 2";
        else if (radio3->value()) selectedOption = "Opção 3";
        else selectedOption = "Nenhuma";

        static int count = 1;
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "[%d] Rodando com %s\n", count++, selectedOption);
        logBuffer->append(buffer);
        logDisplay->scroll(logBuffer->length(), 0);
    }
};

int main() {
    Fl::scheme("plastic"); // tema FLTK (opcional)
    MyAppWindow win(400, 300, "Exemplo FLTK com Menu, Log, Radio e Botão");
    win.show();
    return Fl::run();
}
