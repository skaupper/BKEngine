#ifndef BKENGINE_INISETTINGSINTERFACE_H
#define BKENGINE_INISETTINGSINTERFACE_H

#include <fstream>
#include <map>

#include "interfaces/SettingsInterface.h"
#include "utils/Logger.h"


namespace bkengine
{
    class INISettingsInterface : public SettingsInterface
    {
        public:
            virtual void init() override;
            virtual void loadFromFile(const std::string &filename) override;
            virtual void saveToFile(const std::string &filename) const override;
            virtual std::string get(const std::string &key) const override;
            virtual std::string remove(const std::string &key) override;
            virtual bool hasValue(const std::string &key) const override;
            virtual void create(const std::string &key, const std::string &value) override;
            virtual void change(const std::string &key,
                                const std::string &newvalue) override;

            virtual uint32_t count() const override;

        protected:
            std::map<std::string, std::map<std::string, std::string>> withSections;
            std::map<std::string, std::string> withoutSections;
    };
}

#endif
