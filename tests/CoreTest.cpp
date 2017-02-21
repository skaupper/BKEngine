#include "CoreTest.h"


TEST_F(CoreTest, DISABLED_initSetupQuitAndGetter)
{
    /*
    int width = 1920, height = 1080;
    const char *title = "GTEST";
    SDL_Window *window = (SDL_Window *) 0x00001234;
    SDL_Renderer *renderer = (SDL_Renderer *) 0x12340000;
    SDL_Surface *surface = (SDL_Surface *) 0x00123400;
    TTF_Font *font = (TTF_Font *) 0x01234000;
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
    ON_CALL(*mock, SDL_SetRenderDrawColor(_, _, _, _, _)).WillByDefault(Return(0));
    ON_CALL(*mock, IMG_Load(_)).WillByDefault(Return(surface));
    EXPECT_CALL(*mock, SDL_Init(_));
    EXPECT_CALL(*mock, IMG_Init(_));
    EXPECT_CALL(*mock, TTF_Init());
    EXPECT_CALL(*mock, Mix_OpenAudio(_, _, _, _));
    EXPECT_CALL(*mock, SDL_SetHint(_, _));
    EXPECT_CALL(*mock, SDL_Quit());
    EXPECT_CALL(*mock, TTF_Quit());
    EXPECT_CALL(*mock, IMG_Quit());
    EXPECT_CALL(*mock, Mix_Quit());
    EXPECT_CALL(*mock, SDL_CreateWindow(StrEq(title), _, _, width, height, _));
    EXPECT_CALL(*mock, SDL_DestroyWindow(window));
    EXPECT_CALL(*mock, SDL_SetWindowIcon(_, _));
    EXPECT_CALL(*mock, SDL_FreeSurface(surface));
    EXPECT_CALL(*mock, SDL_CreateRenderer(_, _, _));
    EXPECT_CALL(*mock, SDL_DestroyRenderer(renderer));
    EXPECT_CALL(*mock, SDL_SetRenderDrawColor(_, _, _, _, _));
    EXPECT_CALL(*mock, IMG_Load(_));
    ASSERT_EQ(Core::init(), 0);
    Core *core = Core::getInstance(width, height, title);
    ASSERT_NE(core, (Core *) 0x0);
    ASSERT_EQ(core->setup(), 0);
    ASSERT_EQ(core->getRenderer(), renderer);
    ASSERT_EQ(core->getWindowSize().w, width);
    ASSERT_EQ(core->getWindowSize().h, height);
    Core::quit();
    */
}
