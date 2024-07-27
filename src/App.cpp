#include "App.hpp"
#include <raylib.h>
#include "config.h"

App::App() {

}

int App::start()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SudokuSaki™️ ");
    // ToggleBorderlessWindowed();
    SetTargetFPS(30);
    
    board = new Board;
    //board->generateBoard();
    board->testValuePicker();
    
    mainLoop();

    CloseWindow();

    return 0;
}

void App::mainLoop()
{
    bool quitting = false;

    
    Color backgroundColor = PURPLE;
    

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

}
