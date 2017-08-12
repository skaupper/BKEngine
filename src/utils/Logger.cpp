#include "utils/Logger.h"

using namespace bkengine;


Logger Logger::fatal;
Logger Logger::error;
Logger Logger::warning;
Logger Logger::info;
Logger Logger::debug;

Logger::StaticConstructor Logger::_;
std::mutex Logger::loggerMutex;
int Logger::logLevel = 4;
bool Logger::useColors;


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


int Logger::LoggerStreamBuf::sync()
{
    loggerMutex.lock();
    
    if (Logger::IsSet(logger->level)) {
        if (useColors) {
            switch (logger->level) {
                case LogLevel::FATAL:
                    output << RED;
                    break;
                    
                case LogLevel::ERROR:
                    output << MAG;
                    break;
                    
                case LogLevel::WARNING:
                    output << YEL;
                    break;
                    
                case LogLevel::INFO:
                    output << GRN;
                    break;
                    
                case LogLevel::DEBUG:
                    output << BLU;
                    break;
                    
                case LogLevel::NOTHING:
                default:
                    break;
            }
        }
        
        output << GetTimeString() << "[" << prefix << "] " << str();
        
        if (useColors) {
            output << NRM;
        }
        
        output << std::flush;
        str("");
    }
    
    loggerMutex.unlock();
    return 0;
}


Logger::StaticConstructor::StaticConstructor()
{
    Logger::fatal.SetInternalLevel(LogLevel::FATAL);
    Logger::error.SetInternalLevel(LogLevel::ERROR);
    Logger::warning.SetInternalLevel(LogLevel::WARNING);
    Logger::info.SetInternalLevel(LogLevel::INFO);
    Logger::debug.SetInternalLevel(LogLevel::DEBUG);
    Logger::logLevel = 31;
    Logger::useColors = true;
}


Logger::Logger() : Logger(LogLevel::NOTHING)
{
}

Logger::Logger(LogLevel level) : std::ostream(&buffer)
{
    SetInternalLevel(level);
    buffer.SetParentLogger(this);
}


void Logger::SetInternalLevel(LogLevel level)
{
    this->level = level;
    std::string prefix;
    
    switch (level) {
        case LogLevel::FATAL:
            prefix = "FATAL";
            break;
            
        case LogLevel::ERROR:
            prefix = "ERROR";
            break;
            
        case LogLevel::WARNING:
            prefix = "WARNING";
            break;
            
        case LogLevel::INFO:
            prefix = "INFO";
            break;
            
        case LogLevel::NOTHING:
        default:
            prefix = "NOTHING";
            break;
    }
    
    buffer.SetPrefix(prefix);
}


void Logger::SetLevel(LogLevel level)
{
    logLevel |= (int) level;
}

void Logger::UnsetLevel(LogLevel level)
{
    logLevel &= ~((int) level);
}

bool Logger::IsSet(LogLevel level)
{
    return (logLevel & ((int) level)) != (int) LogLevel::NOTHING;
}

void Logger::UseColors(bool colors)
{
    useColors = colors;
}