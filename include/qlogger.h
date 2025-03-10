#ifndef QLOGGER_H
#define QLOGGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <mutex>

class QLogger {
public:

    static void Log(const std::string& message) {
        std::cout << message << std::endl;
    }

    template<typename... Args>
    static void Log(const std::string& format, Args... args) {
        std::ostringstream oss;
        Format(oss, format, args...);
        std::cout << oss.str() << std::endl;
    }

private:

    template<typename T, typename... Args>
    static void Format(std::ostringstream& oss, const std::string& format, T value, Args... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << value;
            Format(oss, format.substr(pos + 2), args...);
        } else {
            oss << format;
        }
    }

    static void Format(std::ostringstream& oss, const std::string& format) {
        oss << format;
    }
};

#define QLOG(format, ...) QLogger::Log(format, ##__VA_ARGS__)


#endif // QLOGGER_H