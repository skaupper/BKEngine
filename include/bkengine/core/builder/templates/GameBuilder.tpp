namespace bkengine
{
    template <typename T>
    GameBuilder &GameBuilder::setEventInterface()
    {
        interfaceContainer.setEventInterface<T>();
        return *this;
    }

    template <typename T>
    GameBuilder &GameBuilder::setFontInterface()
    {
        interfaceContainer.setFontInterface<T>();
        return *this;
    }

    template <typename T>
    GameBuilder &GameBuilder::setGraphicsInterface()
    {
        interfaceContainer.setGraphicsInterface<T>();
        return *this;
    }

    template <typename T>
    GameBuilder &GameBuilder::setImageInterface()
    {
        interfaceContainer.setImageInterface<T>();
        return *this;
    }

    template <typename T>
    GameBuilder &GameBuilder::setSettingsInterface()
    {
        interfaceContainer.setSettingsInterface<T>();
        return *this;
    }

    template <typename T>
    std::shared_ptr<T> GameBuilder::build() const
    {
        struct wrapper : public T
        {
        };

        auto game = std::static_pointer_cast<Game>(std::make_shared<wrapper>());
        game->interfaceContainer = interfaceContainer;
        game->setWindowSize(windowSize);
        game->setWindowTitle(windowTitle);
        game->setIconFile(iconFile);
        
        return game;
    }
}