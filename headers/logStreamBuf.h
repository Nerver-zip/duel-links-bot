#ifndef LOG_STREAM_BUF_H
#define LOG_STREAM_BUF_H

#include <streambuf>
#include <string>
#include <functional>

class LogStreamBuf : public std::streambuf {
public:
    using LogCallback = std::function<void(const std::string&)>;

    explicit LogStreamBuf(LogCallback callback);
    ~LogStreamBuf();

protected:
    int overflow(int c) override;
    int sync() override;

private:
    std::string buffer;
    LogCallback logCallback;
};

#endif
