#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <SFML/System/Clock.hpp>
int main() { 
    sf::RenderWindow window(sf::VideoMode(screenWidth,screenHeight), "SFML Raycaster");

    sf::Vector2<double> playerPos(5.0, 5.0);
    sf::Vector2<double> playerDir(1.0, 0.0);
    sf::Vector2<double> playerPlane(0.0, 0.9); 
    double time = 0; //time of current frame
    double oldTime = 0;
    sf::Clock clock; 
        while(window.isOpen()) {

        sf::Event event{};
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        
        //handleInput();
        sf::Time elapsed = clock.getElapsedTime();
        double milliseconds = elapsed.asMilliseconds();
        oldTime = time;
        time = milliseconds;
        double frameTime = (time - oldTime) / 1000.0; 
        
        double moveSpeed = frameTime * 5.0; 
        double rotSpeed = frameTime * 3.0;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (worldMap[int(playerPos.x + playerDir.x * moveSpeed)][int(playerPos.y)] == 0)
                playerPos.x += playerDir.x * moveSpeed;
            if (worldMap[int(playerPos.x)][int(playerPos.y + playerDir.y * moveSpeed)] == 0)
                playerPos.y += playerDir.y * moveSpeed;
        }
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (worldMap[int(playerPos.x - playerDir.x * moveSpeed)][int(playerPos.y)] == 0)
                playerPos.x -= playerDir.x * moveSpeed;
            if (worldMap[int(playerPos.x)][int(playerPos.y - playerDir.y * moveSpeed)] == 0)
                playerPos.y -= playerDir.y * moveSpeed;
        }
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            double oldDirX = playerDir.x;
            playerDir.x = playerDir.x * cos(-rotSpeed) - playerDir.y * sin(-rotSpeed);
            playerDir.y = oldDirX * sin(-rotSpeed) + playerDir.y * cos(-rotSpeed);
    
            double oldPlaneX = playerPlane.x;
            playerPlane.x = playerPlane.x * cos(-rotSpeed) - playerPlane.y * sin(-rotSpeed);
            playerPlane.y = oldPlaneX * sin(-rotSpeed) + playerPlane.y * cos(-rotSpeed);
        }
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            double oldDirX = playerDir.x;
            playerDir.x = playerDir.x * cos(rotSpeed) - playerDir.y * sin(rotSpeed);
            playerDir.y = oldDirX * sin(rotSpeed) + playerDir.y * cos(rotSpeed);
    
            double oldPlaneX = playerPlane.x;
            playerPlane.x = playerPlane.x * cos(rotSpeed) - playerPlane.y * sin(rotSpeed);
            playerPlane.y = oldPlaneX * sin(rotSpeed) + playerPlane.y * cos(rotSpeed);
        }
        


        for (int x = 0; x < screenWidth; ++x) {
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
                    (rayDir.y == 0.0) ? bignum : std::abs(1.0 / rayDir.y)
                    );
            double perpWallDist = 0.0;
            

            sf::Vector2<int> step(0, 0);

            if(rayDir.x < 0) {
                step.x = -1;
                sideDist.x =(playerPos.x - mapPos.x) * deltaDist.x;
            } else {
                step.x = 1;
                sideDist.x =(mapPos.x + 1.0 - playerPos.x) * deltaDist.x;
            }
                
            if(rayDir.y < 0) {
                step.y = -1;
                sideDist.y =(playerPos.y - mapPos.y) * deltaDist.y;
            } else {
                step.y = 1;
                sideDist.y =(mapPos.y + 1.0 - playerPos.y) * deltaDist.y;
            }

            int hit = 0;
            int side = 0;
            while (hit == 0) {
                if (sideDist.x < sideDist.y) {
                    sideDist.x += deltaDist.x;
                    mapPos.x += step.x;
                    side = 0;
                } else {
                    sideDist.y += deltaDist.y;
                    mapPos.y += step.y;
                    side = 1;
                }

                if (mapPos.x < 0 || mapPos.x >= mapWidth || mapPos.y < 0 || mapPos.y >= mapHeight) {
                    hit =1;
                    break;
                }

                if (worldMap[mapPos.x][mapPos.y] > 0) hit = 1;
            }

            if (side == 0) perpWallDist = sideDist.x - deltaDist.x;
            else    perpWallDist = sideDist.y - deltaDist.y;

            int lineHeight = (perpWallDist > 0.0) ? int(screenHeight / perpWallDist) : screenHeight;

            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

            sf::Color col = sf::Color::Yellow;
            switch (worldMap[mapPos.x][mapPos.y]) {
                case 1: col = sf::Color::Red; break;
                case 2: col = sf::Color::Green; break;
                case 3: col = sf::Color::Blue; break;
                case 4: col = sf::Color::White; break;
                case 5: col = sf::Color(255, 128, 0); break;
                default: break;
            }

            if (side == 1) col = sf::Color(col.r / 2, col.g / 2, col.b/2);

            sf::RectangleShape column(sf::Vector2(1.f, float(drawEnd - drawStart +1)));
            column.setPosition(float(x), float(drawStart));
            column.setFillColor(col);
            window.draw(column);

        }

        window.display();

    }
    return 0;
}
