#include "SDLWrapper.h"

using namespace bkengine_test;


SDL SDL::instance;
SDL *SDLProvider::instance = SDL::getInstance();


const char *SDL::SDL_GetError()
{
    return ::SDL_GetError();
}

void SDL::SDL_DestroyRenderer(SDL_Renderer *renderer)
{
    ::SDL_DestroyRenderer(renderer);
}

void SDL::SDL_DestroyWindow(SDL_Window *window)
{
    ::SDL_DestroyWindow(window);
}

void SDL::SDL_Quit()
{
    ::SDL_Quit();
}

int SDL::SDL_Init(uint32_t flags)
{
    return ::SDL_Init(flags);
}

SDL_bool SDL::SDL_SetHint(const char *name, const char *value)
{
    return ::SDL_SetHint(name, value);
}

SDL_Window *SDL::SDL_CreateWindow(const char *title, int x,
                                  int y, int w, int h, uint32_t flags)
{
    return ::SDL_CreateWindow(title, x, y, w, h, flags);
}

void SDL::SDL_SetWindowIcon(SDL_Window *window,
                            SDL_Surface *surface)
{
    ::SDL_SetWindowIcon(window, surface);
}

void SDL::SDL_FreeSurface(SDL_Surface *surface)
{
    ::SDL_FreeSurface(surface);
}

SDL_Renderer *SDL::SDL_CreateRenderer(SDL_Window *window,
                                      int index, uint32_t flags)
{
    return ::SDL_CreateRenderer(window, index, flags);
}

int SDL::SDL_SetRenderDrawColor(SDL_Renderer *renderer,
                                uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ::SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int SDL::SDL_PollEvent(SDL_Event *event)
{
    return ::SDL_PollEvent(event);
}

void SDL::SDL_Delay(uint32_t ms)
{
    ::SDL_Delay(ms);
}

int SDL::SDL_RenderClear(SDL_Renderer *renderer)
{
    return ::SDL_RenderClear(renderer);
}

void SDL::SDL_RenderPresent(SDL_Renderer *renderer)
{
    ::SDL_RenderPresent(renderer);
}

void SDL::SDL_DestroyTexture(SDL_Texture *texture)
{
    ::SDL_DestroyTexture(texture);
}

SDL_Texture *SDL::SDL_CreateTextureFromSurface(
    SDL_Renderer *renderer, SDL_Surface *surface)
{
    return ::SDL_CreateTextureFromSurface(renderer, surface);
}

int SDL::SDL_QueryTexture(SDL_Texture *texture,
                          uint32_t *format, int *access, int *w, int *h)
{
    return ::SDL_QueryTexture(texture, format, access, w, h);
}

int SDL::SDL_RenderCopyEx(SDL_Renderer *renderer,
                          SDL_Texture *texture, const SDL_Rect *srcrect,
                          const SDL_Rect *dstrect, const double angle, const SDL_Point *center,
                          const SDL_RendererFlip flip)
{
    return ::SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle,
                              center, flip);
}

int SDL::SDL_RenderCopy(SDL_Renderer *renderer,
                        SDL_Texture *texture, const SDL_Rect *srcrect,
                        const SDL_Rect *dstrect)
{
    return ::SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

uint32_t SDL::SDL_GetTicks()
{
    return ::SDL_GetTicks();
}


int SDL::TTF_Init()
{
    return ::TTF_Init();
}

TTF_Font *SDL::TTF_OpenFont(const char *path, int size)
{
    return ::TTF_OpenFont(path, size);
}

SDL_Surface *SDL::TTF_RenderText_Solid(TTF_Font *font, const char *text,
                                       SDL_Color color)
{
    return ::TTF_RenderText_Solid(font, text, color);
}

void SDL::TTF_CloseFont(TTF_Font *font)
{
    ::TTF_CloseFont(font);
}

void SDL::TTF_Quit()
{
    ::TTF_Quit();
}


int SDL::IMG_Init(int flags)
{
    return ::IMG_Init(flags);
}

SDL_Surface *SDL::IMG_Load(const char *path)
{
    return ::IMG_Load(path);
}

void SDL::IMG_Quit()
{
    ::IMG_Quit();
}


int SDL::Mix_OpenAudio(int frequency, uint16_t channel, int format,
                       int chunksize)
{
    return ::Mix_OpenAudio(frequency, channel, format, chunksize);
}

void SDL::Mix_Quit()
{
    ::Mix_Quit();
}
