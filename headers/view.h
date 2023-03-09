#pragma once

#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <SFML/Graphics.hpp>

sf::View view;

void setView(float x, float y){ view.setCenter(x, y); }

void changeView(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) view.zoom(0.999f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) view.zoom(1.001f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) view.rotate(0.1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) view.setSize(500, 500);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) view.setSize(200, 200);
	///if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
}

#endif // VIEW_H_INCLUDED
