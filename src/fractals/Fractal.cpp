//
// Created by Noe Steiner on 19/10/2023.
//

#include "Fractal.h"
#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

Fractal::Fractal(sf::RenderWindow *window, sf::Shader *shader, sf::RectangleShape *background, sf::Clock *clock,
                 sf::Vector2f offset, sf::Vector2f resolution, float zoom) {

    this->window = window;
    this->shader = shader;
    this->background = background;
    this->clock = clock;
    this->offset = offset;
    this->resolution = resolution;
    this->zoom = zoom;

}
