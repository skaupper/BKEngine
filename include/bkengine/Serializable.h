#ifndef BKENGINE_SERIALIZABLE_H
#define BKENGINE_SERIALIZABLE_H

#include <string>
#include <map>
#include <memory>

#include <json/json.h>


namespace bkengine
{
    class GameSerializer
    {
    public:
        static Json::Value serialize(const Game &);
        static std::shared_ptr<Game> deserialize(const Json::Value &obj)
        {
            auto game = Serializer::get(obj["type"].asString());
            game->deserialize(obj);
            for(auto &scene : obj["scenes"]) {
                game.addScene(SceneSerializer::deserialize(scene));
            }
            return game;
        }
    };

    class SceneSerializer
    {
    public:
        static Json::Value serialize(const Scene &);
        static std::shared_ptr<Scene> deserialize(const Json::Value &obj)
        {
            auto scene = Serializer::get(obj["type"].asString());
            scene->deserialize(obj);
            for(auto &element : obj["elements"]) {
                scene.addScene(ElementSerializer::deserialize(element));
            }
            return scene;
        }
    };

    class Serializable : public Json::Value
    {
        public:
            Serializable(const Json::Value &json);

            virtual void deserialize(const Json::Value &);
            virtual Json::Value serialize() const;
    };

    class Serializer
    {
        private:
            static std::map<std::string, std::shared_ptr<Serializable>(*)()> factories;

        public:
            template <typename T> static void addFactory(const std::string &name)
            {
                factories[name] = std::make_shared<T>;
            }

            template <typename T> static std::shared_ptr<T> get(const std::string &name)
            {
                return std::static_pointer_cast<T>(factories[name]());
            }
    };
}

#endif
