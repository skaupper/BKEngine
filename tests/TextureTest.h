#ifndef TEXTURE_TEST_H
#define TEXTURE_TEST_H

#include "gtest/gtest.h"

#include "Texture.h"

#include "SDLMock.h"


using namespace bkengine;


class TextureMock : public Texture
{
    public:
        static int initCount;
        static int destructCount;

        TextureMock()
        {
            initCount++;
        }

        virtual ~TextureMock()
        {
            if (texture) {
                destructCount++;
            }

            imageCache.clear();
            textCache.clear();
        }
};

class TextureTest : public ::testing::Test
{
    public:
        SDLMock *mock;

        TextureTest() : mock(nullptr)
        {
        }

        virtual ~TextureTest()
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
