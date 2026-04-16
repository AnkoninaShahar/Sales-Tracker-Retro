#include <SFML/Graphics.hpp>
#include "ScreenManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1200, 600 }), "SFML works!");
    ScreenManager screen;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        screen.Render(window);
        window.display();
    }
}