namespace bkengine
{
    template <typename T>
    InterfaceContainer &InterfaceContainer::setEventInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        eventInterface = std::static_pointer_cast<EventInterface>(tmpPointer);
        return *this;
    }

    template <typename T>
    InterfaceContainer &InterfaceContainer::setSettingsInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        settingsInterface = std::static_pointer_cast<SettingsInterface>(tmpPointer);
        return *this;
    }

    template <typename T>
    InterfaceContainer &InterfaceContainer::setGraphicsInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        graphicsInterface = std::static_pointer_cast<GraphicsInterface>(tmpPointer);
        return *this;
    }
}