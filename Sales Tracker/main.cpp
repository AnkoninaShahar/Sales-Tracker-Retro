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

            if (const auto* mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>())
                screen.Scroll(mouseWheel->delta, window);

            if (const auto* keyboard = event->getIf<sf::Event::TextEntered>())
                screen.EditItem(static_cast<char>(keyboard->unicode));
          
        }

        window.clear();
        screen.Render(window);
        window.display();
    }
}