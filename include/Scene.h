#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include <string>
#include <memory>

#include "Element.h"
#include "Entity.h"

namespace bkengine
{
    class Element;
    class Game;

    class Scene
    {
        public:
            explicit Scene(const std::string &name = "");
            Scene(Scene &&scene);
            Scene &operator=(Scene &&scene);
            virtual ~Scene();

            bool hasElement(const std::string &name) const;
            bool hasElement(unsigned int index) const;

            void removeElement(const std::string &name);
            void removeElement(unsigned int index);


            template <typename T> T &addElement(const T &);
            template <typename T> T &addElement(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addElement(Params...);

            template <typename T> T &getElement(const std::string &name);
            template <typename T, typename... Params> T &getElement(unsigned int index);

            virtual void onLoop();
            virtual void onRender();
            virtual int onEvent(SDL_Event *);

            std::string getName() const;

        private:
            std::string name;

            std::vector<std::shared_ptr<Element>> elements;
    };

#include "templates/Scene_templates.h"
}

#endif // SCENE_H_INCLUDED
