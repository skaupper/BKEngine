#ifndef BKENGINE_MISC_H
#define BKENGINE_MISC_H

#include <cstdint>

#include "SDLWrapper.h"
#include "Logger.h"


namespace bkengine
{
    struct Rect;

    /**
        Represents a point in a two dimensional system.
        \sa Size
    */
    struct Point {
        float x;
        float y;

        /**
            Creates a instance of the point (0/0).
        */
        Point() : x(0), y(0) {}

        /**
            Creates a instance of the point (x/y).

            \param [in] x x coordinate of the point.
            \param [in] y y coordinate of the point.
        */
        Point(float x, float y) : x(x), y(y) {}

        /**
            Converts the point into an instance of Rect.
            The resulting Rect will be composed like "{ x, y, 0, 0 }".
            \sa Rect
        */
        operator Rect() const;

        /**
            Returns a string representation of the point.
            The representation looks like "<Point {x: 1.0; y: 2.0}>" therefore
            it is not suitable for any kind of calculation.

            \return A string representation of the point.
        */
        std::string toString() const;

        /**
            Returns the point represented as `SDL_Point`.

            \return A `SDL_Point` representation of the point.
        */
        SDL_Point toSDLPoint() const;
    };

    /**
        Represents a plane in a two dimensional system.
        \sa Point
    */
    struct Size {
        float w;
        float h;

        /**
            Creates a instance of a plane with the dimensions (0/0).
        */
        Size() : w(0), h(0) {}

        /**
            Creates a instance of a plane with the dimensions (w/h).
        */
        Size(float w, float h) : w(w), h(h) {}

        /**
            Converts the plane into an instance of Rect.
            The resulting Rect will be composed like "{ 0, 0, w, h }".
            \sa Rect
        */
        operator Rect() const;

        /**
            Returns a string representation of the plane.
            The representation looks like "<Size {w: 1.0; w: 2.0}>" therefore
            it is not suitable for any kind of calculation.

            \return A string representation of the plane.
        */
        std::string toString() const;
    };

    /**
        Represents a rectangle in a two dimensional system.
        \sa Point \n Size
    */
    struct Rect {
        float x;
        float y;
        float w;
        float h;

        /**
            Creates a rectangle from (0/0) to (100/100).
            Due to the fact that we mostly use relative coordinates
            the default values for width and height of the rectangle are 100 (%).
        */
        Rect() : Rect(100, 100) {}

        /**
            Creates a rectangle from (0/0) to (w/h).
        */
        Rect(float w, float h) : Rect(0, 0, w, h) {}

        /**
            Creates a rectangle from (x/y) to (x+w/y+h).
        */
        Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

        /**
            Converts the rectangle into a Point.
            The x and y coordinates are extracted and returned as (x/y).
        */
        explicit operator Point() const;

        /**
            Converts the rectangle into a plane Size.
            The w and h components are extracted and returned as (w/h).
        */
        explicit operator Size() const;

        /**
            Returns a string representation of the rectangle.
            The representation looks like "<Rect {x: 1.1; y: 2.0; w: 1.0; w: 2.0}>"
            therefore it is not suitable for any kind of calculation.

            \return A string representation of the rectangle.
        */
        std::string toString() const;

        /**
            Returns the rectangle represented as `SDL_Rect`.

            \return A `SDL_Rect` representation of the rectangle.
        */
        SDL_Rect toSDLRect() const;

        /**
            Compare two instances of Rect for equality.
            Two rectangles are equal if all of their components are equal.

            \param [in] rect Rect to compare to.

            \return `true` if both rectangles are equal `false` otherwise.
        */
        bool operator==(const Rect &rect) const;

        /**
            Compare two instances of Rect for inequality.
            Two rectangles are inequal if at least one of their components are unequal.

            \param [in] rect Rect to compare to.

            \return `true` if both rectangles are unequal `false` otherwise.
        */
        bool operator!=(const Rect &rect) const;

        /**
            Dummy operator which allows us to use a Rect in a `std::map`.
            Equals to `rect1 != rect2`.
        */
        bool operator<(const Rect &c) const;
    };

