#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "diceRoll.hpp"  // include animation for dice roll
#include "grid.hpp"      // include grid


int main() {
    // Create a SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "KnuckleBone");

    //(3 x 3, 100.f size cells, start x 200.f start y 100.f, space between cells)
    Grid grid1(3,3, 75.f, 45.f, 80.f);
    Grid grid2(3,3, 75.f, 500.f, 80.f);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("media/fonts/arial.ttf")) {
        // Handle error
        return -1;
    }

    sf::Text instructionText("Enter your Players name:", font, 24);
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    sf::Text nameText("", font, 24);
    nameText.setPosition(300, 200);
    nameText.setFillColor(sf::Color::Green);

    sf::Text displayName("", font, 30);
    displayName.setPosition(55, 25);
    displayName.setFillColor(sf::Color::Yellow);

    sf::Text displayName2("", font, 30);
    displayName2.setPosition(550, 25);
    displayName2.setFillColor(sf::Color::Yellow);

    // Variables for input handling
    std::string userInput[2] = {"", ""};
    bool nameEntered[2] = {false, false};
    int i = 0;

    // Seed the random number generator for the dice roll
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a DiceRollAnimation instance
    DiceRollAnimation diceRoll("media/animations/dice_roll/", "frame_", sf::milliseconds(1));  // Adjust frame duration here
    if (!diceRoll.loadFrames(1, 24)) {  // Adjust the frame range to match your dice frames
        std::cerr << "Failed to load dice roll frames!" << std::endl;
        return -1; // Exit if frame loading fails
    }
    
    // Set initial position for the dice animation
    diceRoll.setPosition(550.f, 400.f);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
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

                            i++;
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
            window.draw(displayName);
            diceRoll.draw(window);           // Draw the dice animation
            window.display(); 
        }
        

        // Display everything
        window.display();

        // Render the window
        //window.clear(sf::Color::White);  // Clear the window with a white color
        

    }

    return 0;
}
