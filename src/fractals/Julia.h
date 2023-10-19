//
// Created by Noe Steiner on 19/10/2023.
//

#ifndef FRACTALFORGE_JULIA_H
#define FRACTALFORGE_JULIA_H


#include "Fractal.h"

class Julia : public Fractal {
private:
    sf::Vector2f c;
    void updateShader();

public:
    Julia(sf::RenderWindow *window, sf::Shader *shader, sf::RectangleShape *background, sf::Clock *clock,
          sf::Vector2f offset, sf::Vector2f resolution, float zoom);

    void displayParameters() override;
    void loadShader() override;
    void update();

};


#endif //FRACTALFORGE_JULIA_H
