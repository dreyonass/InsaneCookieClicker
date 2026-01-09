#include <iostream>
#include <Windows.h>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <sstream>
#include <string>

#include <chrono>
#include <vector>
using namespace std;
void LoadFont(sf::Font& font, string str)
{
    cerr << "Error could not find file:: " << str << "!!" << endl;
}
int main()
{
    unsigned int width = 800;
    unsigned int height = 600;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "My window");


    const sf::Font font("Fonts/arial.ttf");

    sf::Text text(font);
    text.setString("grazus sausainis");
    text.setOrigin(text.getGlobalBounds().size / 2.0f);
    text.setPosition({ width / 2.0f, height / 3.0f });
    text.setFillColor(sf::Color::White);
    int kiek = 0;

    sf::CircleShape sausainis(50.f);
    sausainis.setFillColor(sf::Color::Yellow);
    sausainis.setPosition({ width / 2.0f - 50.f, height / 2.0f - 50.f });

    // Track previous mouse button state so we count only on transition
    bool mouseWasPressed = false;
    vector<sf::Vector2i> mousePositions;

    // Sampling setup: sample every 500 ms (half second)
    using clock = std::chrono::steady_clock;
    const std::chrono::milliseconds sampleInterval(500);
    auto lastSample = clock::now();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // Read current mouse state
        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // If currently pressed but was not pressed last frame -> count one click
        if (mousePressed && !mouseWasPressed)
        {
            // Get mouse position at time of press (window coordinates)
            sf::Vector2i mpos_i = sf::Mouse::getPosition(window);
            sf::Vector2f mpos(static_cast<float>(mpos_i.x), static_cast<float>(mpos_i.y));

            // Compute circle center (position is top-left of bounding box)
            float radius = sausainis.getRadius();
            sf::Vector2f circlePos = sausainis.getPosition();
            sf::Vector2f center(circlePos.x + radius, circlePos.y + radius);

            // Check point-in-circle
            float dx = mpos.x - center.x;
            float dy = mpos.y - center.y;
            if (dx * dx + dy * dy <= radius * radius)
            {
                // Only increment if the mouse was over the sausainis when clicked
                kiek += 1;
            }
        }

        // Update previous state for next frame
        mouseWasPressed = mousePressed;

        sf::Text text2(font);
        text2.setString("kiekis: " + to_string(kiek));

        // Sample mouse position at the desired interval
        auto now = clock::now();
        if (now - lastSample >= sampleInterval)
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            mousePositions.push_back(pos);

            // cap history size to avoid unbounded growth
            if (mousePositions.size() > 1000)
                mousePositions.erase(mousePositions.begin());

            // print only the sampled position and the count (not every frame)
            std::cout << "Pozicija: " << pos.x << ',' << pos.y
                << "  (count=" << mousePositions.size() << ")\n";

            lastSample = now;
        }

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(text);
        window.draw(sausainis);
        window.draw(text2);
        // end the current frame
        window.display();
    }
}