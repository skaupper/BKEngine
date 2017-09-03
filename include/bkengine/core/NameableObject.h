#ifndef BKENGINE_NAMEABLE_OBJECT_H
#define BKENGINE_NAMEABLE_OBJECT_H

#include <string>


namespace bkengine
{
    class NameableObject
    {
    public:
        std::string getName() const;

    protected:
        void setName(const std::string &);

    private:
        std::string name;
    };
}

#endif  // BKENGINE_NAMEABLE_OBJECT_H