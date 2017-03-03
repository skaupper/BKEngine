#ifndef BKENGINE_ELEMENT_H
#define BKENGINE_ELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include "Animation.h"
#include "Misc.h"
#include "Event.h"
#include "Serializable.h"

namespace bkengine
{
    class Scene;
    class Element : public Serializable
    {
            friend class Scene;
            friend class GameSerializer;

            /* hierarchal */
        public:
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

        protected:
            int currentAnimation;
            std::vector<std::shared_ptr<Animation>> animations;
            Scene *parentScene;


            /* getter and setter */
        public:
            void applyCollisionBox(const Rect &);
            Rect getCollisionBox() const;
            void setRenderBox(const Rect &);
            Rect getRenderBox() const;
            std::string getDescription() const;

        protected:
            std::string description;
            Rect renderBox;
            Rect collisionBox;


            /* other stuff */
        public:
            explicit Element(Scene *parentScene = nullptr, const std::string &description = "",
                             const Rect &renderbox = Rect(),
                             int collisionLayer = -1);
            virtual ~Element();

            virtual void setupEnvironment();
            virtual void setupAnimations();

            virtual void onRender(const Rect &parentRect = Rect());
            virtual void onLoop();
            virtual bool onEvent(const Event &);

            void clear();

            virtual void deserialize(const Json::Value &) override;
            virtual Json::Value serialize() const override;


        protected:
            int collisionLayer;

            std::vector<Element *> getCollisionLayer();
    };

#include "templates/Element_templates.h"
}

#endif
