#include "logger.h"



Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::log(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::string levelStr;
    switch (level) {
    case Level::Debug: levelStr = "DEBUG"; break;
    case Level::Info: levelStr = "INFO"; break;
    case Level::Warning: levelStr = "WARN"; break;
    case Level::Error: levelStr = "ERROR"; break;
    }

    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);

    //log_file_ << std::put_time(std::localtime(&now_time), "%F %T")
    //    << " [" << levelStr << "] " << message << std::endl;
}

Logger::Logger() : log_file_("server.log", std::ios::app) {
	if (!log_file_.is_open()) {
		std::cerr << "Failed to open log file." << std::endl;
	}
    else {
        std::cout << "Log file opened successfully." << std::endl;
    }

};

void Logger::setLogFile(const std::string& filename) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (log_file_.is_open()) {
		log_file_.close();
	}
	log_file_.open(filename, std::ios::app);
	if (!log_file_.is_open()) {
		std::cerr << "Failed to open log file: " << filename << std::endl;
	}
	else {
		std::cout << "Log file set to: " << filename << std::endl;
	}
};
void Logger::setMinLevel(Level level) {
	std::lock_guard<std::mutex> lock(mutex_);
	min_level = level;
	std::cout << "Minimum log level set to: " << static_cast<int>(level) << std::endl;
};