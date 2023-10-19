//
// Created by Noe Steiner on 19/10/2023.
//

#ifndef FRACTALFORGE_FRACTAL_H
#define FRACTALFORGE_FRACTAL_H

#include <SFML/Graphics.hpp>

class Fractal {
protected:

    sf::Shader *shader{};
    sf::RectangleShape *background{};
    sf::RenderWindow *window{};
    sf::Clock *clock{};

    sf::Vector2f offset{};
    sf::Vector2f resolution{};

    float zoom{};

public :
    Fractal(sf::RenderWindow *window,
            sf::Shader *shader,
            sf::RectangleShape *background,
            sf::Clock *clock,
            sf::Vector2f offset,
            sf::Vector2f resolution,
            float zoom);

    virtual void displayParameters() = 0;

};

#endif //FRACTALFORGE_FRACTAL_H
