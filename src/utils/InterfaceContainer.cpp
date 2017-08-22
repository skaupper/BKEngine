#include "utils/InterfaceContainer.h"

using namespace bkengine;


std::shared_ptr<EventInterface> InterfaceContainer::getEventInterface() const
{
    return eventInterface;
}

std::shared_ptr<FontInterface> InterfaceContainer::getFontInterface() const
{
    return fontInterface;
}

std::shared_ptr<GraphicsInterface> InterfaceContainer::getGraphicsInterface() const
{
    return graphicsInterface;
}

std::shared_ptr<ImageInterface> InterfaceContainer::getImageInterface() const
{
    return imageInterface;
}

std::shared_ptr<SettingsInterface> InterfaceContainer::getSettingsInterface() const
{
    return settingsInterface;
}
