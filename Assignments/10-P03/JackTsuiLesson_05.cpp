#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 5: Drawing the Game Grid");

    sf:: Font font;

    if(!font.loadFromFile("media/fonts/Bebas.ttf"))
    {
        std:: cerr << "Error loading font" << std::endl;
        return -1;

    }

    sf:: Text text;
    text.setFont(font);


    // Grid configuration
    const int rows = 5;
    const int cols = 5;
    const float cellSize = 100.f; // Width and height of each cell
    const float gridStartX = 200.f; // Starting X position of the grid
    const float gridStartY = 100.f; // Starting Y position of the grid
    const float cellSpacing = 0.f; // Spacing between cells

    // Vector to hold grid cells
    std::vector<sf::RectangleShape> grid;

    // Create the grid cells
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setFillColor(sf::Color::White); // Default cell color
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(2.f);

            // Calculate cell position
            float x = gridStartX + col * (cellSize + cellSpacing);
            float y = gridStartY + row * (cellSize + cellSpacing);
            cell.setPosition(x, y);


            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(24);

            text.setString(std:: to_string(row + 1) + ", " + std:: to_string(col + 1));
            text.setPosition(x + 30.f, y + 30.f);


            // Add the cell to the grid
            grid.push_back(cell);
        }
    }

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Render
        window.clear(sf::Color::White);
        for (const auto& cell : grid) {
            window.draw(cell);
            window.draw(text);

        }
        window.display();
    }

    return 0;
}