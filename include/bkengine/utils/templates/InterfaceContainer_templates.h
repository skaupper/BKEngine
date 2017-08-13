namespace bkengine
{
    template <typename T>
    void InterfaceContainer::setEventInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        eventInterface = std::static_pointer_cast<EventInterface>(tmpPointer);
    }

    template <typename T>
    void InterfaceContainer::setFontInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        fontInterface = std::static_pointer_cast<FontInterface>(tmpPointer);
    }

    template <typename T>
    void InterfaceContainer::setGraphicsInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        graphicsInterface = std::static_pointer_cast<GraphicsInterface>(tmpPointer);
    }

    template <typename T>
    void InterfaceContainer::setImageInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        imageInterface = std::static_pointer_cast<ImageInterface>(tmpPointer);
    }

    template <typename T>
    void InterfaceContainer::setSettingsInterface()
    {
        auto tmpPointer = std::make_shared<T>();
        settingsInterface = std::static_pointer_cast<SettingsInterface>(tmpPointer);
    }
}