#ifndef BKENGINE_ELEMENT_H
#define BKENGINE_ELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include "core/Animation.h"
#include "utils/Event.h"
#include "utils/Misc.h"
#include "serialization/Serializable.h"


namespace bkengine
{
    class Scene;

    /**
        Represents the most basic collidable graphics element.

        The instance holds a vector of Animation s.
    */
    class Element : public Serializable
    {
            friend class Scene;

            /* hierarchal */
        public:
            /**
                Sets the current animation.

                If `index` does not exist in the vector,
                a warning is printed and the first animation will be activated.

                \param [in] index The index of the animation to be activated.
            */
            void activate(unsigned int index);

            /**
                Sets the current animation.

                If no animation with the name `name` is found,
                a warning is printed and the first animation will be activated.

                \param [in] name The name of the animation to be activated.
            */
            void activate(const std::string &name);


            /**
                Checks if a animation exists.

                \param [in] name The name of the animation to be checked.

                \return `true` if an animation is found, `false` otherwise.
            */
            bool hasAnimation(const std::string &name) const;

            /**
                Checks if a animation exists.

                \param [in] index The index of the animation to be checked.

                \return `true` if an animation is found, `false` otherwise.
            */
            bool hasAnimation(unsigned int index) const;

            /**
                Removes an already existing animation.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] name The name of the animation to be removed.
            */
            void removeAnimation(const std::string &name);

            /**
                Removes an already existing animation.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] index The index of the animation to be removed.
            */
            void removeAnimation(unsigned int index);


            /**
                Returns an animation represented by `name`.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] name The name of the animation to be returned.
            */
            Animation &getAnimation(const std::string &name);

            /**
                Returns an animation represented at `index`.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] index The index of the animation to be returned.
            */
            Animation &getAnimation(unsigned int index);

            /**
                Returns the current activated animation.

                If the animation is not found, a message is logged
                and a std::string is thrown.
                This is only the case if there are no animations yet.

                \tparam T The type to which the animation should be casted.
            */
            Animation &getCurrentAnimation();

            /**
                Adds an animation.

                \param [in] animation The animation to be added.
                \tparam T The animation type. This has to be a subtype of Animation.
            */
            template <typename T> T &addAnimation(const T &animation);

            /**
                Adds an animation.

                \param [in] animation The animation to be added.
                \tparam T The animation type. This has to be a subtype of Animation.
            */
            template <typename T> T &addAnimation(const std::shared_ptr<T> &animation);

            /**
                Adds an animation by using the animations constructor directly.

                \param [in] params The parameters used to create the animation.
                \tparam T The animation type. This has to be a subtype of Animation.
                \tparam Params The types of the constructors parameters.
            */
            template <typename T, typename... Params> T &addAnimation(Params...);

            /**
                Returns an animation represented by `name`.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] name The name of the animation to be returned.
                \tparam T The type to which the animation should be casted.
            */
            template <typename T> T &getAnimation(const std::string &name);

            /**
                Returns an animation represented at `index`.

                If the animation is not found, a message is logged
                and a std::string is thrown.

                \param [in] index The index of the animation to be returned.
                \tparam T The type to which the animation should be casted.
            */
            template <typename T> T &getAnimation(unsigned int index);

            /**
                Returns the current activated animation.

                If the animation is not found, a message is logged
                and a std::string is thrown.
                This is only the case if there are no animations yet.

                \tparam T The type to which the animation should be casted.
            */
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
            std::string getName() const;
            unsigned int getAnimationCount() const;

        protected:
            std::string name;
            Rect renderBox;
            Rect collisionBox;


            /* other stuff */
        public:
            explicit Element(Scene *parentScene = nullptr,
                             const std::string &name = "",
                             const Rect &renderbox = Rect(),
                             int collisionLayer = -1);
            virtual ~Element();

            virtual void setupEnvironment();
            virtual void setupAnimations();

            virtual void onRender(std::shared_ptr<GraphicsInterface> graphicsInterface,
                                  const Rect &parentRect = Rect());
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
