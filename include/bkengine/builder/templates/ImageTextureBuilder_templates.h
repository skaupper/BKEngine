namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> ImageTextureBuilder::build() const
    {
        auto imageInterface = game->interfaceContainer.getImageInterface();
        std::shared_ptr<ImageTexture> texture = imageInterface->renderImageFileToTexture(filePath);
        texture->size = textureSize;
        return texture;
    }
}