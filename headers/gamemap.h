/// Map of the game
/// Cannot step on:     * - BRICK, # - CONCRETE, W - WATER,  1 - HEADQUARTERS
/// Can step on:        G - GREEN BUSHES
/// Pickable items:     S - STAR, B - FreezingBomb;

#pragma once

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SFML\Graphics.hpp>

constexpr int SPRITE_W = 15;
constexpr int SPRITE_H = 15;
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 25;

sf::String tileMap[HEIGHT_MAP] = {
"0000000000000000000000000",
"000000####00000WWWWWW0000",
"000000000#000000000000000",
"000000000#000000B00000000",
"00S000000#00000000000000S",
"0000000000000000000000000",
"0000000000000000000000000",
"GGG00000000WWWWWW00000000",
"0000000000000WWWWWW000000",
"000000000000000WWWWWW0000",
"0000000##0000000000000000",
"000000##00000000000*00000",
"00000##000000000000*00000",
"0#####GGG0000000000*****0",
"0000000000000000000*00000",
"0S00000000000000GGG*00000",
"0000000000000000****00000",
"0000000S00000000*00000000",
"00000WWWWW000000000000000",
"00000000000###0000000##00",
"0000000000000000000000000",
"0##00##0000000000##000000",
"0000000000000000000000000",
"00000000000***00000000000",
"00000000000*1*00000000000",
};

#endif // MAP_H_INCLUDED
