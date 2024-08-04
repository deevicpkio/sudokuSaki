#include "App.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>
#include "Board.hpp"
#include "config.h"

App::App() {

}

int App::start()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SudokuSaki™️ ");
    ToggleBorderlessWindowed();
    SetTargetFPS(30);
    
    mBoard = new Board;
    mBoard->newBoard();
    
    mScene = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT);
    mScene->init(mBoard);

    mainLoop();

    CloseWindow();

    return 0;
}

void App::mainLoop()
{
    bool quitting = false;

    
    Color backgroundColor = GOLD;
    

    while(!quitting) {

        if (WindowShouldClose()) {
            quitting = WindowShouldClose();
            continue;
        }
        handleInput();

        update();

        BeginDrawing();
            ClearBackground(backgroundColor);
            draw();
        EndDrawing();
    }

}

void App::handleInput() {
    int keyPressed = GetKeyPressed();

    switch(keyPressed)
    {
        case KEY_A:
            break;
        case KEY_D:
            break;
        case KEY_W:
            break;
        case KEY_S:
            break;
        case KEY_SPACE:
            break;
    }
    
    if (IsKeyReleased(KEY_ZERO))
            mScene->setSelectedValue(0);
    if (IsKeyReleased(KEY_ONE))
            mScene->setSelectedValue(1);
    if (IsKeyReleased(KEY_TWO))
            mScene->setSelectedValue(2);
    if (IsKeyReleased(KEY_THREE))
            mScene->setSelectedValue(3);
    if (IsKeyReleased(KEY_FOUR))
            mScene->setSelectedValue(4);
    if (IsKeyReleased(KEY_FIVE))
            mScene->setSelectedValue(5);
    if (IsKeyReleased(KEY_SIX))
            mScene->setSelectedValue(6);
    if (IsKeyReleased(KEY_SEVEN))
            mScene->setSelectedValue(7);
    if (IsKeyReleased(KEY_EIGHT))
            mScene->setSelectedValue(8);
    if (IsKeyReleased(KEY_NINE))
            mScene->setSelectedValue(9);
}

void App::update() 
{
    mScene->update();
}

void App::draw()
{
    mScene->draw();
}
