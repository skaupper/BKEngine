namespace bkengine
{
    template <typename ChildType, typename ParentType>
    void HierarchicalObject<ChildType, ParentType>::addChild(const std::shared_ptr<ChildType> &child)
    {
        if(hasChild(child->getName())) {
            throw NameAlreadyExistsException("A child object with the name '" + child->getName() + "' already exists.");    
        }

        if (!onAddInternal(child.get()) && !onAdd(child)) {
            nameSet.insert(child->getName());
            children.push_back(child);
        }
    }

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> HierarchicalObject<ChildType, ParentType>::removeChildByName(const std::string &name)
    {
        auto it = std::find_if(children.begin(), children.end(), getNamePredicate(name));
        if (it == children.end()) {
            throw NameNotFoundException("No child object '" + name + "' exists.");
        }

        if (!onRemoveInternal(it->get()) && !onRemove(*it)) {
            auto removedChild = *it;
            nameSet.erase(name);
            children.erase(it);
            return removedChild;
        }

        return nullptr;
    }

    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::hasChild(const std::string &name) const
    {
        return nameSet.count(name) != 0;
    }

    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::hasChildIndex(uint32_t index) const
    {
        return index < children.size();
    }

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> HierarchicalObject<ChildType, ParentType>::getChildByIndex(uint32_t index) const
    {
        if (index >= children.size()) {
            throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
        }

        return children[index];
    }

    template <typename ChildType, typename ParentType>
    uint32_t HierarchicalObject<ChildType, ParentType>::getChildIndexByName(const std::string &name)
    {
        auto it = std::find_if(children.cbegin(), children.cend(), getNamePredicate(name));
        if (it == children.cend()) {
            throw NameNotFoundException("No child object '" + name + "' exists.");
        }

        return std::distance(children.cbegin(), it);
    }

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> HierarchicalObject<ChildType, ParentType>::getChildByName(const std::string &name) const
    {
        auto it = std::find_if(children.cbegin(), children.cend(), getNamePredicate(name));
        if (it == children.cend()) {
            throw NameNotFoundException("No child object '" + name + "' exists.");
        }

        return *it;
    }

    template <typename ChildType, typename ParentType>
    std::string HierarchicalObject<ChildType, ParentType>::getChildNameByIndex(uint32_t index) const
    {
        if (index >= children.size()) {
            throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
        }

        return children[index]->getName();
    }

    template <typename ChildType, typename ParentType>
    std::shared_ptr<ChildType> HierarchicalObject<ChildType, ParentType>::removeChildByIndex(uint32_t index)
    {
        if (index >= children.size()) {
            throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
        }

        auto it = children.begin();
        std::advance(it, index);

        if (!onRemoveInternal(it->get()) && !onRemove(*it)) {
            auto removedChild = *it;
            children.erase(it);
            return removedChild;
        }

        return nullptr;
    }

    template <typename ChildType, typename ParentType>
    uint32_t HierarchicalObject<ChildType, ParentType>::getChildrenCount() const
    {
        return children.size();
    }

    template <typename ChildType, typename ParentType>
    std::vector<std::string> HierarchicalObject<ChildType, ParentType>::getAllChildrenNames() const
    {
        auto extractNames = [](const std::shared_ptr<ChildType> &child) { return child->getName(); };

        std::vector<std::string> allNames;

        std::transform(children.cbegin(), children.cend(), std::back_inserter(allNames), extractNames);
        return allNames;
    }

    template <typename ChildType, typename ParentType>
    void HierarchicalObject<ChildType, ParentType>::addAllChildren(
        const std::vector<std::shared_ptr<ChildType>> &newChildren)
    {
        for(auto &child : newChildren) {
            addChild(child);
        }
    }

    template <typename ChildType, typename ParentType>
    std::vector<std::shared_ptr<ChildType>> HierarchicalObject<ChildType, ParentType>::removeAllChildren()
    {
        if(children.size() == 0) {
            return {};
        }

        std::vector<std::shared_ptr<ChildType>> removedChildren;

        for (auto i = children.size(); i != 0; --i) {
            auto removedChild = removeChildByIndex(i - 1);
            if (removedChild) {
                removedChildren.push_back(removedChild);
            }
        }

        return removedChildren;
    }

    template <typename ChildType, typename ParentType>
    std::vector<std::shared_ptr<ChildType>> HierarchicalObject<ChildType, ParentType>::getAllChildren() const
    {
        return children;
    }

    template <typename ChildType, typename ParentType>
    std::weak_ptr<ParentType> HierarchicalObject<ChildType, ParentType>::getParent() const
    {
        return parent;
    }

    template <typename ChildType, typename ParentType>
    void HierarchicalObject<ChildType, ParentType>::setParent(const std::weak_ptr<ParentType> &newParent)
    {
        parent = newParent;
    }


    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::onAdd(const std::shared_ptr<ChildType> &)
    {
        return false;
    }

    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::onRemove(const std::shared_ptr<ChildType> &)
    {
        return false;
    }


    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::onAddInternal(ChildType *)
    {
        return false;
    }

    template <typename ChildType, typename ParentType>
    bool HierarchicalObject<ChildType, ParentType>::onRemoveInternal(ChildType *)
    {
        return false;
    }
}