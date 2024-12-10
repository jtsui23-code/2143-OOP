

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "diceRoll.hpp"  // include animation for dice roll
#include "grid.hpp"      // include grid
#include<string>
#include <map> 
#include<vector>





class Player {
private:
    std::string name;
    int score;

public:

    Player() : score(0) {}

    // Setters and Getters
    void setName(std:: string playerName) 
    {
        name = playerName;
    }

    std::string getName()
    {
        return name;
    }

    void setScore(int playerScore) {
        score = playerScore;
    }

    int getScore() const {
        return score;
    }

    void increaseScore(int points) 
    {
        score += points;
    }

    
};


class Game
{
    private:

    Player player[2];

    int height;
    int width;
 
    Grid grid1;
    Grid grid2;

    sf::RenderWindow* window;

    sf::Texture buttonTexture;
    sf:: Texture turnSkin;
    sf:: RectangleShape turnIndicator;    
    sf::RectangleShape button;

    std:: vector< sf::Text> grid1Num;
    std:: vector< sf::Text> grid2Num;

    sf::Text roll;

    sf::Text instructionText;
    sf::Text nameText;
    sf::Font font;
    sf::Text displayName;
    sf::Text displayName2;

    std::string userInput[2];
    bool nameEntered[2] = {false, false};
    int i;
    int g1;
    int g2;
    sf:: Text score1;
    sf:: Text score2;

    sf:: Text score1Display;
    sf:: Text score2Display;   

    // Create a DiceRollAnimation instance
    DiceRollAnimation diceRoll;  

    int diceNum;
    bool firstTurn;
    int diceRolls;



    public:

    Game(sf::RenderWindow &w) : grid1(3, 3, 125.f, 120.f, 80.f), grid2(3, 3, 125.f, 800.f - 25.f, 80.f), window(&w),
    turnIndicator(sf:: Vector2f(150.f, 200.f)), button(sf:: Vector2f(200.f, 100.f)), roll("Space", font, 50)
    ,instructionText("Enter your Players' name:", font, 24), nameText("", font, 24), displayName("", font, 45)
    , displayName2("", font, 45), score1("Score: ", font, 45), score2("Score: ", font, 45), score1Display("Score: ", font, 45)
    ,score2Display("Score: ", font, 45), diceRoll("media/animations/dice_roll/", "frame_", sf::milliseconds(50))

    {
    height = 1200;
    width = 800;

    loadAssets();

    turnIndicator.setPosition(sf::Vector2f(550.f, 450.f));
    turnIndicator.setTexture(&turnSkin);

    button.setPosition(535.f,630.f);
    button.setTexture(&buttonTexture);

    //Fills in 9 indexs with empty text 
    grid1Num.resize(9, sf::Text("0", font, 45));
    grid2Num.resize(9, sf::Text("0", font, 45));

    roll.setPosition(565.f, 640.f);
    roll.setFillColor(sf::Color::White);

    // Prompts for player name input
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    nameText.setPosition(350, 200);
    nameText.setFillColor(sf::Color::Green);

    displayName.setPosition(300, 25);
    displayName.setFillColor(sf::Color::Yellow);

    displayName2.setPosition(950, 25);
    displayName2.setFillColor(sf::Color::Yellow);


    score1.setFillColor(sf::Color:: White);
    score2.setFillColor(sf::Color::White);
    score1.setPosition(400.f, 455.f);
    score2.setPosition(width + 250.f, 455.f);

    score1Display.setFillColor(sf::Color:: White);
    score2Display.setFillColor(sf::Color::White);
    score1Display.setPosition(250.f, 450.f);
    score2Display.setPosition(width + 100.f, 450.f);

    // Set initial position for the dice animation
    diceRoll.setPosition(900.f, 560.f);

    diceRoll.setScale(1.2f,1.2f);

    userInput[0] = {""};
    userInput[1] = {""};

    nameEntered[0] = {false};
    nameEntered[1] = {false};
    i = 0;
    g1 = 0;
    g2 = 0;

     diceNum = 0;
     firstTurn = true;
     diceRolls = 1;


    }

