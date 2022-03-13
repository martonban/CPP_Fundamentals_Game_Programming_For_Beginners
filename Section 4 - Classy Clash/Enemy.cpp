#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture){
        worldPos = pos;
        texture = idle_texture;
        idle = idle_texture;
        run = run_texture;
        width = texture.width / maxFrames;
        height = texture.height;
        speed = 2.0f;
}

        
void Enemy::tick(float delataTime){

        if(!getAlive()) return;
        velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
        BaseCharacter::tick(delataTime);


        if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())){
                target -> takeDamage(damagePerSec * delataTime);
        }

}

Vector2 Enemy::getScreenPos(){
        return Vector2Subtract(worldPos, target->getWorldPos());
}