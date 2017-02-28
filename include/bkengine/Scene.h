#ifndef BKENGINE_SCENE_H
#define BKENGINE_SCENE_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Element.h"

namespace bkengine
{
    class Game;
    class Scene
    {
            friend class Element;
            /* hierarchal */
        public:
            bool hasElement(const std::string &name) const;
            bool hasElement(unsigned int index) const;

            void removeElement(const std::string &name);
            void removeElement(unsigned int index);

            Element &getElement(unsigned int index);
            Element &getElement(const std::string &name);

            template <typename T> T &addElement(const T &);
            template <typename T> T &addElement(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addElement(Params...);
            template <typename T> T &getElement(const std::string &name);
            template <typename T> T &getElement(unsigned int index);

        protected:
            void addToCollisionLayer(Element *, int layer);
            void removeFromCollisionLayer(Element *);
            std::vector<Element *> getCollisionLayer(int layer);

            Game *parentGame;
            std::vector<std::shared_ptr<Element>> elements;
            std::map<int, std::vector<Element *>> collisionLayers;


            /* getter and setter */
        public:
            std::string getName() const;

        protected:
            std::string name;


            /* other stuff */
        public:
            explicit Scene(Game *parentGame, const std::string &name = "");
            Scene(Scene &&scene);
            Scene &operator=(Scene &&scene);
            virtual ~Scene();

            virtual void setup();

            virtual void onLoop();
            virtual void onRender();
            virtual bool onEvent(const Event &);

            void clear();

        protected:

    };

#include "templates/Scene_templates.h"
}

#include "Game.h"

#endif
