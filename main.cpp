#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main() { 
    sf::RenderWindow window(sf::VideoMode(screenWidth,screenHeight). "SFML Raycaster");

    sf::Vector2<double> playerPos(5.0, 5.0);
    sf::Vector2<double> playerDir(1.0, 0.0);
    sf::Vector2<double> playerPlane(0.0, 0.9); 
    
    while(window.isOpen()) {

        sf::Event event{};
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        
        for (int x = 0, x < screenWidth; ++x) {
            double cameraX = 2.0 * x / double(screenWidth) - 1.0;
            sf::Vector2<double> rayDir(
                playerDir.x + playerPlane.x * cameraX,
                playerDir.y + playerPlane.y * cameraX
            );

            sf::Vector2<int> mapPos(int(playerPos.x), int(playerPos.y));

            sf::Vector2<double> sideDist;


            double bignum = 1e30;

            sf::Vector2<double> deltaDist(
                    (rayDir.x == 0.0) ? bignum : std::abs(1.0 / rayDir.x),
                    (rayDir.y == 0.0) ? bignum : std::abs(1.0 / rayDir.y),
                    );
            double perpWallDist = 0.0;

                

}
