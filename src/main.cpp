#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

#include "fractals/Fractal.h"
#include "fractals/Julia.h"

int main() {

    // Window and ImGui setup
    sf::RenderWindow window(sf::VideoMode(3840, 2160), "FractalForge");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // Fractal shader setup
    sf::Shader fullScreenShader;
    sf::RectangleShape background(sf::Vector2f(window.getSize()));

    // Clocks
    sf::Clock deltaClock;
    sf::Clock clock;

    float zoom = 3.0f;
    sf::Vector2f offset(0, 0);

    // Fractal setup
    Julia julia(&window, &fullScreenShader, &background, &clock, &offset, sf::Vector2f(window.getSize()), &zoom);
    std::vector<Fractal *> fractals = {&julia};
    Fractal *currentFractal = nullptr;

    sf::Vector2i lastMousePosition;
    bool mouseDrag = false;

    // Main engine loop
    while (window.isOpen()) {

        // -- EVENT HANDLING --
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseDrag = true;
                    lastMousePosition = sf::Mouse::getPosition(window);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseDrag = false;
                }
            }

            // also check if not dragging an ImGui window
            if (event.type == sf::Event::MouseMoved && mouseDrag && !ImGui::IsAnyItemActive()) {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                sf::Vector2i delta = currentMousePosition - lastMousePosition;
                offset.x -= delta.x * (zoom / window.getSize().x);  // Ces facteurs peuvent être ajustés pour des déplacements plus doux
                offset.y += delta.y * (zoom / window.getSize().y);
                lastMousePosition = currentMousePosition;
            }
        }
        // -- END EVENT HANDLING --

        // Update gui states
        window.clear();

        // Fractal update
        if (currentFractal != nullptr) {
            currentFractal->update();
        }

        // ImGui update
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Select a fractal");
        if (ImGui::Button("Julia")) {
            julia.loadShader();
            currentFractal = &julia;
        }
        ImGui::SliderFloat("zoom", &zoom, 0.0f, 2.f, "%.9f");
        ImGui::End();

        if (currentFractal != nullptr) {
            currentFractal->displayParameters();
        }

        ImGui::SFML::Render(window);


        window.display();
    }


    ImGui::SFML::Shutdown();
}
