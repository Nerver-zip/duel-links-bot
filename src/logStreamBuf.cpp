#include "LogStreamBuf.h"

LogStreamBuf::LogStreamBuf(LogCallback callback)
    : logCallback(std::move(callback)) {
}

LogStreamBuf::~LogStreamBuf() {
    sync();
}

int LogStreamBuf::overflow(int c) {
    if (c == traits_type::eof()) return traits_type::not_eof(c);

    if (c == '\n') {
        sync();
    } else {
        buffer += static_cast<char>(c);
    }

    return c;
}

int LogStreamBuf::sync() {
    if (!buffer.empty()) {
        logCallback(buffer + '\n');
        buffer.clear();
    }
    return 0;
}
