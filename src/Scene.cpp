#include "Scene.h"

using namespace bkengine;


Scene::Scene(const std::string &name)
{
    Scene::name = name;
}

Scene &Scene::operator=(Scene &&scene)
{
    name = std::move(scene.name);
    elements = std::move(scene.elements);
    return *this;
}

Scene::Scene(Scene &&scene)
{
    name = std::move(scene.name);
    elements = std::move(scene.elements);
}

Scene::~Scene()
{
    elements.clear();
}

bool Scene::hasElement(unsigned int index) const
{
    return index < elements.size();
}

bool Scene::hasElement(const std::string &name) const
{
    for (auto &element : elements) {
        if (element->getDescription() == name) {
            return true;
        }
    }

    return false;
}

void Scene::removeElement(const std::string &name)
{
    int index = 0;

    for (auto &element : elements) {
        if (element->getDescription() == name) {
            elements.erase(elements.begin() + index);
            return;
        }

        index++;
    }

    Logger::LogCritical("Scene::removeElement(const std::string &=" + name +
                        "): Element not found");
    throw "Element not found";
}

void Scene::removeElement(unsigned int index)
{
    if (index < elements.size()) {
        elements.erase(elements.begin() + index);
    } else {
        Logger::LogCritical("Scene::removeElement(int=" + std::to_string(
                                index) + "): Element not found");
        throw "Element not found";
    }
}

void Scene::onRender()
{
    for (auto &element : elements) {
        element->onRender();
    }
}

void Scene::onLoop()
{
    for (auto &element : elements) {
        element->onLoop();
    }
}

int Scene::onEvent(SDL_Event *event)
{
    for (auto &element : elements) {
        int status = element->onEvent(event);

        if (status != 0) {
            return status;
        }
    }

    return 0;
}

std::string Scene::getName() const
{
    return name;
}
