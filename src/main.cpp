#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(3840, 2160), "FractalForge");
    window.setFramerateLimit(60);
    sf::Shader fullScreenShader;
    ImGui::SFML::Init(window);

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    int fractal = 0;
    int previousFractal = -1;
    fullScreenShader.loadFromFile("shaders/julia.glsl", sf::Shader::Fragment);
    fullScreenShader.setUniform("resolution", sf::Vector2f(window.getSize()));
    fullScreenShader.setUniform("zoom", 2.0f);
    fullScreenShader.setUniform("offset", sf::Vector2f(-1.0f, -1.0f));
    fullScreenShader.setUniform("juliaC", sf::Vector2f(0.2f,0.2f ));
    sf::Vector2f c(0.2f, 0.2f);
    float zoom = 2.0f;
    sf::Clock deltaClock;
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event); // Corrected event processing for ImGui

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(); // Clear window at the beginning of the frame
        float elapsedTime = clock.getElapsedTime().asSeconds();
        // Changer l'angle pour modifier l'ensemble de Julia
        float angle = elapsedTime * 0.1f;
        // Mettre à jour la constante complexe pour l'ensemble de Julia en fonction de l'angle
        fullScreenShader.setUniform("juliaC", c);
        fullScreenShader.setUniform("zoom", zoom);
        window.draw(background, &fullScreenShader); // Draw background with shader

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Select Fractal");
        ImGui::Combo("Fractal", &fractal, "Julia\0");
        ImGui::End();

        ImGui::Begin("c complex");
        ImGui::SliderFloat("c real", &c.x, -1.0f, 1.0f, "%.9f");
        ImGui::SliderFloat("c imaginary", &c.y, -1.0f, 1.0f, "%.9f");
        ImGui::SliderFloat("zoom", &zoom, 0.0f, 10.0f, "%.9f");
        ImGui::End();

        ImGui::SFML::Render(window); // Render ImGui

        window.display(); // Display everything
    }


    ImGui::SFML::Shutdown();
}
