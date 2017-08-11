#ifndef BKENGINE_INTERFACE_CONTAINER_H
#define BKENGINE_INTERFACE_CONTAINER_H

#include "interfaces/EventInterface.h"
#include "interfaces/SettingsInterface.h"
#include "interfaces/GraphicsInterface.h"
#include "interfaces/ImageInterface.h"
#include "interfaces/FontInterface.h"


namespace bkengine
{
    class InterfaceContainer
    {
        public:
            template <typename T> InterfaceContainer &setEventInterface();
            template <typename T> InterfaceContainer &setSettingsInterface();
            template <typename T> InterfaceContainer &setGraphicsInterface();

            std::shared_ptr<EventInterface> getEventInterface() const;
            std::shared_ptr<SettingsInterface> getSettingsInterface() const;
            std::shared_ptr<GraphicsInterface> getGraphicsInterface() const;

        private:
            std::shared_ptr<EventInterface> eventInterface;
            std::shared_ptr<SettingsInterface> settingsInterface;
            std::shared_ptr<GraphicsInterface> graphicsInterface;
    };
}

#include "templates/InterfaceContainer_templates.h"

#endif