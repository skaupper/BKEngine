#ifndef BKENGINE_SERIALIZABLE_H
#define BKENGINE_SERIALIZABLE_H

#include <string>
#include <map>
#include <memory>

#include <json/json.h>


namespace bkengine
{
    /**
        Provides a skeleton for basic serialization and deserialization
        together with a backup and restore mechanism.
    */
    class Serializable
    {
        private:
            Json::Value original;

        public:
            Serializable();

            /**
                Uses a JSON object to set member variables.
                Is used by subclasses to simplify serialization. The default implementation
                creates a backup of *json* to allow resetting the object later on.\n
                The recommended way of using this method is following:
                \code{.cpp}
                void SubSerialize::deserialize(const Json::Value &json)
                {
                    Serialize::deserialize(json);

                    // add your own code here
                }
                \endcode

                In this way you ensure that the overridden methods will be called anyways.

                \sa Serializable::serialize \n Serializable::backup \n Serializable::restore
            */
            virtual void deserialize(const Json::Value &json);

            /**
                Serializes the object to a JSON object.
                Subclasses can override this method to map its members to a JSON object
                which allows to save it to a file and restore it later on
                (given that Serializable::deserialize is overridden as well!).\n
                The default implementation returns any backup done by Serializable::deserialize
                or Serializable::backup (or an empty object if none of them has been called).\n
                The recommended way of using this method is following:
                \code{.cpp}
                Json::Value SubSerialize::serialize()
                {
                    Json::Value json = Serialize::serialize();
                    // add your own code here
                    return json;
                }
                \endcode

                This way you ensure that all serialization done by super classes is really done!

                \sa Serializable::deserialize \n Serializable::backup \n Serializable::restore
            */
            virtual Json::Value serialize() const;

            /**
                Backups the current state of the object.
                Through a call to Serializable::serialize the current state of
                the object is backupped to allow the current state to be restored later on.\n
                Note: This overrides any backups done by Serializable::deserialize!

                \sa Serializable::deserialize \n Serializable::serialize \n Serializable::restore
            */
            void backup();

            /**
                Restores any backup of the object.
                If any backup has been created so far (through calls to
                Serializable::deserialize or Serializable::backup) it will be restored with calling Serializable::deserialize.
                Note: This overrides does **NOT** override the current backup.

                \sa Serializable::deserialize \n Serializable::serialize \n Serializable::restore
            */
            void restore();

            /**
                Creates a (beautified) string representation of the object.
                \return A `std::string` representing the current state of the object.
            */
            std::string toString() const;
    };

    /**
        Allows associations from a string to a type which allows a
        (more or less) dynamic creation of any object.

        __Important note:__ Using Serializer effectively
        disables type checking done by the compiler. This way the compiler
        would allow you unreasonable conversions which create runtime errors!
    */
    class Serializer
    {
        private:
            typedef std::shared_ptr<void>(*constructor)();
            static std::map<std::string, constructor> typeConstructors;

        public:
            /**
                Associates a type with a string name.
                Association is done by caching the name and the constructor (!)
                of the type (given as template parameter) in a map
                (a `std::shared_ptr` to the type to be exact).

                \param [in] name A name for the type specified as template parameter.

                \sa Serializer::getInstance
            */
            template <typename T> static void addType(const std::string &name)
            {
                typeConstructors[name] = [] {
                    return std::static_pointer_cast<void>(std::make_shared<T>());
                };
            }

            /**
                Gets an instance of a type associated with *name*.
                _name_ will be looked up in the type associations created with Serializable::addType.
                If no type is found `nullptr` will be returned.\n
                __Important note:__ Using Serializer::addType and Serializer::getInstance effectively
                disables type checking done by the compiler. This way the compiler
                would allow you unreasonable conversions which create runtime errors!

                \param [in] name An associated name for the constructor of a type.

                \return A `std::shared_ptr` to the type given as template
                parameter created with the constructor associated with *name*.

                \sa Serializer::addType
            */
            template <typename T> static std::shared_ptr<T> getInstance(
                const std::string &name)
            {
                return std::static_pointer_cast<T>(typeConstructors[name]());
            }
    };
}

#endif
