#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip> // for std::put_time


class Logger {
public:
    enum class Level { Debug, Info, Warning, Error };

    static Logger& instance();
    void log(Level level, const std::string& message);

    template<typename... Args>
    void log(Level level, const std::string& format, Args... args) {
        if (level < min_level) return;

       // std::string message = fmt::format(format, args...);
        // Actual logging implementation
    }

    void setLogFile(const std::string& filename);
    void setMinLevel(Level level);

private:

    Logger();
    std::ofstream log_file_;
    Level min_level = Level::Info;
    std::mutex mutex_;
};

#define LOG_DEBUG(msg) Logger::instance().log(Logger::Level::Debug, msg)
#define LOG_INFO(msg) Logger::instance().log(Logger::Level::Info, msg)


#endif // !LOGGER_H