    /**
        Represents a 32bit RGBA color.
    */
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        /**
            Creates the color #000000.
        */
        Color() : Color(0, 0, 0) {}

        /**
            Creates the color #rrggbb.
        */
        Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 0xFF)  {}

        /**
            Creates the color #rrggbb with an opacity value of *a*.
        */
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

        std::string toString() const;

        /**
            Compare two instances of Color for equality.
            Two colors are equal if all of their components are equal.

            \param [in] color Color to compare to.

            \return `true` if both colors are equal `false` otherwise.
        */
        bool operator==(const Color &color) const;

        /**
            Compare two instances of Color for inequality.
            Two colors are unequal if at least one of their components are unequal.

            \param [in] color Color to compare to.

            \return `true` if both colors are unequal `false` otherwise.
        */
        bool operator!=(const Color &color) const;

        /**
            Dummy operator which allows us to use a Color in a `std::map`.
            Equals to `color1 != color2`.
        */
        bool operator<(const Color &color) const;
    };

    /**
        A collection of predefined colors.
    */
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

    /**
        Specifies the quality in which the text should be rendered.
        TextQuality::SOLID represents the lowest (but fastest) quality.\n
        TextQuality::BLENDED stands for the highest (and slowest) quality.
    */
    enum class TextQuality {
        SOLID = 1,
        BLENDED = 2
    };

    /**
        Specifies the texture type.
        Is used to differ between text and images.
    */
    enum class TextureType {
        TEXT,
        IMAGE
    };

    /**
        Wraps a pointer to a `SDL_Texture` with all needed (or given) information about it.
        This wrapper prevents Texture objects from being not copyable.
        If we would store the `SDL_Texture` directly in Texture we had
        to newly allocate a similiar texture at every copy.
    */
    class TextureWrapper
    {
            friend class Texture;
        public:
            /**
                Stores a texture of type TextureType::IMAGE.

                \param [in] tex A pointer to a valid `SDL_Texture` instance.
                \param [in] path The file path from which the texture has been created.
            */
            TextureWrapper(SDL_Texture *tex, const std::string &path);

            /**
                Stores a texture of type TextureType::TEXT.

                \param [in] tex A pointer to a valid `SDL_Texture` instance.
                \param [in] text The text from which the texture has been created.
                \param [in] fontName The font which was used to create the texture.
                \param [in] color The color of the text.
                \param [in] quality The quality in which the text will be rendered.

                \sa Font::getFont \n TextQuality \n Color
            */
            TextureWrapper(SDL_Texture *tex, const std::string &text,
                           const std::string &fontName, Color color, TextQuality quality);
            virtual ~TextureWrapper();

            /**
                Returns the `SDL_Texture` instance itself.

                \return A pointer to the texture.
            */
            SDL_Texture *get() const;

            /**
                Sets a new texture.
                If the object already owns a texture it will be freed beforehand.

                \param [in] tex A pointer to a valid `SDL_Texture` instance.

                \sa TextureWrapper::free
            */
            void set(SDL_Texture *tex);

            /**
                Frees the current texture.
                If the object does not own a texture nothing will happen.
            */
            void free();

            /**
                Returns the size of the texture.
                The size has been queried at TextureWrapper::set using the image interface.

                \return The size of the texture as Size.

                \sa TextureWrapper::set \n Size
            */
            Size getSize() const;

        private:
            TextureType type;
            std::string path;
            std::string text;
            std::string fontName;
            Color color;
            TextQuality quality;
            SDL_Texture *texture = NULL;
            Size originalSize;
    };

    /**
        Helper class for dealing with relative coordinates.
    */
    class RelativeCoordinates
    {
        public:
            /**
                Applies relative coordinates to a absolute (or also relative) rectangle.
                Imagine a window with the dimensions 1024:768.
                Applying a (relative) rectangle { 0, 0, 50, 25 } would result in an (absolute) rectangle
                { 0, 0, 512, 192 }.

                \param [in] rect Rectangle with relative coordinates to apply.
                \param [in] srcRect The reference rectangle.

                \return The result of the transformation as Rect.
            */
            static Rect apply(const Rect &rect, const Rect &srcRect);
    };
}

#endif
