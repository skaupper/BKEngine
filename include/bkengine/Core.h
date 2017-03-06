#ifndef BKENGINE_CORE_H
#define BKENGINE_CORE_H

#include <string>
#include <vector>
#include <functional>

#include "Logger.h"
#include "SDLWrapper.h"
#include "Misc.h"


namespace bkengine
{
    class Core
    {
            /* static stuff */
        public:
            /**
                Initializes all interfaces.
            */
            static bool initDeps();

            /**
                Returns the instance of Core created with Core::createInstance.
                Note: This method does not guarantee any validity check of the returned pointer!

                \return The value of the static *instance* variable which contains either `nullptr` if no instance has been created yet or a pointer to Core.
            */
            static Core *getInstance();

            /**
                Creates a single instance of Core with the given parameter.
                If a instance has already been created it will be destroyed before creating a new one.
                If an error occurs while creating renderer and window a `nullptr` is returned.

                \param [in] width Specifies the width of the window to be created.
                \param [in] height Specifies the height of the window to be created.
                \param [in] windowTitle Specifies the title of the window to be created.

                \return A pointer to an instance of Core or `nullptr` if an error occurred.

                \sa Core::getInstance
            */
            static Core *createInstance(int width, int height,
                                        const std::string &windowTitle);

            /**
                Registers a cleanup callback which is called when Core::quit is called.
                Can be used to deinitialize interfaces or static storages on exit.

                \param [in] cleanupFunction Cleanup function to be called while Core::quit.

                \sa Core::quit
            */
            static void registerCleanup(std::function<void()> cleanupFunction);

            /**
                Cleanup all members and dependencies initialized at the creation
                of Core and calls all functions registered with Core::registerCleanup.

                \sa Core::registerCleanup
            */
            static void quit();

        protected:
            static Core *instance;
            static bool depsInited;
            static std::vector<std::function<void()>> cleanupFunctions;


            /* getter and setter */
        public:
            /**
                Sets the window icon of the current window.
                Requires that an window has already been created with
                Core::createInstance and *iconPath* refers to a suitable icon file.

                \param [in] iconPath Path to a .ico file.
                \return `true` if operation suceeded otherwise `false`.
            */
            bool setIcon(const std::string &iconPath);

            /**
                Sets the window title of the current window.
                Requires that an window has already been created with
                Core::createInstance.

                \param [in] windowTitle Window title to be set.

                \sa Core::getWindowTitle \n Core::getTrueWindowTitle
            */
            void setWindowTitle(const std::string &windowTitle);

            /**
                Resizes the current window.
                Requires that an window has already been created with
                Core::createInstance.

                \param [in] width New window width.
                \param [in] height New window height.

                \sa Core::getWindowSize \n Core::getTrueWindowSize
            */
            void resizeWindow(int width, int height);

            /**
                Queries the current size of the window.
                Asks the underlying framework which owns the window for the current size.

                \sa Core::getWindowSize \n Core::resizeWindow
                \return A Size object filled with the actual dimensions.
            */
            Size getTrueWindowSize() const;

            /**
                Queries the current title of the window.
                Asks the underlying framework which owns the window for the current title.

                \sa Core::getWindowTitle \n Core::setWindowTitle
                \return The current window title as `std::string`.
            */
            std::string getTrueWindowTitle() const;

            /**
                Returns the window size requested at window creation.
                In contrast to Core::getTrueWindowSize *getWindowSize* returns the
                dimensions the user requested with a call to Core::createInstance
                resp. subsequent calls to Core::resizeWindow.\n
                Note: The returned values may or may not differ from the actual values.

                \sa Core::getTrueWindowSize \n Core::resizeWindow
                \return A Size object filled with the requested window dimensions.
            */
            Size getWindowSize() const;

            /**
                Returns the window title requested at window creation.
                In contrast to Core::getTrueWindowTitle *getWindowTitle* returns the
                title the user requested with a call to Core::createInstance
                resp. subsequent calls to Core::setWindowTitle.\n
                Note: The returned string may or may not differ from the actual title.

                \sa Core::getTrueWindowTitle \n Core::setWindowTitle
                \return The requested window title as `std::string`.
            */
            std::string getWindowTitle() const;

            /**
                Returns the SDL renderer used by the current window.
                The renderer is created by Core::createInstance.\n
                Note: This method does not guarantee any validity check of the returned pointer!\n
                Note: This method may or may not be changed or dropped in the future
                during the introduction of separate graphical interfaces!

                \return A pointer to an SDL renderer used by the current window.
            */
            SDL_Renderer *getRenderer() const;

        protected:
            std::string windowTitle;
            int windowWidth;
            int windowHeight;


            /* other stuff */
        public:
            virtual ~Core();

            /**
                Initializes all (directly) underlying frameworks like **SDL2**,
                **SDL2_ttf**, **SDL2_image** and **SDL2_mixer**.
                You may want to call this method by yourself if your code
                relies on the initialized third party tools but you do not
                need a window or a renderer yet.\n
                Note: *initEnvironment* will be called automatically at
                Core::createInstance if it has not been called by then.

                \return `true` if initialization was successful otherwise `false`.
            */
            bool initEnvironment();

        protected:
            bool environmentInited;
            SDL_Window *window;
            SDL_Renderer *renderer;

            Core();
            Core(Core &&);
            Core &operator=(Core &&);
            void move(Core &);
            Core(int width, int height, const std::string &windowTitle);
    };
}

#endif
