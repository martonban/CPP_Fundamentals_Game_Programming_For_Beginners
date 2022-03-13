#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){
    
}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(){
        return Rectangle{
        getScreenPos().x, 
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void  BaseCharacter::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime){
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames){
            frame = 0;
        }
    }

    if (Vector2Length(velocity) != 0.0){
        // set mapPos = mapPos+velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        if (velocity.x < 0.f){
            rightLeft = -1.f;
        }
        else{
            rightLeft = 1.f;
        }
        texture = run;
    }
    else{
        texture = idle;
    }
    velocity = {}; 
    
    // Draw the character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, 5.0f * width, 5.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}