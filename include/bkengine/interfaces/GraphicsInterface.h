#ifndef BKENGINE_GRAPHICSINTERFACE_H
#define BKENGINE_GRAPHICSINTERFACE_H

#include <string>

#include "utils/Misc.h"


namespace bkengine
{
    class GraphicsInterface
    {
        public:
            virtual ~GraphicsInterface() = default;

            virtual bool initWindow(int width, int height, const std::string &title) = 0;
            virtual std::string getLastError() = 0;

            virtual void resizeWindow(int width, int height) = 0;
            virtual void setWindowTitle(const std::string &title) = 0;
            virtual void delay(uint32_t milliseconds) = 0;

            virtual Rect getWindowSize() = 0;

            virtual bool setIcon(const std::string &iconPath) = 0;

            virtual void clear() = 0;
            virtual void draw() = 0;
    };
}

#endif