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
            /* hierarchal */
        public:
            template <typename T> void addImage(const std::string &path,
                                                const Rect &clip = Rect(), const Rect &size = Rect());
            template <typename T> void addText(const std::string &fontName,
                                               const std::string &text, const Rect &size, const Color &color = Color(),
                                               TextQuality quality = TextQuality::SOLID);
            template <typename T> void addTexture(const T &texture);
            template <typename T> void addTexture(std::shared_ptr<T> texture);

            bool hasTexture(unsigned int index) const;

            Texture &getNextTexture();
            Texture &getCurrentTexture();

        protected:
            int currentTexture;
            std::vector<std::shared_ptr<Texture>> textures;


            /* getter and setter */
        public:
            std::string getName() const;

        protected:
            std::string name;


            /* other stuff */
        public:
            explicit Animation(const std::string &descr = "", unsigned int frameDelta = 1);
            virtual ~Animation();

            void incFrameCount();
            void setFramesPerTexture(unsigned int frames);
            void reset();

            virtual void setupTextures();
            virtual void setupEnvironment();

            virtual void deserialize(const Json::Value &) override;
            virtual Json::Value serialize() const override;

        protected:
            unsigned int frameCounter;
            unsigned int framesPerTexture;
    };

#include "templates/Animation_templates.h"
}

#endif
