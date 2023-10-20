//
// Created by Noe Steiner on 19/10/2023.
//

#ifndef FRACTALFORGE_JULIA_H
#define FRACTALFORGE_JULIA_H


#include "Fractal.h"
#include <map>

class Julia : public Fractal {
private:
    sf::Vector2f c;
    void updateShader();
    std::map<std::string, sf::Vector2f> parameters = {
            {"0", sf::Vector2f(0, 0)},
            {"-0.56 + 0.395i", sf::Vector2f(-0.56, 0.395)},
            {"-0.56 + 0.645i", sf::Vector2f(-0.56, 0.645)},
            {"-0.514 + 0.58i", sf::Vector2f(-0.514, 0.58)},
            {"-0.4 + 0.582i", sf::Vector2f(-0.4, 0.582)},
            {"0.32 + 0.035i", sf::Vector2f(0.32, 0.035)},
            {"-0.0519 + 0.688i", sf::Vector2f(-0.0519, 0.688)}
    };


public:
    Julia(sf::RenderWindow *window, sf::Shader *shader, sf::RectangleShape *background, sf::Clock *clock,
          sf::Vector2f* offset, sf::Vector2f resolution, float *zoom);

    void displayParameters() override;
    void loadShader() override;
    void update() override;

};


#endif //FRACTALFORGE_JULIA_H
