#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include "Animation.h"
#include "Misc.h"
#include "Event.h"

namespace bkengine
{
    class Scene;
    class Element
    {
            friend class Scene;
        public:
            explicit Element(Scene *parentScene, const std::string &description = "",
                             const Rect &renderbox = Rect(),
                             int collisionLayer = -1);
            virtual ~Element();

            void activate(unsigned int index);
            void activate(const std::string &name);

            bool hasAnimation(const std::string &name) const;
            bool hasAnimation(unsigned int index) const;

            void removeAnimation(const std::string &name);
            void removeAnimation(unsigned int index);

            Animation &getAnimation(const std::string &name);
            Animation &getAnimation(unsigned int index);
            Animation &getCurrentAnimation();

            template <typename T> T &addAnimation(const T &);
            template <typename T> T &addAnimation(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addAnimation(Params...);
            template <typename T> T &getAnimation(const std::string &name);
            template <typename T> T &getAnimation(unsigned int index);
            template <typename T> T &getCurrentAnimation();

            virtual void setup();

            virtual void onRender(const Rect &parentRect = Rect());
            virtual void onLoop();
            virtual bool onEvent(const Event &);

            void applyCollisionBox(const Rect &);
            Rect getCollisionBox() const;
            void setRenderBox(const Rect &);
            Rect getRenderBox() const;
            std::string getDescription() const;

            void clear();

        protected:
            std::string description;
            Rect renderBox;
            Rect collisionBox;
            bool flipped;
            int frame;
            int collisionLayer;
            int currentAnimation;
            std::vector<std::shared_ptr<Animation>> animations;
            Scene *parentScene;

            std::vector<Element *> getCollisionLayer();
    };

#include "templates/Element_templates.h"
}

#endif // ELEMENT_H
