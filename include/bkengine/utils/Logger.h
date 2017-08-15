#ifndef BKENGINE_LOGGER_H
#define BKENGINE_LOGGER_H

#include <iomanip>
#include <iostream>
#include <mutex>

#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"


namespace bkengine
{
    enum class LogLevel
    {
        NOTHING = 0,
        DEBUG = 1,
        INFO = 2,
        WARNING = 4,
        ERROR = 8,
        FATAL = 16
    };

    class Logger : public std::ostream
    {
    private:
        class LoggerStreamBuf : public std::stringbuf
        {
            std::ostream &output;
            std::string prefix;
            Logger *logger;

        public:
            LoggerStreamBuf() : output(std::cout), prefix(""), logger(nullptr)
            {
            }

            void SetParentLogger(Logger *logger)
            {
                this->logger = logger;
            }

            void SetPrefix(const std::string &newPrefix)
            {
                prefix = newPrefix;
            }

            int sync() override;
        };

        struct StaticConstructor
        {
            StaticConstructor();
        };
        static StaticConstructor _;

        static bool useColors;
        static std::mutex loggerMutex;
        static int logLevel;

        LogLevel level;
        LoggerStreamBuf buffer;


        void SetInternalLevel(LogLevel level);

        explicit Logger();
        explicit Logger(LogLevel level);

    public:
        static void SetLevel(LogLevel level);
        static void UnsetLevel(LogLevel level);
        static bool IsSet(LogLevel level);
        static void UseColors(bool colors);

        static Logger fatal;
        static Logger error;
        static Logger warning;
        static Logger info;
        static Logger debug;
    };
}

#endif  // BKENGINE_LOGGER_H