#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "entity.h"

class Player : public Entity {
public:
    int score;
    bool isShoot;

    Player(sf::Image& image, float X, float Y, int W, int H, std::string Name,
           float Speed = 0, Direction Dir = Direction::up) : Entity(image, X, Y, W, H, Name, Speed, Dir){
        score = 0; isShoot = false;
        if (name == "Player1") {spriteX = 0; spriteY = 0;}  /// small yellow tank
        if (name == "Player2") {spriteX = 1; spriteY = 128;}/// small green tank
        sprite.setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
    };

    int getPlayerScore()    { return score;};

    void control(float time){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {/// LEFT
            dir = Direction::left; speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;/// in animate method!?
            sprite.setTextureRect(sf::IntRect(spriteX + 32 + int(currentFrame)*SPRITE_W, spriteY, SPRITE_W, SPRITE_H));///in animate method!?
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){/// RIGHT
            dir = Direction::right; speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;///
            sprite.setTextureRect(sf::IntRect(spriteX + 96 + int(currentFrame)*SPRITE_W, spriteY, SPRITE_W, SPRITE_H));///
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {/// UP
            dir = Direction::up; speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(spriteX + 0 + int(currentFrame)*(SPRITE_W+1), spriteY, SPRITE_W, SPRITE_H));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){/// DOWN
            dir = Direction::down; speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(spriteX + 64 + int(currentFrame)*(SPRITE_W+1), spriteY, SPRITE_W, SPRITE_H));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){/// Shoot
            isShoot = true;
        }
    };

    void update(float time) override{
        moveTimer += time;
        control(time);
        switch (dir){
            case Direction::up:    dx = 0;       dy = -speed;  break;
            case Direction::down:  dx = 0;       dy = speed;   break;
            case Direction::left:  dx = -speed;  dy = 0;       break;
            case Direction::right: dx = speed;   dy = 0;       break;

        }
        x += dx * time; y += dy * time; speed = 0;
        interactionWithMap();
        sprite.setPosition(x, y);
        if (score < 0) life = false;
    };

    void interactionWithMap(){
        /// limit the movement to the borders of the map
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > WIDTH_MAP*SPRITE_W-SPRITE_W) x = WIDTH_MAP*SPRITE_W-SPRITE_W;
        if (y > HEIGHT_MAP*SPRITE_H-SPRITE_H) y = HEIGHT_MAP*SPRITE_H-SPRITE_H;
        /// collisions with map objects
        for (int i = y/SPRITE_H; i < y/SPRITE_H +1 ; ++i){
            for (int j = x/SPRITE_W; j < x/SPRITE_W + 1; ++j){
                 /// solid objects don't let to step on them
                if (tileMap[i][j] == '*' || tileMap[i][j] == '#' || tileMap[i][j] == 'W'){
                    if (dy > 0) y = i*SPRITE_H-SPRITE_H;
                    if (dy < 0) y = i*SPRITE_H+SPRITE_H;
                    if (dx > 0) x = j*SPRITE_W-SPRITE_W;
                    if (dx < 0) x = j*SPRITE_W+SPRITE_W;
                }
                /// pickable items give/take away points and disappear
                if (tileMap[i][j] == 'S'){ score += 100; tileMap[i][j] = '0'; }
                if (tileMap[i][j] == 'B'){ score -= 300; tileMap[i][j] = '0'; }
            }
        }
    };

};

#endif // PLAYER_H_INCLUDED
