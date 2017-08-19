#include "core/Scene.h"

using namespace bkengine;


bool Scene::onRender()
{
    return false;
}

bool Scene::onLoop()
{
    return false;
}

bool Scene::onEvent(const Event &event)
{
    return false;
}

std::string Scene::getName() const
{
    return name;
}

void Scene::setName(const std::string &name)
{
    Scene::name = name;
}

void Scene::_onRender()
{
    bool suppress = onRender();
    if (suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onRender();
    }
}

void Scene::_onLoop()
{
    bool suppress = onLoop();
    if (suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onLoop();
    }
}

void Scene::_onEvent(const Event &event)
{
    bool suppress = onEvent(event);
    if (suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onEvent(event);
    }
}