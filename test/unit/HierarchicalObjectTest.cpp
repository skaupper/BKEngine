#include "catch.hpp"

#include "core/HierarchicalObject.h"
#include "exceptions/NameAlreadyExistsException.h"
#include "exceptions/IndexOutOfRangeException.h"

using namespace bkengine;


class NameableObjectWrapper : public NameableObject
{
public:
    using NameableObject::setName;
};

class HierarchicalObjectWrapper 
    : public HierarchicalObject<NameableObjectWrapper, HierarchicalObjectWrapper>
{
public:
    using HierarchicalObject<NameableObjectWrapper, HierarchicalObjectWrapper>::getParent;
};



TEST_CASE("HierarchicalObject")
{
    HierarchicalObjectWrapper object;
    auto obj1 = std::make_shared<NameableObjectWrapper>();
    obj1->setName("obj1");
    auto obj2 = std::make_shared<NameableObjectWrapper>();
    obj2->setName("obj2");
    auto obj3 = std::make_shared<NameableObjectWrapper>();
    obj3->setName("obj3");

    SECTION("empty object")
    {
        REQUIRE(object.getChildrenCount() == 0);
        REQUIRE(object.getAllChildrenNames().size() == 0);
        REQUIRE(object.getParent().expired());
    }

    SECTION("addChild")
    {
        SECTION("add one child")
        {
            REQUIRE(object.getChildrenCount() == 0);
            object.addChild(obj1);
            REQUIRE(object.getChildrenCount() == 1);
        }
        SECTION("add same child twice")
        {
            REQUIRE(object.getChildrenCount() == 0);
            object.addChild(obj1);
            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE_THROWS_AS(object.addChild(obj1), NameAlreadyExistsException);
            REQUIRE(object.getChildrenCount() == 1);
        }
        SECTION("add two different named children")
        {
            REQUIRE(object.getChildrenCount() == 0);
            object.addChild(obj1);
            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE_NOTHROW(object.addChild(obj2));
            REQUIRE(object.getChildrenCount() == 2);
        }
    }

    SECTION("hasChild")
    {
        SECTION("check for non-existent child")
        {
            REQUIRE_FALSE(object.hasChild("arbitrary name"));
            REQUIRE_FALSE(object.hasChild(obj1->getName()));
        }
        SECTION("check for existing child")
        {
            REQUIRE_FALSE(object.hasChild(obj1->getName()));
            object.addChild(obj1);
            REQUIRE(object.hasChild(obj1->getName()));
        }
        SECTION("add two different children and check if they exist")
        {
            REQUIRE_FALSE(object.hasChild(obj1->getName()));
            REQUIRE_FALSE(object.hasChild(obj2->getName()));

            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE_FALSE(object.hasChild(obj3->getName()));
            REQUIRE(object.hasChild(obj1->getName()));
            REQUIRE(object.hasChild(obj2->getName()));
        }
    }

    SECTION("hasChildIndex")
    {
        SECTION("check for non-existent index")
        {
            REQUIRE_FALSE(object.hasChildIndex(0));
            REQUIRE_FALSE(object.hasChildIndex(1));
        }
        SECTION("check for existing index")
        {
            REQUIRE_FALSE(object.hasChildIndex(0));
            object.addChild(obj1);
            REQUIRE(object.hasChildIndex(0));
        }
        SECTION("add two different children and check if their indices exist")
        {
            REQUIRE_FALSE(object.hasChildIndex(0));
            REQUIRE_FALSE(object.hasChildIndex(1));

            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE_FALSE(object.hasChildIndex(2));
            REQUIRE(object.hasChildIndex(0));
            REQUIRE(object.hasChildIndex(1));
        }
    }

    SECTION("removeChildByName")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.removeChildByName(obj1->getName()), NameNotFoundException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            auto removedChild = object.removeChildByName(obj1->getName());
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(obj1 == removedChild);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            auto removedChild = object.removeChildByName(obj1->getName());
            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(obj1 == removedChild);
            removedChild = object.removeChildByName(obj2->getName());
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(obj2 == removedChild);
        }
        SECTION("same children twice")
        {
            object.addChild(obj1);
            object.removeChildByName(obj1->getName());
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE_THROWS_AS(object.removeChildByName(obj1->getName()), NameNotFoundException);
        }
    }

    SECTION("removeChildByIndex")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.removeChildByIndex(0), IndexOutOfRangeException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            auto removedChild = object.removeChildByIndex(0);
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(obj1 == removedChild);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            auto removedChild = object.removeChildByIndex(0);
            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(obj1 == removedChild);
            removedChild = object.removeChildByIndex(0);
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(obj2 == removedChild);
        }
        SECTION("last index twice")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            auto removedChild = object.removeChildByIndex(1);
            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(obj2 == removedChild);
            REQUIRE_THROWS_AS(object.removeChildByIndex(1), IndexOutOfRangeException);
            REQUIRE(object.getChildrenCount() == 1);
        }
    }
    
    SECTION ("getChildIndexByName")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.getChildIndexByName(obj1->getName()), NameNotFoundException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(object.getChildIndexByName(obj1->getName()) == 0);
            REQUIRE_THROWS_AS(object.getChildIndexByName(obj2->getName()), NameNotFoundException);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            REQUIRE(object.getChildIndexByName(obj1->getName()) == 0);
            REQUIRE(object.getChildIndexByName(obj2->getName()) == 1);
            REQUIRE_THROWS_AS(object.getChildIndexByName(obj3->getName()), NameNotFoundException);
        }        
    }
        
    SECTION ("getChildNameByIndex")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.getChildNameByIndex(0), IndexOutOfRangeException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(object.getChildNameByIndex(0) == obj1->getName());
            REQUIRE_THROWS_AS(object.getChildNameByIndex(1), IndexOutOfRangeException);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            REQUIRE(object.getChildNameByIndex(0) == obj1->getName());
            REQUIRE(object.getChildNameByIndex(1) == obj2->getName());
            REQUIRE_THROWS_AS(object.getChildNameByIndex(2), IndexOutOfRangeException);
        }        
    }

    SECTION ("getChildByName")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.getChildByName(obj1->getName()), NameNotFoundException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(object.getChildByName(obj1->getName()) == obj1);
            REQUIRE_THROWS_AS(object.getChildByName(obj2->getName()), NameNotFoundException);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            REQUIRE(object.getChildByName(obj1->getName()) == obj1);
            REQUIRE(object.getChildByName(obj2->getName()) == obj2);
            REQUIRE_THROWS_AS(object.getChildByName(obj3->getName()), NameNotFoundException);
        }        
    }
        
    SECTION ("getChildByIndex")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.getChildByIndex(0), IndexOutOfRangeException);
        }
        SECTION("existing child")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(object.getChildByIndex(0) == obj1);
            REQUIRE_THROWS_AS(object.getChildNameByIndex(1), IndexOutOfRangeException);
        }
        SECTION("two children")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            REQUIRE(object.getChildByIndex(0) == obj1);
            REQUIRE(object.getChildByIndex(1) == obj2);
            REQUIRE_THROWS_AS(object.getChildNameByIndex(2), IndexOutOfRangeException);
        }        
    }

    /*
    SECTION("getChildrenCount")
    {
        // don't know how to test this independently :D
        // gets tested together with other functions (see above)
    }
    */

    SECTION("addAllChildren")
    {
        SECTION("add empty vector to empty object")
        {
            REQUIRE(object.getChildrenCount() == 0);
            object.addAllChildren({});
            REQUIRE(object.getChildrenCount() == 0);
        }
        SECTION("add empty vector to non-empty object")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            object.addAllChildren({});
            REQUIRE(object.getChildrenCount() == 2);
        }
        SECTION("add non-empty vector to empty object")
        {
            REQUIRE(object.getChildrenCount() == 0);
            object.addAllChildren({obj1, obj2});
            REQUIRE(object.getChildrenCount() == 2);
        }
        SECTION("add non-empty vector to non-empty object")
        {
            object.addChild(obj3);

            REQUIRE(object.getChildrenCount() == 1);
            object.addAllChildren({obj1, obj2});
            REQUIRE(object.getChildrenCount() == 3);
        }
        SECTION("add the same object twice")
        {
            // TODO: is this intendet behaviour?
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE_THROWS_AS(object.addAllChildren({obj1, obj1, obj2}), NameAlreadyExistsException);
        }
    }

    SECTION("removeAllChildren")
    {
        SECTION("nothing to be removed")
        {
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(object.removeAllChildren().size() == 0);
            REQUIRE(object.getChildrenCount() == 0);
        }
        SECTION("one child to be removed")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            REQUIRE(object.removeAllChildren().size() == 1);
            REQUIRE(object.getChildrenCount() == 0);
        }
        SECTION("two children to be removed")
        {
            object.addChild(obj1);
            object.addChild(obj2);
            
            REQUIRE(object.getChildrenCount() == 2);
            REQUIRE(object.removeAllChildren().size() == 2);
            REQUIRE(object.getChildrenCount() == 0);
        }
    }

    SECTION("getAllChildrenNames")
    {
        SECTION("no child added")
        {
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(object.getAllChildrenNames().size() == 0);
        }
        SECTION("one scene added")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            auto scenes = object.getAllChildrenNames();
            REQUIRE(scenes.size() == 1);
            REQUIRE(scenes.at(0) == obj1->getName());
        }
        SECTION("two scenes added")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            auto scenes = object.getAllChildrenNames();
            REQUIRE(scenes.size() == 2);
            REQUIRE(scenes.at(0) == obj1->getName());
            REQUIRE(scenes.at(1) == obj2->getName());
        }
    }

    SECTION("getAllChildren")
    {
        SECTION("no child added")
        {
            REQUIRE(object.getChildrenCount() == 0);
            REQUIRE(object.getAllChildren().size() == 0);
        }
        SECTION("one scene added")
        {
            object.addChild(obj1);

            REQUIRE(object.getChildrenCount() == 1);
            auto scenes = object.getAllChildren();
            REQUIRE(scenes.size() == 1);
            REQUIRE(scenes.at(0) == obj1);
        }
        SECTION("two scenes added")
        {
            object.addChild(obj1);
            object.addChild(obj2);

            REQUIRE(object.getChildrenCount() == 2);
            auto scenes = object.getAllChildren();
            REQUIRE(scenes.size() == 2);
            REQUIRE(scenes.at(0) == obj1);
            REQUIRE(scenes.at(1) == obj2);
        }
    }
}