#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
// Create a window with a title and dimensions (800x600)
sf::RenderWindow window(sf::VideoMode(1024, 768), "Jack Tsui's KnuckleBones");

sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        sf:: Time elasped = clock.restart();
        float fps = 1.0f/elasped.asSeconds();
        std:: cout << "FPS: " << fps << std:: endl;
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user presses Escape or clicks the close button
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Clear the window with a specific color
        window.clear(sf::Color::Red);

        // Display the contents of the window
        window.display();
    }

    return 0;

}