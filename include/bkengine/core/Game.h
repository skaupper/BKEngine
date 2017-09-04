#ifndef BKENGINE_GAME_H
#define BKENGINE_GAME_H

#include <memory>
#include <string>
#include <vector>

#include "core/ActivatorObject.h"
#include "core/Scene.h"
#include "exceptions/GameLoopException.h"
#include "utils/InterfaceContainer.h"
#include "utils/Logger.h"
#include "utils/Timer.h"


namespace bkengine
{
    class Game : public ActivatorObject<Scene, Game>
    {
        friend class GameBuilder;
        friend class ImageTextureBuilder;
        friend class TextTextureBuilder;

    public:
        virtual ~Game() = default;

        void run();
        void stop();

        bool isRunning() const;

    protected:
        explicit Game() = default;

        virtual bool onRender();
        virtual bool onLoop();
        virtual bool onEvent(const Event &);

        void setIconFile(const std::string &);
        void setWindowSize(Size);
        void setWindowTitle(const std::string &);

    private:
        void _onRender();
        void _onLoop();
        void _onEvent(const Event &);

        InterfaceContainer interfaceContainer;

        bool running = false;
        Timer timer;

        //            template <typename T> T &getData(const std::string &name);
        //            template <typename T> T &addData(const std::string &name);
        //            bool hasData(const std::string &name);
        //            std::map<std::string, std::shared_ptr<Storage>> dataStore;
    };
}

#endif
