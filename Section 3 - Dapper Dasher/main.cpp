#include "raylib.h"
#include<stdio.h>

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime; 
};


bool isOnGround(AnimData data, int windowHeight);
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame);



int main(){

    //Window Dimensions
    const int windowHeight{380};
    const int windowWidth{512};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");


    //Nebula 
    Texture2D nebula = LoadTexture("sprites/12_nebula_spritesheet.png");



    AnimData nebulae[6]{};

    for (int i = 0; i < 6; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowHeight - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowWidth;
    nebulae[1].pos.x = windowWidth + 500;
    nebulae[2].pos.x = windowWidth + 1200;
    nebulae[3].pos.x = windowWidth + 1700;
    nebulae[4].pos.x = windowWidth + 2200;
    nebulae[5].pos.x = windowWidth + 2700;


    float finishLine{nebulae[5].pos.x};

    
    int nebVel{-300}; 



    // Scarfy
    const int gravity{1000};
    Texture2D scarfy = LoadTexture("sprites/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    // (pixels/s)/s
    int velocity{0};
    const int jumpVel{-600}; 

    Texture2D background = LoadTexture("sprites/far-buildings.png");
    Texture2D midGround = LoadTexture("sprites/back-buildings.png");
    Texture2D frontGround = LoadTexture("sprites/foreground.png");
    float bgX{};
    float mgX{};
    float fgX{};

    bool isInAir{true};
    bool collision{};
    

    SetTargetFPS(120);
    //Game Lopp
    while(WindowShouldClose() == false){
        //DeltaTime
        const float dt{GetFrameTime()};
        
        //Draw
        BeginDrawing();
        ClearBackground(WHITE);
        
        bgX -= 20 * dt;
        if(bgX <= -background.width*2){
            bgX = 0.0;
        }

        mgX -= 40 * dt;
        if(mgX <= -midGround.width*2){
            mgX = 0.0;
        }

        fgX -= 80 * dt;
        if(fgX <= -frontGround.width*2){
            fgX = 0.0;
        }

        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midGround, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midGround.width*2, 0.0};
        DrawTextureEx(midGround, mg2Pos, 0.0, 2.0, WHITE);
        
        
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(frontGround, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + frontGround.width*2, 0.0};
        DrawTextureEx(frontGround, fg2Pos, 0.0, 2.0, WHITE);

        //Ground Check   
        if(isOnGround(scarfyData, windowHeight)){
            velocity = 0;
            isInAir = false; 
        }else{
            velocity += gravity*dt;
            isInAir = true;
        }

        //Jump mechanic
        if(IsKeyPressed(KEY_SPACE) && isInAir == false){
            velocity += jumpVel;
        }


        // Update ScaryPos
        scarfyData.pos.y += velocity * dt;

        //animation 
        scarfyData.frame += dt;

        if(!isInAir){
            scarfyData = updateAnimData(scarfyData, dt, 5);
        }

        for(int i = 0; i < 6; i++){
            nebulae[i] = updateAnimData(nebulae[i], dt, 7);
            nebulae[i].pos.x += nebVel * dt;
        }

        finishLine += nebVel * dt;

        

        for(AnimData nebula : nebulae){
            float pad{50};
            Rectangle nabRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };

            Rectangle scaraftRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };

            if(CheckCollisionRecs(nabRec,scaraftRec)){
                collision = true;
            }
        }



        if(!collision){
            // Are you winning Son?
            // Draw Nebulas
            for(int i = 0; i < 6; i++){
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            
            //Draw Scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        }else{
            //Lose the game
            DrawText("Ganme Over", windowWidth/2, windowHeight/2, 40, RED);
        }

        if(scarfyData.pos.x >= finishLine){
            DrawText("You Win", windowWidth/2, windowHeight/2, 40, GREEN);
        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midGround);
    UnloadTexture(frontGround);
    CloseWindow();



}

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight-data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame){

    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        // Update Animation Frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame ){
            data.frame = 0;
        }
    }
    return data;
}

