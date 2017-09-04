namespace bkengine
{
    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> ActivatorObject<ChildType, ParentType>::activate(const std::string &name)
    {
        return activateByIndex(this->getChildIndex(name));
    }

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> ActivatorObject<ChildType, ParentType>::activateByIndex(uint32_t index)
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

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> ActivatorObject<ChildType, ParentType>::getActivatedObject() const
    {
        return activatedObject;
    }

    template <typename ChildType, typename ParentType>
    uint32_t ActivatorObject<ChildType, ParentType>::getActivatedIndex() const
    {
        return activatedIndex;
    }

    template <typename ChildType, typename ParentType>
    bool ActivatorObject<ChildType, ParentType>::onActivate(const std::shared_ptr<ChildType> &)
    {
        return false;
    }

    template <typename ChildType, typename ParentType>
    bool ActivatorObject<ChildType, ParentType>::onActivateInternal(ChildType *)
    {
        return false;
    }

    template <typename ChildType, typename ParentType>
    bool ActivatorObject<ChildType, ParentType>::onAddInternal(ChildType *obj)
    {
        return HierarchicalObject<ChildType, ParentType>::onAddInternal(obj);
    }

    template <typename ChildType, typename ParentType>
    bool ActivatorObject<ChildType, ParentType>::onRemoveInternal(ChildType *obj)
    {
        return HierarchicalObject<ChildType, ParentType>::onRemoveInternal(obj);
    }
}