#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Holds rectangular properties (position, size, and color). Provides a parameterized constructor, a copy constructor, and an assignment operator.
/// </summary>
namespace Helper
{
	// Struct to hold properties for graphical elements
    struct Properties {
        float x = 0, y = 0;
        float width = 0, height = 0;
        sf::Color color = sf::Color::White;

        Properties(float x = 0, float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color::White) : 
        x(x), y(y), width(width), height(height), color(color) {}

        Properties(const Properties& properties) {
            x = properties.x;
            y = properties.y;
            width = properties.width;
            height = properties.height;
            color = properties.color;
        }

        void operator=(const Properties& other) {
            x = other.x;
            y = other.y;
            width = other.width;
            height = other.height;
            color = other.color;
        }
    };
};

