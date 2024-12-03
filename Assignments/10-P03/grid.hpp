#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <utility>


class Grid {
private:
    int rows, cols;                        // Grid dimensions
    float cellSize;                        // Size of each cell
    float gridStartX, gridStartY;          // Starting position of the grid
    float cellSpacing;                     // Spacing between cells
    std::vector<sf::RectangleShape> grid;  // Vector to hold the grid cells

public:
    // Constructor to initialize the grid
    Grid(int rows, int cols, float cellSize, float gridStartX, float gridStartY, float cellSpacing = 0.f)
        : rows(rows), cols(cols), cellSize(cellSize), gridStartX(gridStartX), gridStartY(gridStartY), cellSpacing(cellSpacing) {
        // Create the grid cells
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setFillColor(sf::Color::Black); // Default cell color
                cell.setOutlineColor(sf::Color::White);
                cell.setOutlineThickness(2.f);

                // Calculate cell position
                float x = gridStartX + col * (cellSize + cellSpacing);
                float y = gridStartY + row * (cellSize + cellSpacing);
                cell.setPosition(x, y);

                // Add the cell to the grid
                grid.push_back(cell);
            }
        }
    }

    // this method checks if the mouse is on any of the 
    // cells in the grid
    std::pair< int, int> getCellPos(const sf::Vector2f& pos)
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col; col < cols; ++col)
            {
                // x is the left side of cell
                // y is the top side of the cell
                // (0,0) is at top left of window & cell
                float x = gridStartX + col * (cols + cellSpacing);
                float y = gridStartY + row * (rows + cellSpacing); 
            }
            if (pos.x >= x && pos.x <= x + cellSize 
                && pos.y >= y && pos.y <= y + cellSize)
                {
                    return {rol, col};
                }
        }
        return {-1, -1};
    }

    // Function to draw the grid
    void draw(sf::RenderWindow& window) {
        for (const auto& cell : grid) {
            window.draw(cell);
        }
    }
};