#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex):
    worldPos(pos),
    texture(tex)
{

}

void Prop::render(Vector2 knightPos){
    Vector2 screePos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screePos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos){
    Vector2 screePos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screePos.x, 
        screePos.y,
        texture.width * scale,
        texture.height * scale
    };
}