#ifndef BKENGINE_TESTS_MOCK_GRAPHICS_INTERFACE_H
#define BKENGINE_TESTS_MOCK_GRAPHICS_INTERFACE_H

#include "interfaces/GraphicsInterface.h"


class MockGraphicsInterface : public bkengine::GraphicsInterface
{
public:
    bool initWindow(bkengine::Size, const std::string &) override
    {
    }
    std::string getLastError() override
    {
    }
    void setWindowSize(bkengine::Size) override
    {
    }
    bkengine::Size getWindowSize() override
    {
    }
    void setWindowTitle(const std::string &) override
    {
    }
    std::string getWindowTitle() override
    {
    }
    void delay(uint32_t) override
    {
    }
    bool setIcon(const std::string &) override
    {
    }
    void clear() override
    {
    }
    void draw() override
    {
    }
};

#endif  // BKENGINE_TESTS_MOCK_GRAPHICS_INTERFACE_H