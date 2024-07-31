#include "App.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>
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
}

void App::update() {

}

void App::draw()
{
    mScene->draw();
}
