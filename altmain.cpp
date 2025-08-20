#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "constants.h"
#include "caster.h"

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,1,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,2,2,2,2,0,0,4},
  {4,0,0,1,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,5,2,0,0,4},
  {4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,4,4,2,2,2,2,0,0,4},
  {4,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,2,2,2,2,2,0,0,0,0,4,2,3,4,5,0,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
};
  int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Raycaster");
    sf::Clock clock;
    double oldTime = 0.0;

    sf::Vector2<double> playerPos(5.0, 5.0);
    sf::Vector2<double> playerDir(1.0, 0.0);
    sf::Vector2<double> playerPlane(0.0, 0.9);

    while (window.isOpen()) {
        handleEvents(window);

        window.clear(sf::Color(30, 30, 30));

        double frameTime = calcFrameTime(clock, oldTime);
        double moveSpeed = frameTime * 10.0;
        double rotSpeed = frameTime * 3.0;

        movement(worldMap, playerPos, playerDir, playerPlane, moveSpeed, rotSpeed);
        castFloornCeiling(window, worldMap, playerPos, playerDir, playerPlane);
        castRays(window, worldMap, playerPos, playerDir, playerPlane);
        

        window.display();
    }

    return 0;
}
