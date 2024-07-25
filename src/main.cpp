#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "App.hpp"
#include "config.h"

int main () {
    
    App app = App();
    bool quitting = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "<New Raylib Game implementing RayGUI");
    ToggleBorderlessWindowed();
    SetTargetFPS(60);
    
    GuiLoadStyle(STY_JUNGLE);
    Color backgroundColor = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));

    while(!quitting) {

        if (WindowShouldClose()) {
            quitting = WindowShouldClose();
            continue;
        }
        
        app.HandleInput();

        app.Update(GetFrameTime());


        BeginDrawing();
        
        ClearBackground(backgroundColor);

        if (GuiButton((Rectangle){ 25, 255, 125, 30 }, GuiIconText(ICON_EXIT, "Exit Game"))) quitting = true;

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
