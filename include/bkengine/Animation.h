#ifndef BKENGINE_ANIMATION_H
#define BKENGINE_ANIMATION_H

#include <string>
#include <vector>
#include <memory>

#include "Texture.h"
#include "Serializable.h"
#include "GameSerializer.h"
#include "Logger.h"


namespace bkengine
{
    class Animation : public Serializable
    {
            friend class Element;
            friend class Serializer;
            /* hierarchal */
        public:
            /**
                Creates an image textures an adds it to its children.

                \param [in] path Filepath to the image file. Which formats are supported depends on the underlying framework.
                \param [in] clip Specifies which region of the texture should be used. Components are in percent that means {0, 0, 100, 100} clips the whole image.
                \param [in] size Specifies the relative size of the texture to the parent element.

                \sa Texture::loadImage
            */
            template <typename T> void addImage(const std::string &path,
                                                const Rect &clip = Rect(), const Rect &size = Rect());

            /**
                Creates a texture of a text an adds it to its children.

                \param [in] fontName The name of the font to be used. The font name must be registered with Font::registerFont.
                \param [in] text The UTF-8 encoded text to be rendered.
                \param [in] size Specifies the relative size of the texture to the parent element.
                \param [in] color A static RGBA8 color for the text.
                \param [in] quality Specify the texture quality to be used.

                \sa Font::registerFont \n Font::getFont \n TextQuality
            */
            template <typename T> void addText(const std::string &fontName,
                                               const std::string &text, const Rect &size, const Color &color = Color(),
                                               TextQuality quality = TextQuality::SOLID);

            /**
                Adds a new texture to its children.

                \param [in] texture The texture to be added.

                \sa Texture
            */
            template <typename T> void addTexture(const T &texture);

            /**
                Adds a new texture to its children.

                \param [in] texture The texture to be added.

                \sa Texture
            */
            template <typename T> void addTexture(const std::shared_ptr<T> texture);

            /**
                Checks if the child *index* exists.

                \param [in] index The index to be checked.
                \return `true` if the child exists `false` otherwise.
            */
            bool hasTexture(unsigned int index) const;

            /**
                Returns the currently rendered Texture.
                Note: This can potentially return another Texture each frame!

                \return The texture which has been rendered recently.
            */
            Texture &getCurrentTexture();

        protected:
            Texture &getNextTexture();
            int currentTexture;
            std::vector<std::shared_ptr<Texture>> textures;


            /* getter and setter */
        public:
            /**
                Returns the name of the Animation.

                \return The name of the Animation as `std::string`.
            */
            std::string getName() const;

        protected:
            std::string name;


            /* other stuff */
        public:
            explicit Animation(const std::string &descr = "", unsigned int frameDelta = 1);
            virtual ~Animation();

            /**
                Sets how long a single texture should be rendered straight.

                \param [in] frames Sets the time per texture (currently 60 frames = 1 second).
            */
            void setFramesPerTexture(unsigned int frames);

            /**
                Resets the frame counter and starts over with the first texture.
            */
            void reset();

            /**
                Initializes textures at instance creation.
                Should be overrided by subclasses. The default implementation does nothing.\n
                Note: This method is never called while deserializing!

                \sa Animation::setupEnvironment
            */
            virtual void setupTextures();


            /**
                Initializes environment at instance creation.
                Should be overrided by subclasses. The default implementation does nothing.\n
                Note: This method is called no matter how the instance is created.

                \sa Animation::setupTextures
            */
            virtual void setupEnvironment();

            virtual void deserialize(const Json::Value &) override;
            virtual Json::Value serialize() const override;

        protected:
            void incFrameCount();

            unsigned int frameCounter;
            unsigned int framesPerTexture;
    };

#include "templates/Animation_templates.h"
}

#endif
