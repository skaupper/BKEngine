#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <time.h>
#include <sstream>

namespace bkengine
{
    enum class LogLevel : unsigned int {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4
    };

    class Logger
    {
        private:
            static LogLevel logLevel;
            static std::array<std::string, 5> logLevelStrings;
            static std::string file;
            static bool stdout;

        public:
            static void UseStdout(bool useStdout = true);
            static void UseFile(const std::string &path = "");

            static void SetLevel(unsigned int logLevel);
            static void SetLevel(const LogLevel &logLevel);

            static void LogDebug(const std::string &text);
            static void LogInfo(const std::string &text);
            static void LogWarning(const std::string &text);
            static void LogError(const std::string &text);
            static void LogCritical(const std::string &text);
            static void Log(const LogLevel &level, const std::string &text);
            static void Log(unsigned int level, const std::string &text);
    };
}

#endif
