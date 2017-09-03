#ifndef BKENGINE_ACTIVATOR_OBJECT_H
#define BKENGINE_ACTIVATOR_OBJECT_H

#include <type_traits>

#include "core/ActivatableObject.h"
#include "core/HierarchicalObject.h"


namespace bkengine
{
    template <typename ChildType, typename ParentType>
    class ActivatorObject : public HierarchicalObject<ChildType, ParentType>
    {
        static_assert(std::is_base_of<ActivatableObject, ChildType>::value,
                      "Child type is no sub class of ActivatableObject!");

    public:
        std::shared_ptr<ChildType> activate(const std::string &name)
        {
            return activateByIndex(this->getChildIndex(name));
        }

        std::shared_ptr<ChildType> activateByIndex(uint32_t index)
        {
            auto child = this->getChildByIndex(index);
            if (!onActivateInternal(child.get()) && !onActivate(child)) {
                static_cast<ChildType *>(child.get())->onActivate();
                activatedObject = child;
                activatedIndex = index;
                return child;
            }
            return nullptr;
        }

        std::shared_ptr<ChildType> getActivatedObject() const
        {
            return activatedObject;
        }

        uint32_t getActivatedIndex() const
        {
            return activatedIndex;
        }

    protected:
        virtual bool onActivate(const std::shared_ptr<ChildType> &)
        {
            return false;
        }

        virtual bool onActivateInternal(ChildType *)
        {
            return false;
        }

        bool onAddInternal(ChildType *obj) override
        {
            return HierarchicalObject<ChildType, ParentType>::onAddInternal(obj);
        }

        bool onRemoveInternal(ChildType *obj) override
        {
            return HierarchicalObject<ChildType, ParentType>::onRemoveInternal(obj);
        }

    private:
        std::shared_ptr<ChildType> activatedObject;
        uint32_t activatedIndex;
    };
}

#endif  // BKENGINE_ACTIVATOR_OBJECT_H