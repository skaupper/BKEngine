#include "utils/Logger.h"

using namespace bkengine;


static std::string GetTimeString()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    int day = now->tm_mday;
    int hour = now->tm_hour;
    int minute = now->tm_min;
    int second = now->tm_sec;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day << "/"
       << std::setfill('0') << std::setw(2) << month << "/"
       << std::setfill('0') << std::setw(4) << year << " "
       << std::setfill('0') << std::setw(2) << hour << ":"
       << std::setfill('0') << std::setw(2) << minute << ":"
       << std::setfill('0') << std::setw(2) << second;
    return ss.str();
}

LogLevel Logger::logLevel = LogLevel::DEBUG;
std::array<std::string, 5> Logger::logLevelStrings = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
std::string Logger::file = "";
bool Logger::stdout = true;

void Logger::UseStdout(bool b)
{
    stdout = b;
}

void Logger::UseFile(const std::string &path)
{
    file = path;
}

void Logger::SetLevel(unsigned int logLevel)
{
    Logger::logLevel = (LogLevel) logLevel;
}

void Logger::SetLevel(const LogLevel &logLevel)
{
    Logger::logLevel = logLevel;
}

void Logger::LogDebug(const std::string &text)
{
    Log((int) LogLevel::DEBUG, text);
}

void Logger::LogInfo(const std::string &text)
{
    Log((int) LogLevel::INFO, text);
}

void Logger::LogWarning(const std::string &text)
{
    Log((int) LogLevel::WARNING, text);
}

void Logger::LogError(const std::string &text)
{
    Log((int) LogLevel::ERROR, text);
}

void Logger::LogCritical(const std::string &text)
{
    Log((int) LogLevel::CRITICAL, text);
}

void Logger::Log(const LogLevel &level, const std::string &text)
{
    Log((int) level, text);
}

void Logger::Log(unsigned int level, const std::string &text)
{
    if (level < (unsigned int) logLevel) {
        return;
    }

    static std::mutex mutex;
    mutex.lock();
    std::stringstream textstream;
    textstream << GetTimeString() << " [" << logLevelStrings[level]  << "] " <<
               text << std::endl;

    if (!file.empty()) {
        std::ofstream stream;
        stream.open(file, std::ofstream::out | std::ofstream::app);
        stream << textstream.str();
        stream.close();
    }

    if (stdout) {
        std::cout << textstream.str();
    }

    mutex.unlock();
}
