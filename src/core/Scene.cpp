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
    if(suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onRender();
    }
}

void Scene::_onLoop() 
{   
    bool suppress = onLoop();
    if(suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onLoop();
    }
}

void Scene::_onEvent(const Event &event)
{
    bool suppress = onEvent(event);
    if(suppress) {
        return;
    }

    for (auto &element : elements) {
        element->onEvent(event);
    }
}


void Scene::addToCollisionLayer(std::shared_ptr<Element> element, uint32_t layer)
{
    assert(element != nullptr);

    collisionLayers[layer].push_back(element);
}

void Scene::removeFromCollisionLayer(std::shared_ptr<Element> element)
{
    assert(element != nullptr);

    int layer = element->collisionLayer;

    if (collisionLayers.find(layer) == collisionLayers.end()) {
        Logger::error << "Scene::removeFromCollisionLayer(Element *=" << (unsigned long) element.get()
                      << ", uint32_t=" << layer << "): Layer not found!";
        return;
    }

    auto elementIterator = std::find(collisionLayers[layer].begin(), collisionLayers[layer].end(), element);

    if (elementIterator == collisionLayers[layer].end()) {
        Logger::error << "Scene::removeFromCollisionLayer(Element *=" << (unsigned long) element.get()
                      << ", uint32_t=" << layer << "): Element not found!";
        return;
    }

    collisionLayers[layer].erase(elementIterator);

    if (collisionLayers[layer].size() == 0) {
        collisionLayers.erase(layer);
    }
}

std::vector<std::shared_ptr<Element>> Scene::getCollisionLayer(uint32_t layer)
{
    assert(collisionLayers.find(layer) != collisionLayers.end());

    return collisionLayers[layer];
}