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

void Scene::_onRender()
{
    bool suppress = onRender();
    if (suppress) {
        return;
    }

    for (auto &element : getAllChildren()) {
        element->onRender();
    }
}

void Scene::_onLoop()
{
    bool suppress = onLoop();
    if (suppress) {
        return;
    }

    for (auto &element : getAllChildren()) {
        element->onLoop();
    }
}

void Scene::_onEvent(const Event &event)
{
    bool suppress = onEvent(event);
    if (suppress) {
        return;
    }

    for (auto &element : getAllChildren()) {
        element->onEvent(event);
    }
}