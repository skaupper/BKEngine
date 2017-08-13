#include "catch.hpp"

#include <cstdio>
#include <fstream>
#include <memory>

#include "interfaces/impl/INISettingsInterface.h"

using namespace bkengine;


TEST_CASE("INISettingsInterface init")
{
    std::shared_ptr<SettingsInterface> settings = std::make_shared<INISettingsInterface>();
    settings->init();

    SECTION("loadFromFile")
    {
        std::string fileName = "tmp.settingsinterface.test.1.ini";
        std::ofstream file(fileName);

        if (!file.good()) {
            FAIL("Unable to open temporary file!");
        }

        SECTION("valid content")
        {
            std::string fileContent = "nosection=1234\n"
                                      "key=value\n"
                                      "[section1]\n"
                                      "bkengine=bk\n";
            file << fileContent;
            file.close();
            SECTION("load from existing file")
            {
                settings->loadFromFile(fileName);
                REQUIRE(settings->hasValue("nosection"));
                REQUIRE(settings->hasValue("key"));
                REQUIRE(settings->hasValue("section1.bkengine"));
                REQUIRE(settings->count() == 3);
            }
            SECTION("load from non existent file")
            {
                settings->loadFromFile("non existent file...");
                REQUIRE(settings->count() == 0);
            }
        }

        SECTION("invalid content")
        {
            std::string fileContent = "nosection1234\n"
                                      "key=value\n"
                                      "[section1\n"
                                      "bkengine=bk\n";
            file << fileContent;
            file.close();

            settings->loadFromFile(fileName);
            REQUIRE(settings->hasValue("key"));
            REQUIRE(settings->hasValue("bkengine"));
            REQUIRE(settings->count() == 2);
        }

        std::remove(fileName.c_str());
    }

    SECTION("create")
    {
        SECTION("key without dot")
        {
            REQUIRE(settings->count() == 0);
            settings->create("nosection", "value");
            REQUIRE(settings->get("nosection") == "value");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with 1 dot")
        {
            REQUIRE(settings->count() == 0);
            settings->create("section.key", "value");
            REQUIRE(settings->get("section.key") == "value");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with 2 dot")
        {
            REQUIRE(settings->count() == 0);
            settings->create("section.key.level2", "value");
            REQUIRE(settings->get("section.key.level2") == "value");
            REQUIRE(settings->count() == 1);
        }
        SECTION("empty value")
        {
            REQUIRE(settings->count() == 0);
            settings->create("section.key.level2", "");
            REQUIRE(settings->count() == 1);
        }
        SECTION("already existing key")
        {
            REQUIRE(settings->count() == 0);
            settings->create("section.key.level2", "value");
            REQUIRE(settings->get("section.key.level2") == "value");
            REQUIRE(settings->count() == 1);
            settings->create("section.key.level2", "value2");
            REQUIRE(settings->get("section.key.level2") == "value");
            REQUIRE(settings->count() == 1);
        }
    }

    SECTION("saveToFile")
    {
        std::string fileName = "tmp.settingsinterface.test.3.ini";
        SECTION("save and load back")
        {
            settings->create("nosection", "value1");
            settings->create("section.key1", "bkengine");
            settings->create("section2.testKey.nestedkey", "testvalue");
            settings->saveToFile(fileName);
            REQUIRE(settings->count() == 3);
            settings->create("extrakey", "0");
            REQUIRE(settings->count() == 4);
            settings->loadFromFile(fileName);
            REQUIRE(settings->count() == 3);
            REQUIRE(settings->get("nosection") == "value1");
            REQUIRE(settings->get("section.key1") == "bkengine");
            REQUIRE(settings->get("section2.testKey.nestedkey") == "testvalue");
        }
        SECTION("save to already opened file")
        {
            // TODO: reproduce a failing file opening?
        }
    }

    SECTION("get")
    {
        SECTION("key without section")
        {
            settings->create("nosection", "1234");
            REQUIRE(settings->get("nosection") == "1234");
        }
        SECTION("key with section")
        {
            settings->create("testsection.testkey", "4321");
            REQUIRE(settings->get("testsection.testkey") == "4321");
        }
        SECTION("key with section and dot in it")
        {
            settings->create("testsection.testkey.name", "name");
            REQUIRE(settings->get("testsection.testkey.name") == "name");
        }
        SECTION("key without section which does not exist")
        {
            std::string errorCase = "";
            REQUIRE(settings->count() == 0);
            REQUIRE(settings->get("sec") == errorCase);
        }
        SECTION("key with section which does not exist")
        {
            std::string errorCase = "";
            REQUIRE(settings->count() == 0);
            REQUIRE(settings->get("key1.sec") == errorCase);
        }
    }

    SECTION("remove")
    {
        SECTION("key without section")
        {
            settings->create("nosection", "1234");
            REQUIRE(settings->count() == 1);
            REQUIRE(settings->remove("nosection") == "1234");
            REQUIRE(settings->count() == 0);
        }
        SECTION("key with section")
        {
            settings->create("section.key1", "2424");
            REQUIRE(settings->count() == 1);
            REQUIRE(settings->remove("section.key1") == "2424");
            REQUIRE(settings->count() == 0);
        }
        SECTION("key with section and dot in it")
        {
            settings->create("section.key1.dot", "4242");
            REQUIRE(settings->count() == 1);
            REQUIRE(settings->remove("section.key1.dot") == "4242");
            REQUIRE(settings->count() == 0);
        }
        SECTION("key without section which does not exist")
        {
            std::string errorCase = "";
            REQUIRE(settings->count() == 0);
            REQUIRE(settings->remove("sec") == errorCase);
        }
        SECTION("key with section which does not exist")
        {
            std::string errorCase = "";
            REQUIRE(settings->count() == 0);
            REQUIRE(settings->remove("key1.sec") == errorCase);
        }
    }

    SECTION("hasValue")
    {
        SECTION("key without section")
        {
            settings->create("nosection", "1234");
            REQUIRE(settings->hasValue("nosection"));
        }
        SECTION("key with section")
        {
            settings->create("testsection.testkey", "4321");
            REQUIRE(settings->hasValue("testsection.testkey"));
        }
        SECTION("key with section and dot in it")
        {
            settings->create("testsection.testkey.name", "name");
            REQUIRE(settings->hasValue("testsection.testkey.name"));
        }
        SECTION("key without section which does not exist")
        {
            settings->create("sec.key", "123");
            REQUIRE_FALSE(settings->hasValue("sec"));
        }
        SECTION("key with section which does not exist")
        {
            settings->create("key1", "0");
            REQUIRE_FALSE(settings->hasValue("key1.sec"));
        }
    }

    SECTION("change")
    {
        SECTION("key without section")
        {
            settings->create("nosection", "1234");
            REQUIRE(settings->get("nosection") == "1234");
            settings->change("nosection", "4321");
            REQUIRE(settings->get("nosection") == "4321");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with section")
        {
            settings->create("testsection.testkey", "1234");
            REQUIRE(settings->get("testsection.testkey") == "1234");
            settings->change("testsection.testkey", "4321");
            REQUIRE(settings->get("testsection.testkey") == "4321");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with section and dot in it")
        {
            settings->create("testsection.testkey.name", "name");
            REQUIRE(settings->get("testsection.testkey.name") == "name");
            settings->change("testsection.testkey.name", "54779");
            REQUIRE(settings->get("testsection.testkey.name") == "54779");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key without section which does not exist")
        {
            settings->change("sec", "123");
            REQUIRE_FALSE(settings->hasValue("sec"));
        }
        SECTION("key with section which does not exist")
        {
            settings->change("key", "0");
            REQUIRE_FALSE(settings->hasValue("key.sec"));
        }
    }

    SECTION("count")
    {
        SECTION("key without section")
        {
            REQUIRE(settings->count() == 0);
            settings->create("nosection", "1234");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with section")
        {
            REQUIRE(settings->count() == 0);
            settings->create("nosection.section", "1234");
            REQUIRE(settings->count() == 1);
        }
        SECTION("key with section and dot in it")
        {
            REQUIRE(settings->count() == 0);
            settings->create("nosection.section.key", "1234");
            REQUIRE(settings->count() == 1);
        }
        SECTION("more complex construct")
        {
            settings->create("sec", "123");
            settings->create("sec.key1", "123");
            settings->create("sec.key2", "123");
            settings->create("s", "123");
            settings->create("se.key1", "123");
            REQUIRE(settings->count() == 5);
        }
    }
}
