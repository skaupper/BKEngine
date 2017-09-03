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
            return [name](const std::shared_ptr<ChildType> &child) {
                return child->getName() == name;
            };
        }

    public:
        void addChild(const std::shared_ptr<ChildType> &child)
        {
            if (!onAddInternal(child.get()) && !onAdd(child)) {
                children.push_back(child);
            }
        }

        std::shared_ptr<ChildType> removeChildByName(const std::string &name)
        {
            auto it = std::find(children.begin(), children.end(), getNamePredicate(name));
            if(it == children.end()) {
                throw NameNotFoundException("No child object '" + name + "' exists.");
            }

            if (!onRemoveInternal(it->get()) && !onRemove(*it)) {
                children.erase(it);
                return *it;
            }

            return nullptr;
        }

        bool hasChild(const std::string &name) const
        {
            return std::find(children.cbegin(), children.cend(), getNamePredicate(name)) != children.cend();
        }

        std::shared_ptr<ChildType> getChildByIndex(uint32_t index) const
        {
            if(index < 0 || index >= children.size()) {
                throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
            }

            return children[index];
        }

        uint32_t getChildIndex(const std::string &name) 
        {
            auto it = std::find(children.cbegin(), children.cend(), getNamePredicate(name));
            if(it == children.cend()) {
                throw NameNotFoundException("No child object '" + name + "' exists.");
            }

            return std::distance(children.cbegin(), it);   
        }

        std::shared_ptr<ChildType> getChildByName(const std::string &name) const
        {
            auto it = std::find(children.cbegin(), children.cend(), getNamePredicate(name));
            if(it == children.cend()) {
                throw NameNotFoundException("No child object '" + name + "' exists.");
            }

            return *it;
        }

        std::string getChildNameByIndex(uint32_t index) const
        {
            if(index < 0 || index >= children.size()) {
                throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
            }

            return children[index]->getName();
        }

        std::shared_ptr<ChildType> removeChildByIndex(uint32_t index)
        {
            if(index < 0 || index >= children.size()) {
                throw IndexOutOfRangeException("No element found at index " + std::to_string(index));
            }

            auto it = std::advance(children.begin(), index);

            if (!onRemoveInternal(it->get()) && !onRemove(*it)) {
                children.erase(it);
                return *it;
            }

            return nullptr;
        }

        uint32_t getChildrenCount() const
        {
            return children.size();
        }

        std::vector<std::string> getAllChildrenNames() const
        {
            auto extractNames = [](const std::shared_ptr<ChildType> &child) {
                return child->getName();
            };

            std::vector<std::string> allNames;

            std::transform(children.cbegin(), children.cend(), std::back_inserter(allNames), extractNames);
            return allNames;
        }

        void addAllChildren(const std::vector<std::shared_ptr<ChildType>> &newChildren)
        {
            std::for_each(newChildren.cbegin(), newChildren.cend(), addChild);
        }

        std::vector<std::shared_ptr<ChildType>> removeAllChildren()
        {
            std::vector<std::shared_ptr<ChildType>> removedChildren;

            for(auto i = children.size() - 1; i >= 0; --i) {
                auto removedChild = removeChildByIndex(i);
                if(removedChild) {
                    removedChildren.push_back(removedChild);
                }
            }

            return removedChildren;
        }

    protected:
        std::weak_ptr<ParentType> getParent() const
        {
            return parent;
        }

        void setParent(const std::weak_ptr<ParentType> &newParent)
        {
            parent = newParent;
        }


        virtual bool onAdd(const std::shared_ptr<ChildType> &)
        {
        }

        virtual bool onRemove(const std::shared_ptr<ChildType> &)
        {
        }


        virtual bool onAddInternal(ChildType *)
        {
        }
        virtual bool onRemoveInternal(ChildType *)
        {
        }

    private:
        std::weak_ptr<ParentType> parent;
        std::vector<std::shared_ptr<ChildType>> children;
    };
}

#endif  // BKENGINE_HIERARCHICAL_OBJECT_H