#ifndef BKENGINE_INTERFACE_CONTAINER_H
#define BKENGINE_INTERFACE_CONTAINER_H

#include <memory>

#include "exceptions/NullPointerException.h"
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
            template <typename T> void setEventInterface();
            template <typename T> void setFontInterface();
            template <typename T> void setGraphicsInterface();
            template <typename T> void setImageInterface();
            template <typename T> void setSettingsInterface();
            
            std::shared_ptr<EventInterface> getEventInterface() const;
            std::shared_ptr<FontInterface> getFontInterface() const;
            std::shared_ptr<GraphicsInterface> getGraphicsInterface() const;
            std::shared_ptr<ImageInterface> getImageInterface() const;
            std::shared_ptr<SettingsInterface> getSettingsInterface() const;
            
        private:
            std::shared_ptr<EventInterface> eventInterface = nullptr;
            std::shared_ptr<FontInterface> fontInterface = nullptr;
            std::shared_ptr<GraphicsInterface> graphicsInterface = nullptr;
            std::shared_ptr<ImageInterface> imageInterface = nullptr;
            std::shared_ptr<SettingsInterface> settingsInterface = nullptr;
    };
}

#include "templates/InterfaceContainer_templates.h"

#endif