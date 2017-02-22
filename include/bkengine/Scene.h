#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Element.h"

namespace bkengine
{
    class Scene
    {
            friend class Element;
        public:
            explicit Scene(const std::string &name = "");
            Scene(Scene &&scene);
            Scene &operator=(Scene &&scene);
            virtual ~Scene();

            bool hasElement(const std::string &name) const;
            bool hasElement(unsigned int index) const;

            void removeElement(const std::string &name);
            void removeElement(unsigned int index);

            Element &addElement(const std::string &description = "",
                                const Rect &renderBox = Rect(),
                                int collisionLayer = -1);
            Element &getElement(const std::string &name);
            Element &getElement(unsigned int index);

            template <typename T> T &addElement(const T &);
            template <typename T> T &addElement(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addElement(Params...);
            template <typename T> T &getElement(const std::string &name);
            template <typename T> T &getElement(unsigned int index);

            virtual void onLoop();
            virtual void onRender();
            virtual bool onEvent(const Event &);

            std::string getName() const;

        private:
            std::string name;
            std::vector<std::shared_ptr<Element>> elements;
            std::map<int, std::vector<Element *>> collisionLayers;

            void addToCollisionLayer(Element *, int layer);
            void removeFromCollisionLayer(Element *);
            std::vector<Element *> getCollisionLayer(int layer);


    };

#include "templates/Scene_templates.h"
}

#endif // SCENE_H_INCLUDED
