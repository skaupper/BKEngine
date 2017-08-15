#include "core/utils/SceneUtils.h"

using namespace bkengine;


void SceneUtils::addElement(const std::shared_ptr<Scene> &scene,
                            const std::shared_ptr<Element> &element,
                            uint32_t collisionLayer)
{
    assert(scene != nullptr);
    assert(element != nullptr);

    if (hasElement(scene, element->name)) {
        throw NameAlreadyExistsException("Element '" + element->name + "' already exists in scene!");
    }

    element->parentScene = scene;
    element->collisionLayer = collisionLayer;
    scene->elements.push_back(element);
    scene->collisionLayers[collisionLayer].push_back(element);
}

bool SceneUtils::hasElement(const std::shared_ptr<Scene> &scene, const std::string &name)
{
    assert(scene != nullptr);

    auto findByName = [&name](const std::shared_ptr<Element> &element) { return name == element->name; };

    auto &elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);
    return result != elements.cend();
}

std::shared_ptr<Element> SceneUtils::removeElement(const std::shared_ptr<Scene> &scene, const std::string &name)
{
    assert(scene != nullptr);

    auto findByName = [&name](const std::shared_ptr<Element> &element) { return name == element->name; };

    auto &elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);

    if (result == elements.cend()) {
        throw NameNotFoundException("No element found with the name '" + name + "'!");
    }

    auto element = *result;
    auto &collisionLayer = scene->collisionLayers[element->collisionLayer];

    auto resultCollisionLayer = std::find_if(collisionLayer.cbegin(), collisionLayer.cend(), findByName);

    assert(resultCollisionLayer != collisionLayer.cend());

    collisionLayer.erase(resultCollisionLayer);
    elements.erase(result);

    return element;
}

std::vector<std::shared_ptr<Element>> SceneUtils::removeAllElements(const std::shared_ptr<Scene> &scene)
{
    assert(scene != nullptr);

    auto elementsCopy = scene->elements;
    scene->elements.clear();
    return elementsCopy;
}

std::shared_ptr<Element> SceneUtils::getElement(const std::shared_ptr<Scene> &scene, const std::string &name)
{
    assert(scene != nullptr);

    auto findByName = [&name](const std::shared_ptr<Element> &element) { return name == element->name; };

    auto &elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);

    if (result == elements.cend()) {
        throw NameNotFoundException("No element found with the name '" + name + "'!");
    }

    return *result;
}

std::vector<std::string> SceneUtils::getElementNames(const std::shared_ptr<Scene> &scene)
{
    assert(scene != nullptr);

    auto getName = [](const std::shared_ptr<Element> &element) { return element->name; };

    std::vector<std::string> names;
    auto &elements = scene->elements;
    std::transform(elements.cbegin(), elements.cend(), std::back_inserter(names), getName);
    return names;
}

uint32_t SceneUtils::getElementCount(const std::shared_ptr<Scene> &scene)
{
    assert(scene != nullptr);

    return scene->elements.size();
}

std::vector<std::shared_ptr<Element>> SceneUtils::getCollisionLayer(const std::shared_ptr<Scene> &scene,
                                                                    uint32_t collisionLayer)
{
    assert(scene != nullptr);

    return scene->collisionLayers[collisionLayer];
}

std::vector<std::shared_ptr<Element>> SceneUtils::getCollisionLayerOfElement(const std::shared_ptr<Scene> &scene,
                                                                             const std::shared_ptr<Element> &element)
{
    assert(scene != nullptr);
    assert(element != nullptr);

    auto otherThanElement = [&element](const std::shared_ptr<Element> &elementInLayer) {
        return element != elementInLayer;
    };
    auto &collisionLayer = scene->collisionLayers[element->collisionLayer];

    std::vector<std::shared_ptr<Element>> elementsOtherThanElement;

    std::copy_if(
        collisionLayer.cbegin(), collisionLayer.cend(), std::back_inserter(elementsOtherThanElement), otherThanElement);

    return elementsOtherThanElement;
}

void SceneUtils::moveElementToCollisionLayer(const std::shared_ptr<Scene> &scene,
                                             const std::string &name,
                                             uint32_t newCollisionLayer)
{
    assert(scene != nullptr);

    auto findByName = [&name](const std::shared_ptr<Element> &element) { return name == element->name; };

    auto &elements = scene->elements;
    auto result = std::find_if(elements.cbegin(), elements.cend(), findByName);

    if (result == elements.cend()) {
        throw NameNotFoundException("No element found with the name '" + name + "'!");
    }

    auto element = *result;
    auto &collisionLayer = scene->collisionLayers[element->collisionLayer];

    auto resultCollisionLayer = std::find_if(collisionLayer.cbegin(), collisionLayer.cend(), findByName);

    assert(resultCollisionLayer != collisionLayer.cend());

    collisionLayer.erase(resultCollisionLayer);

    element->collisionLayer = newCollisionLayer;
    scene->collisionLayers[newCollisionLayer].push_back(element);
}
