#ifndef BKENGINE_SERIALIZABLE_H
#define BKENGINE_SERIALIZABLE_H

#include <string>
#include <map>
#include <memory>

#include <json/json.h>


namespace bkengine
{
    class Serializable : public Json::Value
    {
        public:
            Serializable();
            Serializable(const Json::Value &json);

            virtual void deserialize(const Json::Value &) = 0;
            virtual Json::Value serialize() const = 0;

            std::string toString() const;
    };

    typedef std::shared_ptr<void>(*constructor)();
    class Serializer
    {
        private:
            static std::map<std::string, constructor> typeConstructors;

        public:
            template <typename T> static void addType(const std::string &name)
            {
                typeConstructors[name] = [] {
                    return std::static_pointer_cast<void>(std::make_shared<T>());
                };
            }

            template <typename T> static std::shared_ptr<T> getInstance(
                const std::string &name)
            {
                return std::static_pointer_cast<T>(typeConstructors[name]());
            }
    };

}

#endif
