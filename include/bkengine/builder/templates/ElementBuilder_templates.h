namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> ElementBuilder::build() const
    {
        struct wrapper : public T
        {
        };
        auto element = std::make_shared<wrapper>();
        element->name = std::move(name);
        element->parentScene = parentScene;
        element->renderBox = renderBox;
        element->collisionBox = collisionBox;
        return element;
    }
}