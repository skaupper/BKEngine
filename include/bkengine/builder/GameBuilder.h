#ifndef BKENGINE_GAME_BUILDER_H
#define BKENGINE_GAME_BUILDER_H

#include <string>

#include "core/Game.h"
#include "utils/InterfaceContainer.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class GameBuilder
    {
        public:
            static GameBuilder createBuilder();
            
            GameBuilder &setWindowSize(Size);
            GameBuilder &setWindowTitle(const std::string &);
            
            GameBuilder &setIconFile(const std::string &);
            
            template <typename T> GameBuilder &setEventInterface();
            template <typename T> GameBuilder &setFontInterface();
            template <typename T> GameBuilder &setGraphicsInterface();
            template <typename T> GameBuilder &setImageInterface();
            template <typename T> GameBuilder &setSettingsInterface();
            
            template <typename T> std::shared_ptr<T> build() const;
            
        private:
            GameBuilder() = default;
            
            InterfaceContainer interfaceContainer;
            Size windowSize = {1024, 768};
            std::string windowTitle = "BKEngine Test";
            std::string iconFile = "";
    };
}

#include "templates/GameBuilder_templates.h"

#endif // BKENGINE_GAME_BUILDER_H