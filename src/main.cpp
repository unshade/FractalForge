#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

#include "fractals/Fractal.h"

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

    // Main engine loop
    while (window.isOpen()) {

        // -- EVENT HANDLING --
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // -- END EVENT HANDLING --

        // Update gui states
        window.clear();

        // ImGui update
        ImGui::SFML::Update(window, deltaClock.restart());



        ImGui::SFML::Render(window);

        // SFML update

        window.display();
    }


    ImGui::SFML::Shutdown();
}
