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
        std::shared_ptr<ChildType> activate(const std::string &name);
        std::shared_ptr<ChildType> activateByIndex(uint32_t index);

        std::shared_ptr<ChildType> getActivatedObject() const;
        uint32_t getActivatedIndex() const;

    protected:
        virtual bool onActivate(const std::shared_ptr<ChildType> &);
        virtual bool onActivateInternal(ChildType *);

        bool onAddInternal(ChildType *obj) override;
        bool onRemoveInternal(ChildType *obj) override;

    private:
        std::shared_ptr<ChildType> activatedObject;
        uint32_t activatedIndex;
    };
}

#include "templates/ActivatorObject.tpp"

#endif  // BKENGINE_ACTIVATOR_OBJECT_H