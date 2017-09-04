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

        auto animation = std::static_pointer_cast<Animation>(std::make_shared<wrapper>());
        animation->name = name;
        animation->framesPerTexture = framesPerTexture;

        if (parentElement != nullptr) {
            parentElement->addChild(animation);
        }
        return animation;
    }
}