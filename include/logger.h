#pragma once

#include <iostream>
#include <string>

namespace SubShift {

class Logger {
private:
    bool m_shouldLog = false;
public:
    Logger& instance() {
        static Logger INSTANCE;
        return INSTANCE;
    }

    void setupLogging(bool shouldLog) {
        m_shouldLog = shouldLog;
    }

    // TODO: Add more overloads to handle e.g. std::endl;
    friend Logger& operator<< (Logger& out, const std::string& value) {
        if (out.m_shouldLog) std::cout << value;
        return out;
    }
};

}

#define LOG SubShift::Logger().instance()