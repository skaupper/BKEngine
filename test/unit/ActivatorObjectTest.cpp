#include "catch.hpp"

#include "core/ActivatorObject.h"
#include "exceptions/NameAlreadyExistsException.h"
#include "exceptions/IndexOutOfRangeException.h"

using namespace bkengine;


class ChildObject : public NameableObject, public ActivatableObject
{
public:
    using NameableObject::setName;
};

class ParentObject 
    : public ActivatorObject<ChildObject, ParentObject>
{
public:
    using HierarchicalObject<ChildObject, ParentObject>::getParent;
};



TEST_CASE("ActivatorObject")
{
    ParentObject object;
    auto obj1 = std::make_shared<ChildObject>();
    obj1->setName("obj1");
    auto obj2 = std::make_shared<ChildObject>();
    obj2->setName("obj2");

    object.addChild(obj1);
    object.addChild(obj2);


    SECTION("activate")
    {
        SECTION("non-existent child")
        {
            REQUIRE_THROWS_AS(object.activate("obj3"), NameNotFoundException);
        }
        SECTION("existing child")
        {
            std::shared_ptr<ChildObject> activated;
            
            REQUIRE_NOTHROW(activated = object.activate("obj1"));
            REQUIRE(activated == obj1);
            REQUIRE(object.getActivatedObject() == obj1);
            REQUIRE(object.getActivatedIndex() == 0);

            REQUIRE_NOTHROW(activated = object.activate("obj2"));
            REQUIRE(activated == obj2);
            REQUIRE(object.getActivatedObject() == obj2);
            REQUIRE(object.getActivatedIndex() == 1);
        }
    }

    SECTION("activateByIndex")
    {
        SECTION("non-existent index")
        {
            REQUIRE_THROWS_AS(object.activateByIndex(2), IndexOutOfRangeException);
        }
        SECTION("existing index")
        {
            std::shared_ptr<ChildObject> activated;
            
            REQUIRE_NOTHROW(activated = object.activateByIndex(0));
            REQUIRE(activated == obj1);
            REQUIRE(object.getActivatedObject() == obj1);
            REQUIRE(object.getActivatedIndex() == 0);

            REQUIRE_NOTHROW(activated = object.activateByIndex(1));
            REQUIRE(activated == obj2);
            REQUIRE(object.getActivatedObject() == obj2);
            REQUIRE(object.getActivatedIndex() == 1);
        }
    }
}
