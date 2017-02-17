#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

#include "Texture.h"
#include "Logger.h"


namespace bkengine
{
    class Animation
    {
        public:
            Animation(const std::string &descr = "", unsigned int frameDelta = 1);
            virtual ~Animation();

            void addImage(const std::string &path);
            void addImage(const std::string &path, Rect rect);
            void addText(const std::string &text, const Color &color, short size);

            template <typename T> void addImage(const std::string &path);
            template <typename T> void addImage(const std::string &path, Rect rect);
            template <typename T> void addText(const std::string &text, const Color &color,
                                               short size);
            template <typename T> void addTexture(const T &texture);

            bool hasTexture(unsigned int index);

            Texture &getNextTexture();
            Texture &getCurrentTexture();

            void incFrameCount();
            void setFramesPerTexture(unsigned int frames);

            void reset();

            std::string getDescription();

        protected:
            unsigned int frameCounter;
            unsigned int framesPerTexture;
            int currentIndex;
            std::vector<Texture> textures;
            std::string description;
    };

#include "templates/Animation_templates.h"
}

#endif // ANIMATION_H
