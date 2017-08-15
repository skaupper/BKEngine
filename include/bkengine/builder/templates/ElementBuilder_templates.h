namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> ElementBuilder::build() const
    {
        struct wrapper : public T
        {
        };

        if (name.empty()) {
            throw BuilderException("You have to specify a name for the scene!");
        }
        if (parentScene == nullptr) {
            throw BuilderException("Elements without parent scene are not allowed!");
        }

        auto element = std::static_pointer_cast<Element>(std::make_shared<wrapper>());
        element->name = std::move(name);
        element->renderBox = renderBox;
        element->collisionBox = collisionBox;

        // TODO: maybe implement the option to build without parentScene?
        SceneUtils::addElement(parentScene, element, collisionLayer);
        return element;
    }
}