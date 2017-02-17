#ifndef SDL_MOCK_H
#define SDL_MOCK_H

#include "gmock/gmock.h"
#include "SDLWrapper.h"

using namespace ::testing;
using namespace bkengine_test;

class SDLMock : public SDL
{
    public:
        SDLMock()
        {
            SDLProvider::setInstance(this);
        }

        MOCK_METHOD0(SDL_GetError, const char *());
        MOCK_METHOD1(SDL_DestroyRenderer, void (SDL_Renderer *));
        MOCK_METHOD1(SDL_DestroyWindow, void (SDL_Window *));
        MOCK_METHOD0(SDL_Quit, void ());
        MOCK_METHOD1(SDL_Init, int (uint32_t));
        MOCK_METHOD2(SDL_SetHint, SDL_bool(const char *, const char *));
        MOCK_METHOD6(SDL_CreateWindow, SDL_Window * (const char *, int, int, int, int,
                     uint32_t));
        MOCK_METHOD2(SDL_SetWindowIcon, void (SDL_Window *, SDL_Surface *));
        MOCK_METHOD1(SDL_FreeSurface, void (SDL_Surface *));
        MOCK_METHOD3(SDL_CreateRenderer, SDL_Renderer * (SDL_Window *, int, uint32_t));
        MOCK_METHOD5(SDL_SetRenderDrawColor, int (SDL_Renderer *, uint8_t, uint8_t,
                     uint8_t, uint8_t));
        MOCK_METHOD1(SDL_PollEvent, int (SDL_Event *));
        MOCK_METHOD1(SDL_Delay, void (uint32_t));
        MOCK_METHOD1(SDL_RenderClear, int (SDL_Renderer *));
        MOCK_METHOD1(SDL_RenderPresent, void (SDL_Renderer *));
        MOCK_METHOD1(SDL_DestroyTexture, void (SDL_Texture *));
        MOCK_METHOD2(SDL_CreateTextureFromSurface, SDL_Texture * (SDL_Renderer *,
                     SDL_Surface *));
        MOCK_METHOD5(SDL_QueryTexture, int (SDL_Texture *, uint32_t *, int *, int *,
                                            int *));
        MOCK_METHOD7(SDL_RenderCopyEx, int (SDL_Renderer *, SDL_Texture *,
                                            const SDL_Rect *, const SDL_Rect *, const double, const SDL_Point *,
                                            const SDL_RendererFlip));
        MOCK_METHOD4(SDL_RenderCopy, int (SDL_Renderer *, SDL_Texture *,
                                          const SDL_Rect *, const SDL_Rect *));
        MOCK_METHOD0(SDL_GetTicks, uint32_t ());

        MOCK_METHOD0(TTF_Init, int ());
        MOCK_METHOD2(TTF_OpenFont, TTF_Font * (const char *, int));
        MOCK_METHOD3(TTF_RenderText_Solid, SDL_Surface * (TTF_Font *, const char *,
                     SDL_Color));
        MOCK_METHOD1(TTF_CloseFont, void (TTF_Font *));
        MOCK_METHOD0(TTF_Quit, void ());

        MOCK_METHOD1(IMG_Init, int (int));
        MOCK_METHOD1(IMG_Load, SDL_Surface * (const char *));
        MOCK_METHOD0(IMG_Quit, void ());

        MOCK_METHOD4(Mix_OpenAudio, int (int, uint16_t, int, int));
        MOCK_METHOD0(Mix_Quit, void ());
};

#endif
