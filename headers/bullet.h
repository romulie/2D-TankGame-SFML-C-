#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "entity.h"

class Bullet :public Entity{
public:
	Bullet(sf::Image &image, float X, float Y, int W, int H, std::string Name, float Speed, Direction Dir)
	: Entity(image, X, Y, W, H, Name, Speed, Dir){
	    if (name == "Bullet1" || name == "Bullet2") {
            spriteX = 263; spriteY = 102;
            x += w/2-1; y += h/2;
            w = 2; h = 2;
        }
	    sprite.setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
	}

    void control(float time){
        if      (dir == Direction::up)      {dy = -speed; dx = 0;}
        else if (dir == Direction::down)    {dy = speed; dx = 0;}
        else if (dir == Direction::left)    {dx = -speed; dy = 0;}
        else if (dir == Direction::right)   {dx = speed; dy = 0;}
    }

	void update(float time){
        control(time);
        x += dx * time;
        y += dy * time;
        interactionWithMap();
        sprite.setPosition(x, y);
	}

	void interactionWithMap(){
        /// limit the movement to the borders of the map
        if (x < 0 || y < 0 || x > WIDTH_MAP*SPRITE_W-SPRITE_W/2
            || y > HEIGHT_MAP*SPRITE_H-SPRITE_H/2) {life = false; return; }
                /// collisions with map objects
                int i = y/SPRITE_H, j = x/SPRITE_W;
                /// solid objects destroy bullets
                if (tileMap[i][j] == '*' || tileMap[i][j] == '#'){
                    if (dy > 0) {y = i*SPRITE_H-SPRITE_H; life = false; return;}
                    else if (dy < 0) {y = i*SPRITE_H+SPRITE_H; life = false; return;}
                    else if (dx > 0) {x = j*SPRITE_W-SPRITE_W; life = false; return;}
                    else if (dx < 0) {x = j*SPRITE_W+SPRITE_W; life = false; return;}
                }
    }
};

#endif // BULLET_H_INCLUDED
