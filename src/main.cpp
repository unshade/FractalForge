#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "FractalForge");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::RectangleShape background(sf::Vector2f(640, 480));
    background.setFillColor(sf::Color::Red);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.draw(background);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}