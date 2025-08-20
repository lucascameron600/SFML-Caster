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

    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);
    
    double oldTime = 0.0;
    sf::Time previousFrameTime = sf::Time::Zero;
    

    sf::Vector2<double> playerPos(5.0, 5.0);
    sf::Vector2<double> playerDir(1.0, 0.0);
    sf::Vector2<double> playerPlane(0.0, 0.9);

    sf::Font font;
    if (!font.loadFromFile("good timing bd.otf")) // Replace with your font file
    {
        // Handle error
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10, 10); // Adjust position as needed
    double mouseSensitivity = 0.0002;

    while (window.isOpen()) {
        handleEvents(window);

      sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
      sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
      sf::Vector2<int> delta = mousePos - center;
      sf::Mouse::setPosition(center, window);


        window.clear(sf::Color{ 55, 55, 55 });

    
        sf::Time currentTime = clock.getElapsedTime();
        sf::Time deltaTime = currentTime - previousFrameTime;
        previousFrameTime = currentTime;

        // Calculate FPS
        float fps = 1.0f / deltaTime.asSeconds();
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

        double frameTime = calcFrameTime(clock, oldTime);
        double moveSpeed = frameTime * 10.0;
        double rotSpeed = frameTime * 3.0;

        handleMouseMovement(window,playerDir,playerPlane,mouseSensitivity, delta);
        movement(worldMap, playerPos, playerDir, playerPlane, moveSpeed, rotSpeed);
        //castFloornCeiling(window, worldMap, playerPos, playerDir, playerPlane);
        castRays(window, worldMap, playerPos, playerDir, playerPlane);
        
        window.draw(fpsText);
        window.display();
    }

    return 0;
}
