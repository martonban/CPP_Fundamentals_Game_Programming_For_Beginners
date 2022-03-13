#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main(){
    const int windowWidth{700};
    const int windowHeight{500};
    InitWindow(windowWidth, windowHeight, "Top Down");
    const float mapScale{4.0f};

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
      Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
      Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };



    Enemy goblin{
        Vector2{0,0},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        for(auto prop : props){
            prop.render(knight.getWorldPos());
        }


        if (!knight.getAlive()){
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }else{
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.gerHealth()), 0, 3);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        //CheckMap Pos
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + windowWidth > map.width * 4.0 ||
           knight.getWorldPos().y + windowHeight > map.height * 4.0){
            knight.undoMovement();
        }
        
        for(auto prop : props){
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())){
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec())){
                goblin.setAlive(false); 
            }
        }


        EndDrawing();

    }
    CloseWindow();
}
