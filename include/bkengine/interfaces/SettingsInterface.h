#ifndef BKENGINE_SETTINGSINTERFACE_H
#define BKENGINE_SETTINGSINTERFACE_H

#include <string>


namespace bkengine
{
    class SettingsInterface
    {
        public:
            virtual void init() = 0;
            virtual void loadFromFile(const std::string &filename) = 0;
            virtual void saveToFile(const std::string &filename) const = 0;
            virtual bool hasValue(const std::string &key) const = 0;
            virtual std::string get(const std::string &key) const = 0;
            virtual std::string remove(const std::string &key) = 0;
            virtual void create(const std::string &key, const std::string &value) = 0;
            virtual void change(const std::string &key, const std::string &newvalue) = 0;

            virtual uint32_t count() const = 0;
    };
}

#endif
