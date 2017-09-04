#ifndef BKENGINE_HIERARCHICAL_OBJECT_H
#define BKENGINE_HIERARCHICAL_OBJECT_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "core/NameableObject.h"
#include "exceptions/IndexOutOfRangeException.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    template <typename ChildType, typename ParentType>
    class HierarchicalObject : public NameableObject
    {
    private:
        auto getNamePredicate(const std::string &name)
        {
            return [name](const std::shared_ptr<ChildType> &child) { return child->getName() == name; };
        }

    public:
        void addChild(const std::shared_ptr<ChildType> &child);

        bool hasChild(const std::string &name) const;

        std::shared_ptr<ChildType> removeChildByName(const std::string &name);
        std::shared_ptr<ChildType> removeChildByIndex(uint32_t index);

        uint32_t getChildIndex(const std::string &name);
        std::string getChildNameByIndex(uint32_t index) const;

        std::shared_ptr<ChildType> getChildByName(const std::string &name) const;
        std::shared_ptr<ChildType> getChildByIndex(uint32_t index) const;

        uint32_t getChildrenCount() const;

        void addAllChildren(const std::vector<std::shared_ptr<ChildType>> &newChildren);
        std::vector<std::shared_ptr<ChildType>> removeAllChildren();
        std::vector<std::string> getAllChildrenNames() const;
        std::vector<std::shared_ptr<ChildType>> getAllChildren() const;

    protected:
        std::weak_ptr<ParentType> getParent() const;
        void setParent(const std::weak_ptr<ParentType> &newParent);

        virtual bool onAdd(const std::shared_ptr<ChildType> &);
        virtual bool onRemove(const std::shared_ptr<ChildType> &);

        virtual bool onAddInternal(ChildType *);
        virtual bool onRemoveInternal(ChildType *);

    private:
        std::weak_ptr<ParentType> parent;
        std::vector<std::shared_ptr<ChildType>> children;
    };
}

#include "templates/HierarchicalObject.tpp"

#endif  // BKENGINE_HIERARCHICAL_OBJECT_H