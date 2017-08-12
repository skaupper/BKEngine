#include "utils/InterfaceContainer.h"

using namespace bkengine;


std::shared_ptr<EventInterface> InterfaceContainer::getEventInterface() const
{
    if (!eventInterface) {
        throw NullPointerException("You have not set an event interface!");
    }
    
    return eventInterface;
}

std::shared_ptr<FontInterface> InterfaceContainer::getFontInterface()
const
{
    if (!fontInterface) {
        throw NullPointerException("You have not set an font interface!");
    }
    
    return fontInterface;
}

std::shared_ptr<GraphicsInterface> InterfaceContainer::getGraphicsInterface()
const
{
    if (!graphicsInterface) {
        throw NullPointerException("You have not set an graphics interface!");
    }
    
    return graphicsInterface;
}

std::shared_ptr<ImageInterface> InterfaceContainer::getImageInterface()
const
{
    if (!imageInterface) {
        throw NullPointerException("You have not set an image interface!");
    }
    
    return imageInterface;
}

std::shared_ptr<SettingsInterface> InterfaceContainer::getSettingsInterface()
const
{
    if (!settingsInterface) {
        throw NullPointerException("You have not set an settings interface!");
    }
    
    return settingsInterface;
}
