//
// Created by Noe Steiner on 19/10/2023.
//

#include "Julia.h"

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

#include "iostream"

Julia::Julia(sf::RenderWindow *window, sf::Shader *shader, sf::RectangleShape *background, sf::Clock *clock,
             sf::Vector2f offset, sf::Vector2f resolution, float zoom) : Fractal(window, shader, background, clock,
                                                                                 offset, resolution, zoom) {

}

void Julia::displayParameters() {
    ImGui::Begin("Julia parameters");
    ImGui::SliderFloat("c real", &this->c.x, -1.0f, 1.0f, "%.9f");
    ImGui::SliderFloat("c imaginary", &this->c.y, -1.0f, 1.0f, "%.9f");
    ImGui::End();
}

void Julia::loadShader() {
    this->shader->loadFromFile("shaders/julia.glsl", sf::Shader::Fragment);
    this->shader->setUniform("resolution", this->resolution);
    this->shader->setUniform("offset", this->offset);
    this->shader->setUniform("zoom", this->zoom);
    this->shader->setUniform("c", this->c);
    this->window->draw(*this->background, this->shader);
}

void Julia::update() {
    this->updateShader();
}

void Julia::updateShader() {
    this->shader->setUniform("resolution", this->resolution);
    this->shader->setUniform("offset", this->offset);
    this->shader->setUniform("zoom", this->zoom);
    this->shader->setUniform("c", this->c);
    this->window->draw(*this->background, this->shader);
}