    void loadAssets()
    {
        if (!buttonTexture.loadFromFile("media/extra/Red.png")) 
        {
        std::cerr << "Error: Could not load texture 'Red.png'\n";

        }

        if (!turnSkin.loadFromFile("media/extra/Player1.png" )) 
        {
        std::cerr << "Error: Could not load texture 'Player1.png'\n";
        }

        if (!font.loadFromFile("media/fonts/arial.ttf")) 
        {
        // Handle error
        std::cout << "Can't load font";
        }

        if (!diceRoll.loadFrames(1, 24)) 

        {  
        std::cerr << "Failed to load dice roll frames!" << std::endl;
        }

    }

    void checkMouse(sf::Event event)
    {
        

        
        if(event.type == sf:: Event:: MouseButtonPressed && event.mouseButton.button == sf:: Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if(diceNum > 0)
                {

                    if(firstTurn)
                    {
                        diceRolls++;
                        
                        if(grid1.putNumOnClickedCell(mousePos, diceNum))
                        {
                            if ( g1 < 9)
                            {
                                grid1Num = grid1.getGridNum();
                                g1++;
                            }
                            diceNum = 0;
                            firstTurn = !firstTurn;
                        }
                        
                    }
                    else if(!firstTurn)
                    {
                        diceRolls++;
  
                        if(grid2.putNumOnClickedCell(mousePos, diceNum))
                        {
                            if(g2 < 9)
                            {
                                grid2Num = grid2.getGridNum();
                                g2++;
                            }

                            diceNum = 0;
                            firstTurn = !firstTurn;
                        }
                    }
                }
           }    


    }

    void close()
    {
        window->close();
    }

    bool isOpen()
    {
        return window->isOpen();
    }

    void inputNames(sf::Event event)
    {
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

                    if (i == 0) {
                        displayName.setString(userInput[0]);
                    }
                    if (i == 1) {
                        displayName2.setString(userInput[1]);
                    }

                    if (i < 1) {
                        i++;
                    }
                } else if (event.text.unicode < 128) {
                    // Handle valid characters
                    userInput[i] += static_cast<char>(event.text.unicode);
                }

