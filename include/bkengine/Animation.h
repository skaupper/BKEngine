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
            explicit Animation(const std::string &descr = "", unsigned int frameDelta = 1);
            virtual ~Animation();

            void addImage(const std::string &path, const Rect &size = Rect(),
                          const Rect &clip = Rect());
            void addText(const std::string &fontName, const std::string &text,
                         const Rect &size, const Color &color = Color(),
                         TextQuality quality = TextQuality::SOLID);

            template <typename T> void addImage(const std::string &path,
                                                const Rect &clip = Rect(), const Rect &size = Rect());
            template <typename T> void addText(const std::string &fontName,
                                               const std::string &text, const Rect &size, const Color &color = Color(),
                                               TextQuality quality = TextQuality::SOLID);
            template <typename T> void addTexture(const T &texture);

            bool hasTexture(unsigned int index) const;

            Texture &getNextTexture();
            Texture &getCurrentTexture();

            void incFrameCount();
            void setFramesPerTexture(unsigned int frames);

            void reset();

            std::string getDescription() const;

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
