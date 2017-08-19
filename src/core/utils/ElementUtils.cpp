#include "core/utils/ElementUtils.h"

using namespace bkengine;


void ElementUtils::addAnimation(const std::shared_ptr<Element> &element, const std::shared_ptr<Animation> &animation)
{
    assert(element != nullptr);
    assert(animation != nullptr);

    if (hasAnimation(element, animation->name)) {
        throw NameAlreadyExistsException("Animation '" + animation->name + "' already exists in element!");
    }

    element->animations.push_back(animation);
}

bool ElementUtils::hasAnimation(const std::shared_ptr<Element> &element, const std::string &name)
{
    assert(element != nullptr);

    auto findByName = [&name](const std::shared_ptr<Animation> &animation) { return name == animation->name; };

    auto &animations = element->animations;
    auto result = std::find_if(animations.cbegin(), animations.cend(), findByName);
    return result != animations.cend();
}

std::shared_ptr<Animation> ElementUtils::removeAnimation(const std::shared_ptr<Element> &element,
                                                         const std::string &name)
{
    assert(element != nullptr);

    auto findByName = [&name](const std::shared_ptr<Animation> &animations) { return name == animations->name; };

    auto &animations = element->animations;
    auto result = std::find_if(animations.cbegin(), animations.cend(), findByName);

    if (result == animations.end()) {
        throw NameNotFoundException("No animation found with the name '" + name + "'!");
    }

    auto animation = *result;
    animations.erase(result);

    return animation;
}

std::vector<std::shared_ptr<Animation>> ElementUtils::removeAllAnimations(const std::shared_ptr<Element> &element)
{
    assert(element != nullptr);

    auto animationsCopy = element->animations;
    element->animations.clear();
    return animationsCopy;
}

std::shared_ptr<Animation> ElementUtils::getAnimation(const std::shared_ptr<Element> &element, const std::string &name)
{
    assert(element != nullptr);

    auto findByName = [&name](const std::shared_ptr<Animation> &animation) { return name == animation->name; };

    auto &animations = element->animations;
    auto result = std::find_if(animations.cbegin(), animations.cend(), findByName);

    if (result == animations.end()) {
        throw NameNotFoundException("No animation found with the name '" + name + "'!");
    }

    return *result;
}

std::vector<std::string> ElementUtils::getAnimationNames(const std::shared_ptr<Element> &element)
{
    assert(element != nullptr);

    auto getName = [](const std::shared_ptr<Animation> &animation) { return animation->name; };

    std::vector<std::string> nameVector;
    auto &animations = element->animations;

    std::transform(animations.cbegin(), animations.cend(), std::back_inserter(nameVector), getName);
    return nameVector;
}

uint32_t ElementUtils::getAnimationCount(const std::shared_ptr<Element> &element)
{
    assert(element != nullptr);

    return element->animations.size();
}

void ElementUtils::activateAnimation(const std::shared_ptr<Element> &element, const std::string &name)
{
    assert(element != nullptr);

    if (!hasAnimation(element, name)) {
        throw NameNotFoundException("No animation found with the name '" + name + "'!");
    }

    element->currentAnimation = getAnimation(element, name);
}

std::shared_ptr<Animation> ElementUtils::getCurrentAnimation(const std::shared_ptr<Element> &element)
{
    return element->currentAnimation;
}