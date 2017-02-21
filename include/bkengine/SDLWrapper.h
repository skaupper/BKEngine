#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#ifndef TEST
#define MANGLE_SDL(name) name
#else
#define MANGLE_SDL(name) bkengine_test::SDLProvider::getInstance()->name

namespace bkengine_test
{
    class SDL
    {
        protected:
            static SDL instance;
            SDL() {}
            SDL(const SDL &) = delete;
            SDL &operator=(const SDL &) = delete;

        public:
            static SDL *getInstance()
            {
                return &instance;
            }

            virtual const char *SDL_GetError();

            virtual void SDL_DestroyRenderer(SDL_Renderer *);
            virtual void SDL_DestroyWindow(SDL_Window *);
            virtual void SDL_Quit();
            virtual int SDL_Init(uint32_t);
            virtual SDL_bool SDL_SetHint(const char *, const char *);
            virtual SDL_Window *SDL_CreateWindow(const char *, int, int, int, int,
                                                 uint32_t);
            virtual void SDL_SetWindowIcon(SDL_Window *, SDL_Surface *);
            virtual void SDL_FreeSurface(SDL_Surface *);
            virtual SDL_Renderer *SDL_CreateRenderer(SDL_Window *, int, uint32_t);
            virtual int SDL_SetRenderDrawColor(SDL_Renderer *, uint8_t, uint8_t, uint8_t,
                                               uint8_t);
            virtual int SDL_PollEvent(SDL_Event *);
            virtual void SDL_Delay(uint32_t);
            virtual int SDL_RenderClear(SDL_Renderer *);
            virtual void SDL_RenderPresent(SDL_Renderer *);
            virtual void SDL_DestroyTexture(SDL_Texture *);
            virtual SDL_Texture *SDL_CreateTextureFromSurface(SDL_Renderer *,
                    SDL_Surface *);
            virtual int SDL_QueryTexture(SDL_Texture *, uint32_t *, int *, int *, int *);
            virtual void SDL_GetWindowSize(SDL_Window *, int *, int *);
            virtual const char *SDL_GetWindowTitle(SDL_Window *);
            virtual int SDL_RenderCopyEx(SDL_Renderer *, SDL_Texture *, const SDL_Rect *,
                                         const SDL_Rect *, const double, const SDL_Point *, const SDL_RendererFlip);
            virtual int SDL_RenderCopy(SDL_Renderer *, SDL_Texture *, const SDL_Rect *,
                                       const SDL_Rect *);
            virtual uint32_t SDL_GetTicks();


            virtual int TTF_Init();
            virtual TTF_Font *TTF_OpenFont(const char *, int);
            virtual SDL_Surface *TTF_RenderUTF8_Solid(TTF_Font *, const char *, SDL_Color);
            virtual SDL_Surface *TTF_RenderUTF8_Shaded(TTF_Font *, const char *, SDL_Color,
                    SDL_Color);
            virtual SDL_Surface *TTF_RenderUTF8_Blended(TTF_Font *, const char *,
                    SDL_Color);
            virtual void TTF_CloseFont(TTF_Font *);
            virtual void TTF_Quit();

            virtual int IMG_Init(int);
            virtual SDL_Surface *IMG_Load(const char *);
            virtual void IMG_Quit();

            virtual int Mix_OpenAudio(int, uint16_t, int, int);
            virtual void Mix_Quit();
    };

    class SDLProvider
    {
        private:
            static SDL *instance;
            SDLProvider() { }
            virtual ~SDLProvider() {}
            SDLProvider(const SDLProvider &) = delete;
            SDLProvider &operator=(const SDLProvider &) = delete;

        public:
            static SDL *getInstance()
            {
                return instance;
            }

            static void setInstance(SDL *i)
            {
                instance = i;
            }
    };
}

#endif
#endif
