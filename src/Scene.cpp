#include "Scene.h"

using namespace bkengine;


Scene::Scene(Game *parentGame, const std::string &description) :
    parentGame(parentGame),
    description(description)
{
}

Scene &Scene::operator=(Scene &&scene)
{
    description = std::move(scene.description);
    elements = std::move(scene.elements);
    return *this;
}

Scene::Scene(Scene &&scene)
{
    description = std::move(scene.description);
    elements = std::move(scene.elements);
}

Scene::~Scene()
{
    clear();
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
            removeFromCollisionLayer(elements[index].get());
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
        removeFromCollisionLayer(elements[index].get());
        elements.erase(elements.begin() + index);
    } else {
        Logger::LogCritical("Scene::removeElement(int=" + std::to_string(
                                index) + "): Element not found");
        throw "Element not found";
    }
}

Element &Scene::getElement(unsigned int index)
{
    return getElement<Element>(index);
}

Element &Scene::getElement(const std::string &name)
{
    return getElement<Element>(name);
}


void Scene::setupEnvironment()
{
}

void Scene::setupElements()
{
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

bool Scene::onEvent(const Event &event)
{
    for (auto &element : elements) {
        if (!element->onEvent(event)) {
            return false;
        }
    }

    return true;
}

std::string Scene::getDescription() const
{
    return description;
}

void Scene::addToCollisionLayer(Element *element, int layer)
{
    if (layer < 0) {
        return;
    }

    collisionLayers[layer].push_back(element);
}

void Scene::removeFromCollisionLayer(Element *element)
{
    int layer = element->collisionLayer;

    if (collisionLayers.find(layer) == collisionLayers.end()) {
        Logger::LogError("Scene::removeFromCollisionLayer(Element *=" + std::to_string(
                             (unsigned long) element) + ", int=" + std::to_string(layer) +
                         "): Layer not found!");
        return;
    }

    auto elementIterator = std::find(collisionLayers[layer].begin(),
                                     collisionLayers[layer].end(), element);

    if (elementIterator == collisionLayers[layer].end()) {
        Logger::LogError("Scene::removeFromCollisionLayer(Element *=" + std::to_string(
                             (unsigned long) element) + ", int=" + std::to_string(layer) +
                         "): Element not found!");
        return;
    }

    collisionLayers[layer].erase(elementIterator);

    if (collisionLayers[layer].size() == 0) {
        collisionLayers.erase(layer);
    }
}

std::vector<Element *> Scene::getCollisionLayer(int layer)
{
    if (layer < 0) {
        return std::vector<Element *>();
    }

    return collisionLayers[layer];
}

void Scene::clear()
{
    elements.clear();
}

void Scene::deserialize(const Json::Value &obj)
{
    Serializable::deserialize(obj);
    description = obj["description"].asString();

    for (auto &element : obj["elements"]) {
        auto e = GameSerializer::deserialize<Element>(element);
        e->parentScene = this;
        e->setupEnvironment();
        Logger::LogDebug("add element " + e->getDescription());
        addElement(e);
    }
}

Json::Value Scene::serialize() const
{
    Json::Value json;
    json["description"] = description;
    json["type"] = "SCENE";
    json["elements"] = Json::arrayValue;

    for (auto element : elements) {
        json["elements"].append(element->serialize());
    }
    return json;
}
