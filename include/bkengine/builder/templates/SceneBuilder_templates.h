namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> SceneBuilder::build() const
    {
        struct wrapper : public T
        {
        };
        auto scene = std::static_pointer_cast<Scene>(std::make_shared<wrapper>());
        if (name.empty()) {
            throw BuilderException("You have to specify a name for the scene!");
        }
        if (parentGame == nullptr) {
            throw BuilderException("Scenes without parent game are not allowed!");
        }
        scene->name = name;
        GameUtils::addScene(parentGame, scene);
        return scene;
    }

    template <typename T>
    std::shared_ptr<T> SceneBuilder::createScene(const std::string &name, const std::shared_ptr<Game> &game)
    {
        return SceneBuilder::createBuilder().setParentGame(game).setName(name).build<T>();
    }
}