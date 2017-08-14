namespace bkengine
{
    template <typename T>
    std::shared_ptr<T> TextTextureBuilder::build() const
    {
        auto fontInterface = game->interfaceContainer.getFontInterface();
        std::shared_ptr<Texture> texture = fontInterface->renderFontToTexture(text, font, quality);
        texture->size = textureSize;
        return texture;
    }
}