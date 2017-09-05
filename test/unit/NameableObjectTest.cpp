#include "catch.hpp"

#include "core/NameableObject.h"

using namespace bkengine;


class NameableObjectWrapper : public bkengine::NameableObject
{
public:
    using bkengine::NameableObject::setName;
};

TEST_CASE("NameableObject")
{
    NameableObjectWrapper object;

    SECTION("no name set")
    {
        REQUIRE(object.getName().empty());
    }
    SECTION("name set once")
    {
        std::string name = "test name";
        object.setName(name);
        REQUIRE(object.getName() == name);
    }
    SECTION("name set twice")
    {
        std::string name = "test name";
        object.setName("test");
        object.setName(name);
        REQUIRE(object.getName() == name);
    }
}
