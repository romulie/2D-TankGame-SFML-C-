#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "direction.h"
#include "gamemap.h"

class Entity{
public:
    float x, y, dx, dy, speed, moveTimer;   /// coordinates x/y, accelerations dx/dy, speed, timer for animation
    int w, h, health;                       ///dimensions w/h
    bool life;
    std::string name;
    float spriteX, spriteY;                 /// basic coordinates for a sprite of an entity
    float currentFrame;                     /// for animation
    Direction dir;
    sf::Texture texture;
    sf::Sprite sprite;

    Entity(sf::Image &image, float X, float Y, int W, int H, std::string Name,
           float Speed = 0, Direction Dir = Direction::up) {
        x = X; y = Y;
        w = W; h = H;
        dx = 0; dy = 0;
        dir = Dir;
        speed = Speed;
        name = Name;
        moveTimer = 0;
        health = 100;
        life = true;
        currentFrame = 0;
        spriteX = 0; spriteY = 0;
        //image.createMaskFromColor(sf::Color(0, 0, 0));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
    }

    virtual ~Entity() {};

    sf::FloatRect getRect() {return sf::FloatRect(x, y, w, h);}

    float getPlayerX()      { return x;}
    float getPlayerY()      { return y;}

    virtual void update(float time) = 0;
};

#endif // ENTITY_H_INCLUDED
