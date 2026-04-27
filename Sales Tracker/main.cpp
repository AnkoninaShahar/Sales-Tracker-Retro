#include <SFML/Graphics.hpp>
#include "ScreenManager.h"

int main()
{
	// Create an SFML render window with a specified video mode (width: 1120 pixels, height: 600 pixels) and title "Sale Tracker".
    sf::RenderWindow window(sf::VideoMode({ 1120, 600 }), "Sale Tracker");
    ScreenManager screen;

	// Main application loop that continues until the window is closed. 
    // Inside the loop, events are polled and processed to handle user interactions such as closing the window, scrolling with the mouse wheel, and editing items with keyboard input. 
    // The window is cleared, the current screen is rendered, and the display is updated to reflect any changes made during the event processing.
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
		screen.Render(window); // Render the current screen using the ScreenManager instance, which handles the drawing of all UI elements and interactions based on the current state of the application.
        window.display();
    }
}