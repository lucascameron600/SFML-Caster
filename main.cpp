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


}
