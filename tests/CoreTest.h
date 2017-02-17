#ifndef CORE_TEST_H
#define CORE_TEST_H

#include "gtest/gtest.h"

#include "Core.h"

#include "SDLMock.h"


using namespace bkengine;


class CoreTest : public ::testing::Test
{
    public:
        SDLMock *mock;

        CoreTest() : mock(nullptr)
        {
        }

        virtual ~CoreTest()
        {
        }

        virtual void SetUp()
        {
            mock = new SDLMock;
        }

        virtual void TearDown()
        {
            delete mock;
        }
};

#endif
