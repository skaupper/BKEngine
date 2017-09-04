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
        
        auto element = std::static_pointer_cast<Element>(std::make_shared<wrapper>());
        element->name = std::move(name);
        element->renderBox = renderBox;
        element->collisionBox = collisionBox;

        if (parentScene != nullptr) {
            parentScene->addChild(element);
            // TODO: add element to collision layer
        }
        return element;
    }
}