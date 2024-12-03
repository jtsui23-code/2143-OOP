#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "diceRoll.hpp"  // include animation for dice roll
#include "grid.hpp"      // include grid


int main() {
    // Create a SFML window
    int height = 1200;
    int width = 800;
    sf::RenderWindow window(sf::VideoMode(height, width), "KnuckleBone");

    //(3 x 3, 100.f size cells, start x 200.f start y 100.f, space between cells)
    Grid grid1(3,3, 125.f, 120.f, 80.f);
    Grid grid2(3,3, 125.f, width - 25.f, 80.f);


     // Load a texture
    sf::Texture buttonTexture;

    if (!buttonTexture.loadFromFile("media/Buttons/Red.png")) {
        std::cerr << "Error: Could not load texture 'Red.png'\n";
        return -1;
    }

    sf::RectangleShape button(sf:: Vector2f(200.f, 100.f));
    button.setPosition(500.f,630.f);

    button.setTexture(&buttonTexture);


    // Load font
    sf::Font font;
    if (!font.loadFromFile("media/fonts/arial.ttf")) {
        // Handle error
        return -1;
    }

    std:: vector< sf::Text> grid1Num;
    std:: vector< sf::Text> grid2Num;

    sf::Text roll("Space", font, 50);
    roll.setPosition(530.f, 640.f);
    roll.setFillColor(sf::Color::White);

    sf::Text instructionText("Enter your Players name:", font, 24);
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    sf::Text nameText("", font, 24);
    nameText.setPosition(350, 200);
    nameText.setFillColor(sf::Color::Green);

    sf::Text displayName("", font, 45);
    displayName.setPosition(300, 25);
    displayName.setFillColor(sf::Color::Yellow);

    sf::Text displayName2("", font, 45);
    displayName2.setPosition(950, 25);
    displayName2.setFillColor(sf::Color::Yellow);

    // Variables for input handling
    std::string userInput[2] = {"", ""};
    bool nameEntered[2] = {false, false};
    int i = 0;
    int g1 = 0;
    int g2 = 0;

    // Seed the random number generator for the dice roll
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a DiceRollAnimation instance
    DiceRollAnimation diceRoll("media/animations/dice_roll/", "frame_", sf::milliseconds(5));  // Adjust frame duration here
    if (!diceRoll.loadFrames(1, 24)) {  // Adjust the frame range to match your dice frames
        std::cerr << "Failed to load dice roll frames!" << std::endl;
        return -1; // Exit if frame loading fails
    }
    
    // Set initial position for the dice animation
    diceRoll.setPosition(900.f, 570.f);

    int diceNum = 0;
    bool firstTurn = true;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if(event.type == sf:: Event:: MouseButtonPressed && event.mouseButton.button == sf:: Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if(firstTurn)
                {
                    firstTurn = !firstTurn;

                    auto cell1 = grid1.getCellPos(mousePos);
                    if(cell1.first != -1 && cell1.second != -1)
                    {
                        //draw randomNumber on the cell
                        grid1Num[g1].setPosition(cell1.first, cell1.second);
                        grid1Num[g1].setString(std::to_string(diceNum));
                        grid1Num[g1].setFont(font);
                        grid1Num[g1].setCharacterSize(25);
                        g1++;
                    }
                }
                else
                {
                    firstTurn = !firstTurn;

                    auto cell2 = grid2.getCellPos(mousePos);
                    if(cell2.first != -1 && cell2.second != -1)
                    {
                        //draw randomNumber on cell
                        grid2Num[g2].setPosition(cell2.first, cell2.second);
                        grid2Num[g2].setString(std::to_string(diceNum));
                        grid2Num[g2].setFont(font);
                        grid2Num[g2].setCharacterSize(25);
                        g2++;
                    }
                }

            }
                if (!nameEntered[i] && i < 2) 
                {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == '\b') {
                            // Handle backspace
                            if (!userInput[i].empty()) {
                                userInput[i].pop_back();
                            }
                        } else if (event.text.unicode == '\r') {
                            // Handle enter
                            nameEntered[i] = true;
                            
                            if (i == 0)
                            {

                            
                                displayName.setString(userInput[0]);
                            }
                            if (i == 1)
                            {
                                displayName2.setString(userInput[1]);
                            }

                            if (i < 1)
                            {
                                i++;
                            }
                        } else if (event.text.unicode < 128) {
                            // Handle valid characters
                            userInput[i] += static_cast<char>(event.text.unicode);
                        }

                        nameText.setString(userInput[i]);
                    }
                }
            


            // Start the animation on space key press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                diceRoll.startAnimation(); // Start the animation when Space is pressed
                diceNum = diceRoll.getRandomFrame();
            }

        }

        // Update the animation
        diceRoll.update();

        window.clear(sf::Color::Black);
        // Draw the appropriate text
        if (!nameEntered[i] && i < 2) 
        {
            window.draw(instructionText);
            window.draw(nameText);
        } 

        else
        {
            grid1.draw(window);
            grid2.draw(window);
            window.draw(button);
            window.draw(roll);
            window.draw(displayName);
            window.draw(displayName2);
            diceRoll.draw(window);           // Draw the dice animation
            for(int a; a < grid1Num.size(); a++)
            {
                window.draw(grid1Num[a]);
            }
            for (int b; b < grid2Num.size(); b++)
            {
                window.draw(grid2Num[b]);

            }

            window.display(); 
        }
        

        // Display everything
        window.display();

        // Render the window
        //window.clear(sf::Color::White);  // Clear the window with a white color
        

    }

    return 0;
}
