#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
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
    // create the window
    sf::RenderWindow window(sf::VideoMode({ width, height }), "My window");
    //sf::Font font("C:\Users\Drey\source\repos\ConsoleApplication1\ConsoleApplication1\x64\Debug\arial.ttf");
	sf::Font font;
    LoadFont(font, "Fonts/arial.ttf");

    sf::Text text(font);
	text.setString("Hello SFML");
    text.setOrigin(text.getGlobalBounds().size / 2.0f);
    text.setPosition({ width / 2.0f, height / 2.0f });
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Red);
    text.setOutlineThickness(1.0f);
    // run the program as long as the window is open
    while (window.isOpen())
    {
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
        // end the current frame
        window.display();
    }
}