#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
// Create a window
sf::RenderWindow window(sf::VideoMode(800, 600), "Knuckle Bones 02");

    sf::ConvexShape convex;

    convex.setPointCount(5);

    convex.setPoint(0, sf:: Vector2f(200.f, 200.f));
    convex.setPoint(1,sf::Vector2f(200.f, 300.f));
    convex.setPoint(2,sf::Vector2f(200.f, 400.f));
    convex.setPoint(3,sf::Vector2f(500.f, 200.f));
    convex.setPoint(4,sf::Vector2f(500.f, 400.f));

    convex.setFillColor(sf::Color::Red);
    
    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f)); // 200x100 rectangle
    rectangle.setFillColor(sf::Color::Blue);                  // Set the fill color
    rectangle.setPosition(100.f, 100.f);                      // Set the position

    // Create a circle
    sf::CircleShape circle(50.f); // Circle with radius 50
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(100.f, 200.f);

    // Load a texture
    sf::Texture texture;
    if (!texture.loadFromFile("media/images/1.png")) {
        std::cerr << "Error: Could not load texture '1.png'\n";
        return -1;
    }

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(300.f, 300.f); // Set sprite position

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a white background
        window.clear(sf::Color::White);

        // Draw the shapes and sprite
        window.draw(convex);
        window.draw(rectangle);
        window.draw(circle);
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return 0;

}