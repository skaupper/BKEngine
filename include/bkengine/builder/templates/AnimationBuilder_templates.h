namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> AnimationBuilder::build() const
    {
        struct wrapper : public T
        {
        };

        if (name.empty()) {
            throw BuilderException("You have to specify a name for the element!");
        }
        if (parentElement == nullptr) {
            throw BuilderException("Animations without parent element are not allowed!");
        }


        auto animation = std::static_pointer_cast<Animation>(std::make_shared<wrapper>());
        animation->name = name;
        animation->framesPerTexture = framesPerTexture;

        ElementUtils::addAnimation(parentElement, animation);
        return animation;
    }
}