#include "TextureTest.h"

#include <iostream>

#include "Game.h"
#include "Animation.h"

int TextureMock::initCount = 0;
int TextureMock::destructCount = 0;

TEST_F(TextureTest, DISABLED_countConstructorAndDestructorCalls)
{
    int width = 1920, height = 1080;
    const char *title = "TextureTestWindow";
    SDL_Window *window = (SDL_Window *) 0x00001234;
    SDL_Renderer *renderer = (SDL_Renderer *) 0x12340000;
    SDL_Surface *surface = (SDL_Surface *) 0x00123400;
    TTF_Font *font = (TTF_Font *) 0x01234000;
    SDL_Texture *texture = (SDL_Texture *) 0x00120034;
    ON_CALL(*mock, SDL_Init(_)).WillByDefault(Return(0));
    ON_CALL(*mock, IMG_Init(_)).WillByDefault(ReturnArg<0>());
    ON_CALL(*mock, TTF_Init()).WillByDefault(Return(0));
    ON_CALL(*mock, Mix_OpenAudio(_, _, _, _)).WillByDefault(Return(0));
    ON_CALL(*mock, SDL_SetHint(_, _)).WillByDefault(Return(SDL_TRUE));
    ON_CALL(*mock, SDL_Quit()).WillByDefault(Return());
    ON_CALL(*mock, TTF_Quit()).WillByDefault(Return());
    ON_CALL(*mock, IMG_Quit()).WillByDefault(Return());
    ON_CALL(*mock, Mix_Quit()).WillByDefault(Return());
    ON_CALL(*mock, SDL_CreateWindow(StrEq(title), _, _, width, height,
                                    _)).WillByDefault(Return(window));
    ON_CALL(*mock, SDL_DestroyWindow(_)).WillByDefault(Return());
    ON_CALL(*mock, SDL_SetWindowIcon(_, _)).WillByDefault(Return());
    ON_CALL(*mock, SDL_FreeSurface(_)).WillByDefault(Return());
    ON_CALL(*mock, SDL_CreateRenderer(_, _, _)).WillByDefault(Return(renderer));
    ON_CALL(*mock, SDL_DestroyRenderer(_)).WillByDefault(Return());
    ON_CALL(*mock, SDL_DestroyTexture(texture)).WillByDefault(Return());
    ON_CALL(*mock, SDL_SetRenderDrawColor(_, _, _, _, _)).WillByDefault(Return(0));
    ON_CALL(*mock, IMG_Load(_)).WillByDefault(Return(surface));
    ON_CALL(*mock, SDL_CreateTextureFromSurface(_,
            _)).WillByDefault(Return(texture));
    ON_CALL(*mock, TTF_RenderText_Solid(_, _, _)).WillByDefault(Return(surface));
    EXPECT_CALL(*mock, SDL_DestroyTexture(_));
    Game g(width, height, title);
    Scene &scene = g.addScene<Scene>("scene1");
    Element &element = scene.addElement<Element>("element1");
    Animation &animation = element.addAnimation<Animation>("animation1");
    animation.addText<TextureMock>("testFont.ttf", "animation test text", {0, 100});
    std::cout << TextureMock::initCount << std::endl;
    //animation.textures[0].texture->free();
    ASSERT_EQ(TextureMock::initCount, TextureMock::destructCount);
}
