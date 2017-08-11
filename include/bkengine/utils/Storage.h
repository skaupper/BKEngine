#ifndef BKENGINE_STORAGE_H
#define BKENGINE_STORAGE_H

#include <string>

namespace bkengine
{
    class Storage
    {
        private:
            std::string type;

        public:
            static const std::string TYPE;

            Storage(const std::string &type);
            virtual ~Storage();
            const std::string &getType() const;
    };
}

#endif
