#ifndef BKENGINE_FONT_H
#define BKENGINE_FONT_H

#include <string>


namespace bkengine
{
    class Font
    {
    public:
        void setName(const std::string &name);
        void setSize(double size);

        std::string getName() const;
        double getSize() const;

    private:
        std::string name;
        double size;
    };
}

#endif  // BKENGINE_FONT_H