                nameText.setString(userInput[i]);
            }
        }
    }


    
    

    void rollDice(sf::Event event)
    {
        // Start the animation on space key press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (diceRolls != 0)
                {
                    if(g2 < 9)
                    {

                        diceRoll.startAnimation(); // Start the animation when Space is pressed
                        diceNum = diceRoll.getRandomFrame();
                        diceRolls--;
                    }
                }
            }
    }

    void updateDice()
    {
        diceRoll.update();
    }

    void clear()
    {
    window->clear(sf::Color::Black);
    }

    void updateGame()
    {

        // This will make the game remain on the 
        // player input screen until both player has entered their 
        // names
         if (!nameEntered[i] && i < 2) 
        {
            window->draw(instructionText);
            window->draw(nameText);
        } 
        
        // This is the game screen
        // that appears after both players have entered their names 
        // 
        else
        {
            if (firstTurn)
            {
                turnIndicator.setScale(1.f,1.f);
                turnIndicator.setPosition(sf::Vector2f(550.f, 450.f));
            }
            if (!firstTurn)
            {
                turnIndicator.setScale(-1.f, 1.f);
                // If you don't reoffset the position
                // then the image will be positioned off to the left
                turnIndicator.setPosition(sf::Vector2f(550.f + 150.f , 450.f));
            }

            window->draw(turnIndicator);

            // Makes a copy of the vector of Text 
            // Containing all of the numbers on a single grid
            grid1Num = grid1.getGridNum();
            grid2Num = grid2.getGridNum();

            // Displays the grid and the numbers in each of the 
            // grid cells
            grid1.draw(*window);
            grid2.draw(*window);

            // renders the roll button on the screen
            window->draw(button);
            window->draw(roll);

            //Displays both players' names
            window->draw(displayName);
            window->draw(displayName2);

            // Displays both players' score
            window->draw(score1Display);
            window->draw(score2Display);

            diceRoll.draw(*window);           // Draw the dice animation


            // Gets the calculated scores for each player with the 
            // multiplier for any of the same numbers in the common column
            int sc1 = calculateScore(grid1Num);
            int sc2 = calculateScore(grid2Num);


            // This converts the int scores into strings 
            // so they are in a data type that can by displayed on
            // the window
            score1.setString(std::to_string(sc1));
            score2.setString(std::to_string(sc2));

            // Displays the scores
            window->draw(score1);
            window->draw(score2);

            
            // Stores the name of the player and their score in player class
            player[0].setScore(std::stoi(score1.getString().toAnsiString()));
            player[0].setName(displayName.getString());

            player[1].setScore(std::stoi(score2.getString().toAnsiString()));
            player[1].setName(displayName2.getString());


        }
        

        
        // Display everything
        window->display();

        // Render the window
        //window.clear(sf::Color::White);  // Clear the window with a white color
        
        
    }
    

    int calculateScore(const std::vector<sf::Text>& gridNumbers) 
    {
        int score = 0;
        int gridCol = 3;  // Number of columns in the grid
        int gridRow = 3;  // Number of rows in the grid

        // Map to store frequencies of numbers per column
        // An array of maps 
        // the key of the map is the number that 
        // appears in the colmn and its pair is the frequency 
        // of that number appearing in a colmn
        // ex) a colmn of 2 2 5
        // the map would look like {2: 2, 5:1}
        std::map<int, int> frequencyCounter[gridCol];

        // Count frequencies per column
        for (int i = 0; i < gridNumbers.size(); i++) 
        {
            if (!gridNumbers[i].getString().isEmpty()) 
            {
                int number = std::stoi(gridNumbers[i].getString().toAnsiString());

                // Calculate the column index
                int colIndex = i % gridCol;

                // Increment the frequency of the number in this column


                // Exlanation: [colIndex] access a specific index in the array of maps
                // so in the first iteration of the for loop 
                // this will access the first map in the array of maps { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
                // then it will set the key of that map to the value of the cell in the grid
                // then it will increment how many times it has seen that value in the map by 1
                // which is indicated by the ++ in frequencyCounter[colIndex][number]++;

                // Ex) If the second column is filled with 3 4 3 
                // this would pick the second map in the array { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
                // then it would make a key {3:2, 4:1} 


                frequencyCounter[colIndex][number] = frequencyCounter[colIndex][number] + 1;
            }
        }

        // Calculate the score based on frequencies        

        // Iterates through the array of maps 
        // then goes through the whole map that its focuses on 
        // first iteration it will go through the first map 
        // { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
        for (int col = 0; col < gridCol; col++) 
        {
            for (const auto& pair : frequencyCounter[col]) 
            {
                int number = pair.first;   // The number in the column
                int frequency = pair.second; // How many times it appears

                if (frequency == 2) 
                {
                    // Double the sum if the number appears twice
                    score += (number * 2 * 2); // (sum) * 2
                } 
                else if (frequency == 3) 
                {

                    // Triple the sum if the number appears three or more times
                    score += (number * 3 * 3); // (sum) * 3
                } 
                else 
                {

                    // Add the number as is if it appears only once
                    score += number;
                }

                
            }
        }

        return score;
    }


   


    
  
};



int main() 
{
    
    sf::RenderWindow window(sf::VideoMode(1200, 800), "KnuckleBone");

    Game game(window);

    game.loadAssets();

    // Seed the random number generator for the dice roll
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    // Main game loop
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                game.close();
            }
            
            game.checkMouse(event);

            game.inputNames(event);
            // Start the animation on space key press
            game.rollDice(event);
        }

        // Update the animation
        game.updateDice();

        game.clear();       
        
        game.updateGame();


    }
    return 0;
}

