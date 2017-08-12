#include "core/utils/SceneUtils.h"

using namespace bkengine;


void SceneUtils::addElement(std::shared_ptr<Scene> scene, std::shared_ptr<Element> element, uint32_t collisionLayer)
{
    element->parentScene = scene;
    scene->elements.push_back(element);
    scene->collisionLayers[collisionLayer].push_back(element);
}

bool SceneUtils::hasElement(std::shared_ptr<Scene> scene, const std::string &name)
{
    auto findByName = [&name] (std::shared_ptr<Element> element) {
        return name == element->name;
    };

    auto elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);
    return result != elements.cend();
}

std::shared_ptr<Element> SceneUtils::removeElement(std::shared_ptr<Scene> scene, const std::string &name)
{
    auto findByName = [&name] (std::shared_ptr<Element> element) {
        return name == element->name;
    };

    auto elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);

    if(result == elements.cend()) {
        throw NameNotFoundException("No element found with the name '" + name + "'!");
    }

    auto element = *result;
    auto collisionLayer = scene->collisionLayers[element->collisionLayer];
    
    auto resultCollisionLayer = std::find_if(collisionLayer.cbegin(), 
                                                collisionLayer.cend(), 
                                                findByName);

    assert(resultCollisionLayer != collisionLayer.cend());

    collisionLayer.erase(resultCollisionLayer);
    elements.erase(result);

    return element;
}

void SceneUtils::moveElementToCollisionLayer(std::shared_ptr<Scene> scene, const std::string &name, uint32_t newCollisionLayer)
{
    auto findByName = [&name] (std::shared_ptr<Element> element) {
        return name == element->name;
    };

    auto elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);

    if(result == elements.cend()) {
        throw NameNotFoundException("No element found with the name '" + name + "'!");
    }

    auto element = *result;
    auto collisionLayer = scene->collisionLayers[element->collisionLayer];
    
    auto resultCollisionLayer = std::find_if(collisionLayer.cbegin(), 
                                                collisionLayer.cend(), 
                                                findByName);

    assert(resultCollisionLayer != collisionLayer.cend());

    collisionLayer.erase(resultCollisionLayer);

    element->collisionLayer = newCollisionLayer;
    scene->collisionLayers[newCollisionLayer].push_back(element);
}
