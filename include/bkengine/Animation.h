#ifndef BKENGINE_ANIMATION_H
#define BKENGINE_ANIMATION_H

#include <string>
#include <vector>

#include "Texture.h"
#include "Logger.h"


namespace bkengine
{
    class Animation
    {
            /* hierarchal */
        public:
            template <typename T> void addImage(const std::string &path,
                                                const Rect &clip = Rect(), const Rect &size = Rect());
            template <typename T> void addText(const std::string &fontName,
                                               const std::string &text, const Rect &size, const Color &color = Color(),
                                               TextQuality quality = TextQuality::SOLID);
            template <typename T> void addTexture(const T &texture);

            bool hasTexture(unsigned int index) const;

            Texture &getNextTexture();
            Texture &getCurrentTexture();

        protected:
            int currentIndex;
            std::vector<Texture> textures;


            /* getter and setter */
        public:
            std::string getDescription() const;

        protected:
            std::string description;


            /* other stuff */
        public:
            explicit Animation(const std::string &descr = "", unsigned int frameDelta = 1);
            virtual ~Animation();

            void incFrameCount();
            void setFramesPerTexture(unsigned int frames);

            void reset();

        protected:
            unsigned int frameCounter;
            unsigned int framesPerTexture;
    };

#include "templates/Animation_templates.h"
}

#endif
