#ifndef BKENGINE_FONT_H
#define BKENGINE_FONT_H

#include <string>


namespace bkengine
{
    class Font
    {
    public:
        explicit Font() = default;

        void setName(const std::string &name);
        void setSize(double size);

        std::string getName() const;
        double getSize() const;

    private:
        std::string name;
        double size = 0.0;
    };
}

#endif  // BKENGINE_FONT_H