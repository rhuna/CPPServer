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


private:
    Logger() : log_file_("server.log", std::ios::app);
    std::ofstream log_file_;
    std::mutex mutex_;
};

#define LOG_DEBUG(msg) Logger::instance().log(Logger::Level::Debug, msg)
#define LOG_INFO(msg) Logger::instance().log(Logger::Level::Info, msg)


#endif // !LOGGER_H



