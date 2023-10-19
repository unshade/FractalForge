//
// Created by Noe Steiner on 19/10/2023.
//

#ifndef FRACTALFORGE_FRACTAL_H
#define FRACTALFORGE_FRACTAL_H

#include <SFML/Graphics.hpp>


class Fractal {
public:
    virtual void loadShader(const sf::RenderWindow& window) = 0;
    virtual void update(const sf::RenderWindow& window, float elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif //FRACTALFORGE_FRACTAL_H
