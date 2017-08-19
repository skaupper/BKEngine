#include "core/utils/AnimationUtils.h"

using namespace bkengine;


void AnimationUtils::addTexture(const std::shared_ptr<Animation> &animation, const std::shared_ptr<Texture> &texture)
{
    assert(animation != nullptr);
    assert(texture != nullptr);

    if (hasTexture(animation, texture->getName())) {
        throw NameAlreadyExistsException("Texture '" + texture->getName() + "' already exists in animation!");
    }

    animation->textures.push_back(texture);
}

bool AnimationUtils::hasTexture(const std::shared_ptr<Animation> &animation, const std::string &name)
{
    assert(animation != nullptr);

    auto findByName = [&name](const std::shared_ptr<Texture> &texture) { return name == texture->getName(); };

    auto &textures = animation->textures;
    auto result = std::find_if(textures.cbegin(), textures.cend(), findByName);
    return result != textures.cend();
}

std::shared_ptr<Texture> AnimationUtils::removeTexture(const std::shared_ptr<Animation> &animation,
                                                       const std::string &name)
{
    assert(animation != nullptr);

    auto findByName = [&name](const std::shared_ptr<Texture> &textures) { return name == textures->getName(); };

    auto &textures = animation->textures;
    auto result = std::find_if(textures.cbegin(), textures.cend(), findByName);

    if (result == textures.end()) {
        throw NameNotFoundException("No texture found with the name '" + name + "'!");
    }

    auto texture = *result;
    textures.erase(result);

    return texture;
}

std::vector<std::shared_ptr<Texture>> AnimationUtils::removeAllTextures(const std::shared_ptr<Animation> &animation)
{
    assert(animation != nullptr);

    auto texturesCopy = animation->textures;
    animation->textures.clear();
    return texturesCopy;
}

std::shared_ptr<Texture> AnimationUtils::getTexture(const std::shared_ptr<Animation> &animation,
                                                    const std::string &name)
{
    assert(animation != nullptr);

    auto findByName = [&name](const std::shared_ptr<Texture> &texture) { return name == texture->getName(); };

    auto &textures = animation->textures;
    auto result = std::find_if(textures.cbegin(), textures.cend(), findByName);

    if (result == textures.end()) {
        throw NameNotFoundException("No texture found with the name '" + name + "'!");
    }

    return *result;
}

std::vector<std::string> AnimationUtils::getTextureNames(const std::shared_ptr<Animation> &animation)
{
    assert(animation != nullptr);

    auto getName = [](const std::shared_ptr<Texture> &texture) { return texture->getName(); };

    std::vector<std::string> nameVector;
    auto &textures = animation->textures;

    std::transform(textures.cbegin(), textures.cend(), std::back_inserter(nameVector), getName);
    return nameVector;
}

uint32_t AnimationUtils::getTextureCount(const std::shared_ptr<Animation> &animation)
{
    assert(animation != nullptr);

    return animation->textures.size();
}

std::shared_ptr<Texture> AnimationUtils::getCurrentTexture(const std::shared_ptr<Animation> &animation)
{
    assert(animation->currentTextureIndex < animation->textures.size());
    return animation->textures[animation->currentTextureIndex];
}
