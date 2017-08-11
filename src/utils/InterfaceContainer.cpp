#include "utils/InterfaceContainer.h"

using namespace bkengine;


std::shared_ptr<EventInterface> InterfaceContainer::getEventInterface() const
{
    return eventInterface;
}

std::shared_ptr<SettingsInterface> InterfaceContainer::getSettingsInterface()
const
{
    return settingsInterface;
}

std::shared_ptr<GraphicsInterface> InterfaceContainer::getGraphicsInterface()
const
{
    return graphicsInterface;
}