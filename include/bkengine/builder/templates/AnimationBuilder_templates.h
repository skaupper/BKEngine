namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> AnimationBuilder::build() const
    {
        struct wrapper : public T
        {
        };
        auto animation = std::static_pointer_cast<Animation>(std::make_shared<wrapper>());
        animation->name = name;
        animation->framesPerTexture = framesPerTexture;
        return animation;
    }
}