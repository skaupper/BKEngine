#ifndef BKENGINE_COLOR_H
#define BKENGINE_COLOR_H

#include <cstdint>
#include <string>


namespace bkengine
{
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        
        Color();
        Color(uint8_t r, uint8_t g, uint8_t b);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
        
        std::string toString() const;
        
        bool operator==(const Color &color) const;
        bool operator!=(const Color &color) const;
        
        /**
            Dummy operator which allows us to use a Color in a `std::map`.
            Equals to `color1 != color2`.
        */
        bool operator<(const Color &color) const;
    };
    
    class Colors
    {
        private:
            Colors() = delete;
            
        public:
            static Color BLACK;
            static Color WHITE;
            static Color RED;
            static Color LIME;
            static Color BLUE;
            static Color YELLOW;
            static Color CYAN;
            static Color MAGENTA;
            static Color SILVER;
            static Color GRAY;
            static Color MAROON;
            static Color OLIVE;
            static Color GREEN;
            static Color PURPLE;
            static Color TEAL;
            static Color NAVY;
    };
}

#endif // BKENGINE_COLOR_H