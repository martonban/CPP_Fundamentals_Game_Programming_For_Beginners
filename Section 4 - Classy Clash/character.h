#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float delataTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec(){return weaponCollitonRec;}
    float gerHealth() const { return health; }
    void takeDamage(float damage);
private:
   int windowWidth{};
   int windowHeight{};
   Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
   Rectangle weaponCollitonRec{};
   float health{100.f};
};

#endif