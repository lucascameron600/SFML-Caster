#ifndef CASTER_H
#define CASTER_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

void handleEvents(sf::RenderWindow& window);

double calcFrameTime(sf::Clock& clock, double& oldTime);

void movement(const int worldMap[24][24],
                     sf::Vector2<double>& playerPos,
                     sf::Vector2<double>& playerDir,
                     sf::Vector2<double>& playerPlane,
                     double moveSpeed,
                     double rotSpeed);

void castRays(sf::RenderWindow& window,
                       const int worldMap[24][24],
                       sf::Vector2<double>& playerPos,
                       sf::Vector2<double>& playerDir,
                       sf::Vector2<double>& playerPlane);

#endif 
