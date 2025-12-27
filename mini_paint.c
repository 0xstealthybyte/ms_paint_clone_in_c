#include "raylib.h"
#include "raygui.h"
#include <stddef.h>  

#define MAX_BRUSH_SIZE 50
#define MIN_BRUSH_SIZE 2

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Mini MS Paint Clone - Cheap Edition ");
    SetTargetFPS(400);

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    Color currentColor = BLACK;
    float brushSize = 10.0f;
    bool erasing = false;


    BeginTextureMode(canvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();


    Rectangle btnRed = {10, 10, 60, 30};
    Rectangle btnGreen = {80, 10, 60, 30};
    Rectangle btnBlue = {150, 10, 60, 30};
    Rectangle btnEraser = {220, 10, 80, 30};
    Rectangle btnClear = {310, 10, 80, 30};
    Rectangle btnSave = {400, 10, 80, 30};
    Rectangle btnLoad = {490, 10, 80, 30};
    Rectangle btnBrushUp = {580, 10, 30, 30};
    Rectangle btnBrushDown = {620, 10, 30, 30};

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, btnRed)) currentColor = RED, erasing = false;
            else if (CheckCollisionPointRec(mouse, btnGreen)) currentColor = GREEN, erasing = false;
            else if (CheckCollisionPointRec(mouse, btnBlue)) currentColor = BLUE, erasing = false;
            else if (CheckCollisionPointRec(mouse, btnEraser)) erasing = !erasing;
            else if (CheckCollisionPointRec(mouse, btnClear)) {
                BeginTextureMode(canvas);
                ClearBackground(RAYWHITE);
                EndTextureMode();
            }
            else if (CheckCollisionPointRec(mouse, btnBrushUp)) {
                brushSize += 2.0f;
                if (brushSize > MAX_BRUSH_SIZE) brushSize = MAX_BRUSH_SIZE;
            }
            else if (CheckCollisionPointRec(mouse, btnBrushDown)) {
                brushSize -= 2.0f;
                if (brushSize < MIN_BRUSH_SIZE) brushSize = MIN_BRUSH_SIZE;
            }
            else if (CheckCollisionPointRec(mouse, btnSave)) {
                Image img = LoadImageFromTexture(canvas.texture);
                ExportImage(img, "my_paint.png");
                UnloadImage(img);
            }
            else if (CheckCollisionPointRec(mouse, btnLoad)) {
                Image img = LoadImage("my_paint.png");
                if (img.data != NULL)
                {
                    Texture2D tex = LoadTextureFromImage(img);
                    BeginTextureMode(canvas);
                    DrawTexture(tex, 0, 0, WHITE);
                    EndTextureMode();
                    UnloadTexture(tex);
                    UnloadImage(img);
                }
            }
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouse.y > 50) 
        {
            BeginTextureMode(canvas);
            DrawCircleV(mouse, brushSize, erasing ? RAYWHITE : currentColor);
            EndTextureMode();
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        DrawTextureRec(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width, -(float)canvas.texture.height}, (Vector2){0, 0}, WHITE);


        DrawRectangleRec(btnRed, RED);
        DrawText("Red", btnRed.x + 10, btnRed.y + 7, 10, WHITE);

        DrawRectangleRec(btnGreen, GREEN);
        DrawText("Green", btnGreen.x + 5, btnGreen.y + 7, 10, BLACK);

        DrawRectangleRec(btnBlue, BLUE);
        DrawText("Blue", btnBlue.x + 10, btnBlue.y + 7, 10, WHITE);

        DrawRectangleRec(btnEraser, erasing ? DARKGRAY : GRAY);
        DrawText("Eraser", btnEraser.x + 10, btnEraser.y + 7, 10, WHITE);

        DrawRectangleRec(btnClear, MAROON);
        DrawText("Clear", btnClear.x + 15, btnClear.y + 7, 10, WHITE);

        DrawRectangleRec(btnSave, DARKGREEN);
        DrawText("Save", btnSave.x + 15, btnSave.y + 7, 10, WHITE);

        DrawRectangleRec(btnLoad, DARKBLUE);
        DrawText("Load", btnLoad.x + 15, btnLoad.y + 7, 10, WHITE);

        DrawRectangleRec(btnBrushUp, DARKGRAY);
        DrawText("+", btnBrushUp.x + 10, btnBrushUp.y + 5, 20, WHITE);

        DrawRectangleRec(btnBrushDown, DARKGRAY);
        DrawText("-", btnBrushDown.x + 10, btnBrushDown.y + 5, 20, WHITE);

        DrawText(TextFormat("Brush Size: %.0f", brushSize), 670, 15, 15, BLACK);
        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    CloseWindow();
    return 0;
}

