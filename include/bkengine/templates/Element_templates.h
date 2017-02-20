#ifndef ELEMENT_TEMPLATES_H
#define ELEMENT_TEMPLATES_H

template <typename T> T &Element::addAnimation(const T &animation)
{
    return addAnimation<T>(std::make_shared<T>(std::move((T &) animation)));
}

template <typename T> T &Element::addAnimation(const std::shared_ptr<T>
        &animation)
{
    animations.push_back(animation);

    if (animations.size() == 1) {
        currentAnimation = 0;
    }

    return *((T *) animations.back().get());
}

template <typename T, typename... Params> T &Element::addAnimation(
    Params... params)
{
    return addAnimation<T>(std::make_shared<T>(params...));
}


template <typename T> T &Element::getAnimation(const std::string &name)
{
    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            return *((T *) animation.get());
        }
    }

    Logger::LogCritical("Element::getAnimation(const std::string &=" + name +
                        "): Animation not found");
    throw "Animation not found";
}

template <typename T> T &Element::getAnimation(
    unsigned int index)
{
    if (index < animations.size()) {
        return *((T *) animations[index].get());
    }

    Logger::LogCritical("Element::getAnimation(int=" + std::to_string(
                            index) + "): Animation not found");
    throw "Animation not found";
}


template <typename T> T &Element::getCurrentAnimation()
{
    return getAnimation<T>(currentAnimation);
}

#endif
