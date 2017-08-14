namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> ElementBuilder::build() const
    {
        struct wrapper : public T
        {
        };
        auto element = std::make_shared<wrapper>();
        if (name.empty()) {
            throw BuilderException("You have to specify a name for the scene!");
        }
        if (parentScene == nullptr) {
            throw BuilderException("Elements without parent scene are not allowed!");
        }
        element->name = std::move(name);
        element->renderBox = renderBox;
        element->collisionBox = collisionBox;
        SceneUtils::addElement(parentScene, element, collisionLayer);
        return element;
    }
}