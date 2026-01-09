#include <iostream>
#include <Windows.h>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <sstream>
#include <string>
#include <random>
#include <chrono>

using namespace std;
void LoadFont(sf::Font &font, string str)
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
    int veik = 0;

    sf::CircleShape sausainis(50.f);
	sausainis.setFillColor(sf::Color::Yellow);
	sausainis.setPosition({ width / 2.0f - 50.f, height / 2.0f - 50.f });

    // Track previous mouse button state so we count only on transition
    bool mouseWasPressed = false;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // Read current mouse state
        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // If currently pressed but was not pressed last frame -> count one click
        if (mousePressed && !mouseWasPressed)
        {
            kiek += 1;
        }

        // Update previous state for next frame
        mouseWasPressed = mousePressed;

        sf::Text text2(font);
        text2.setString("kiekis: " + to_string(kiek));

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
        // window.draw(...);
		window.draw(text);
		window.draw(sausainis);
		window.draw(text2);
        // end the current frame
        window.display();
    }
}