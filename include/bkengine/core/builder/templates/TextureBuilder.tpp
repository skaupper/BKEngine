namespace bkengine
{    
    template <typename ParentBuilder>
    ParentBuilder &TextureBuilder<ParentBuilder>::setName(const std::string &name)
    {
        TextureBuilder::name = name;
        return *this;
    }
    
    template <typename ParentBuilder>
    ParentBuilder &TextureBuilder<ParentBuilder>::setTexturePosition(const Point &position)
    {
        TextureBuilder::position = position;
        return *this;
    }
    
    template <typename ParentBuilder>
    ParentBuilder &TextureBuilder<ParentBuilder>::setTextureSize(const RelRect &size)
    {
        TextureBuilder::size = size;
        return *this;
    }
    
    template <typename ParentBuilder>
    ParentBuilder &TextureBuilder<ParentBuilder>::setRotation(double angle)
    {
        angleRadians = angle;
        return *this;
    }
    
    template <typename ParentBuilder>
    ParentBuilder &TextureBuilder<ParentBuilder>::setFlip(bool horizontal, bool vertical)
    {
        flipHorizontally = horizontal;
        flipVertically = vertical;
        return *this;
    }
    
    template <typename ParentBuilder>
    std::shared_ptr<LazyTextureContainer> TextureBuilder<ParentBuilder>::build(std::unique_ptr<Texture> texture) const
    {
        if (name.empty()) {
            throw BuilderException("You have to specify a name for the texture!");
        }

        texture->name = name;
        texture->position = position;
        texture->size = size;
        texture->angle = angleRadians;
        texture->flipHorizontally = flipHorizontally;
        texture->flipVertically = flipVertically;
        
        return std::make_shared<LazyTextureContainer>(std::move(texture));
    }
}