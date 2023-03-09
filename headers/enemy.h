#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "entity.h"

class Enemy : public Entity{

public:
    float changeDirTimer;
	Enemy(sf::Image &image, float X, float Y, int W, int H, std::string Name,
       float Speed = 0, Direction Dir = Direction::down) : Entity(image, X, Y, W, H, Name, Speed, Dir){
		changeDirTimer = 0.0;
		if (name == "Enemy0"){ spriteX = 128; spriteY = 1; } /// small silver tank
        if (name == "Enemy1"){ spriteX = 128; spriteY = 16; }/// heavy silver tank
        if (name == "Enemy2"){ spriteX = 128; spriteY = 80; }/// quick silver tank
        sprite.setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
        dx = 0.0; dy = 0.1;
	}

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
                /// pickable items simply disappear if taken by enemy
                if (tileMap[i][j] == 'S'){ tileMap[i][j] = '0';}
                if (tileMap[i][j] == 'B'){ tileMap[i][j] = '0';}
            }
        }
    }

    void control(float time){
        if (dx < 0) {/// LEFT
            dir = Direction::left; //speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;/// in animate method!?
            sprite.setTextureRect(sf::IntRect(spriteX + 32 + int(currentFrame)*SPRITE_W, spriteY, SPRITE_W, SPRITE_H));///in animate method!?
        }
        else if (dx > 0){/// RIGHT
            dir = Direction::right; //speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;///
            sprite.setTextureRect(sf::IntRect(spriteX + 96 + int(currentFrame)*SPRITE_W, spriteY, SPRITE_W, SPRITE_H));///
        }
        else if (dy < 0) {/// UP
            dir = Direction::up; //speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(spriteX + 0 + int(currentFrame)*(SPRITE_W+1), spriteY, SPRITE_W, SPRITE_H));
        }
        else if (dy > 0){/// DOWN
            dir = Direction::down; //speed = 0.1;
            currentFrame += 0.2 * time; if (currentFrame > 2) currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(spriteX + 64 + int(currentFrame)*(SPRITE_W+1), spriteY, SPRITE_W, SPRITE_H));
        }
    }

	void update(float time){
        control(time);
        changeDirTimer += time;
        if (changeDirTimer > 1000){
            dx = speed * (1 - rand()%3) ;
            if (dx != 0) dy = 0;
            else {dy = speed * (1 - rand()%3);}
//std::cout<<"dx = " <<dx<<"; dy = " << dy << "; time = "<<time<<std::endl;
            changeDirTimer = 0;
        }

        x += dx * time;
        y += dy * time;
        interactionWithMap();
        sprite.setPosition(x, y);
    }
};

#endif // ENEMY_H_INCLUDED
