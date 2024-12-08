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
    std::vector<sf::Text> gridNum;         // Vector to hold the text (numbers) for the grid
    std::string fontPath;                  // Path to the font file
    sf::Font font;                         // Font object for rendering text

public:
    /**
     * Public: Grid()
     * 
     * Description:
     *      Default constructor for the Grid class.
     */
    Grid() {}

    /**
     * Public: Grid(int rows, int cols, float cellSize, float gridStartX, float gridStartY, std::string fontPath = "media/fonts/Arial.ttf", float cellSpacing = 0.f)
     * 
     * Description:
     *      Parameterized constructor to initialize grid attributes and create grid cells.
     * 
     * Params:
     *      - int rows: The number of rows in the grid.
     *      - int cols: The number of columns in the grid.
     *      - float cellSize: The size of each grid cell.
     *      - float gridStartX: The starting X coordinate for the grid.
     *      - float gridStartY: The starting Y coordinate for the grid.
     *      - std::string fontPath: The path to the font file.
     *      - float cellSpacing: The spacing between each cell.
     */
    Grid(int rows, int cols, float cellSize, float gridStartX, float gridStartY, std::string fontPath = "media/fonts/Arial.ttf", float cellSpacing = 0.f)
        : rows(rows), cols(cols), cellSize(cellSize), gridStartX(gridStartX), gridStartY(gridStartY), cellSpacing(cellSpacing), fontPath(fontPath) 
    {
        loadAssets();

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setFillColor(sf::Color::Black);  // Default cell color
                cell.setOutlineColor(sf::Color::White);
                cell.setOutlineThickness(2.f);

                // Calculate the position of each cell
                float x = gridStartX + col * (cellSize + cellSpacing);
                float y = gridStartY + row * (cellSize + cellSpacing);
                cell.setPosition(x, y);

                // Initialize the text for each cell with "0"
                gridNum.push_back(sf::Text("0", font, 45));
                gridNum.back().setPosition(x + 50.f, y + 35.f);
                gridNum.back().setFillColor(sf::Color::White);

                // Add the cell to the grid vector
                grid.push_back(cell);
            }
        }
    }

    /**
     * Public: loadAssets()
     * 
     * Description:
     *      Loads the font file specified in fontPath.
     * 
     * Returns:
     *      - void: No return value.
     */
    void loadAssets() 
    {
        if (!font.loadFromFile(fontPath)) 
        {
            std::cout << "Can't load font";  // Print error if font fails to load
        }
    }

    /**
     * Public: getGridNum()
     * 
     * Description:
     *      Returns the vector of grid numbers (sf::Text objects).
     * 
     * Returns:
     *      - std::vector<sf::Text>: The vector of text objects representing numbers in the grid.
     */
    std::vector<sf::Text> getGridNum() 
    {
        return gridNum;
    }


    /**
     * Public: putNumOnClickedCell(const sf::Vector2f& pos, int diceNum)
     * 
     * Description:
     *      Checks if the mouse click is on any cell and places the dice number in the first available empty cell in the clicked column.
     * 
     * Params:
     *      - const sf::Vector2f& pos: The mouse click position.
     *      - int diceNum: The number to place in the clicked cell.
     * 
     * Returns:
     *      - bool: True if the number was placed, false if the cell was full.
     */
    bool putNumOnClickedCell(const sf::Vector2f& pos, int diceNum) 
    {
        for (int row = 0; row < rows; ++row)
         {
            for (int col = 0; col < cols; ++col)
             {
                int index = row * cols + col;

                // Calculate cell boundaries
                float x = gridStartX + col * (cellSize + cellSpacing);
                float y = gridStartY + row * (cellSize + cellSpacing);

                // Check if the mouse click is within the current cell
                if (pos.x >= x && pos.x <= x + cellSize && pos.y >= y && pos.y <= y + cellSize)
                 {
                    // Place the number in the bottom-most empty cell of the column
                    // and checks if the cell is empty
                    if (gridNum[index + cols + cols].getString() == "0") 
                    {
                        gridNum[index + cols + cols].setString(std::to_string(diceNum));
                        return true;
                    }
                    else if (gridNum[index + cols].getString() == "0") 
                    {
                        gridNum[index + cols].setString(std::to_string(diceNum));
                        return true;
                    }

                    else if (gridNum[index].getString() == "0")
                    {
                        gridNum[index].setString(std::to_string(diceNum));
                        return true;
                    }

                    else
                    {
                        return false;
                    }
                }
            }
        }

        return false;
    }


    /**
     * Public: draw(sf::RenderWindow& window)
     * 
     * Description:
     *      Draws the grid and numbers onto the specified window.
     * 
     * Params:
     *      - sf::RenderWindow& window: The window where the grid will be drawn.
     * 
     * Returns:
     *      - void: No return value.
     */
    void draw(sf::RenderWindow& window) 
    {
        // Draw each grid cell
        for (const auto& cell : grid) 
        {
            window.draw(cell);
        }

        // Draw the grid numbers if they are not "0"
        for (const auto& value : gridNum) 
        {
            if (value.getString() != "0") 
            {
                window.draw(value);
            }
        }
    }
};
