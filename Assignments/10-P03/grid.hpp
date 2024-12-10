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
    std::vector<sf::Text> gridNum;
    std::string fontPath;
    sf::Font font;

public:
    // Constructor to initialize the grid
    Grid(){}
    Grid(int rows, int cols, float cellSize, float gridStartX, float gridStartY, std::string fontPath = "media/fonts/Arial.ttf",float cellSpacing = 0.f)
        : rows(rows), cols(cols), cellSize(cellSize), gridStartX(gridStartX), gridStartY(gridStartY), cellSpacing(cellSpacing)
        , fontPath(fontPath)
         {
        // Create the grid cells
        loadAssets();
        

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
                gridNum.push_back(sf::Text("0", font, 45));
                gridNum.back().setPosition(x + 50.f,y + 35.f);
                gridNum.back().setFillColor(sf::Color::White);

                // Add the cell to the grid
                grid.push_back(cell);
            }
        }
    }

    void loadAssets()
    {
        if (!font.loadFromFile(fontPath)) 
        {
        // Handle error
        std::cout << "Can't load font";
        }
    }

    std::vector<sf::Text> getGridNum()
    {
        return gridNum;
    }

    // this method checks if the mouse is on any of the 
    // cells in the grid
    // This method also checks if the player 
    // clicked on an empty cell so there is no 
    // overriding of current cell numbers.
    bool putNumOnClickedCell(const sf::Vector2f& pos, int diceNum)
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                int index = row * cols + col;
                // x is the left side of cell
                // y is the top side of the cell
                // (0,0) is at top left of window & cell
                float x = gridStartX + col * (cellSize + cellSpacing);
                float y = gridStartY + row * (cellSize + cellSpacing); 
                
                //If where the mouse clicked exists a cell then put
                // the dice number in that cell.

                if (pos.x >= x && pos.x <= x + cellSize 
                    && pos.y >= y && pos.y <= y + cellSize)
                    {
                        // Turns the dice number into a string so it can be 
                        // put into the gridNum Text
                        // can only put a dice number in the cell 
                        // if the cell is empty 

                        //This checks if the bottom most cell of the column 
                        // is empty. If the bottom most cell of the column is 
                        // empty then place the number there instead
                        if (gridNum[index + cols + cols].getString() == "0")
                        {
                            gridNum[index + cols + cols].setString(std::to_string(diceNum));
                            return true;
                        }

                        // This checks if the middle cell of the column is empty if the 
                        // midle cell of the column is empty then 
                        // place the dice number there instead
                        else if(gridNum[index + cols].getString() == "0")
                        {
                            gridNum[index + cols].setString(std::to_string(diceNum));
                            return true;
                        }

                        // This places the dice number on the clicked cell 
                        // because the cells under it in the same column are filled
                        else if(gridNum[index].getString() == "0")
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

    

    float getCellSize()
    {
        return cellSize;
    }
  

    // Function to draw the grid
    void draw(sf::RenderWindow& window) 
    {
        for (const auto& cell : grid)
         {
            window.draw(cell);
            
        }
        
        for(const auto& value:gridNum)
        {
            // This will only print the numbers 
            // on the grid if they are 1 - 6

            if(value.getString() != "0")
            {
                window.draw(value);
            }

        }
    }
};