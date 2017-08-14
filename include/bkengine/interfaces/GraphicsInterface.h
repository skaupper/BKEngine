#ifndef BKENGINE_GRAPHICSINTERFACE_H
#define BKENGINE_GRAPHICSINTERFACE_H

#include <cstdint>
#include <string>

#include "utils/Geometry.h"


namespace bkengine
{
    class GraphicsInterface
    {
        public:
            virtual ~GraphicsInterface() = default;
            
            virtual bool initWindow(Size, const std::string &) = 0;
            virtual std::string getLastError() = 0;
            
            virtual void setWindowSize(Size) = 0;
            virtual Size getWindowSize() = 0;
            
            virtual void setWindowTitle(const std::string &) = 0;
            virtual std::string getWindowTitle() = 0;
            
            virtual void delay(uint32_t) = 0;
            
            
            virtual bool setIcon(const std::string &) = 0;
            
            virtual void clear() = 0;
            virtual void draw() = 0;
    };
}

#endif