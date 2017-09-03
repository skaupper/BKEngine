#ifndef BKENGINE_ACTIVATABLE_OBJECT_H
#define BKENGINE_ACTIVATABLE_OBJECT_H

namespace bkengine
{
    class ActivatableObject
    {
    public:
        virtual void onActivate()
        {
        }
        virtual void onDeactivate()
        {
        }


    protected:
        virtual void onActivateInternal()
        {
        }
        virtual void onDeactivateInternal()
        {
        }
    };
}

#endif  // BKENGINE_ACTIVATABLE_OBJECT_H