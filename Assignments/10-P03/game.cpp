

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

    // Array size 2 of Player objects
    // They represent the player1 and player2
    Player player[2];

    // This is the dimension of the 
    // window screen.
    int height;
    int width;
    

    // This creates two Grid objects
    // that are displayed on the screen
    // and that perform the gridNum logic
    Grid grid1;
    Grid grid2;

    // Variable for storing fonts used in the game
    sf::Font font;
    sf::Font titleFont;

    // This is a pointer to a sfml window
    sf::RenderWindow* window;

    // This texture is what gives the roll button its
    // red gradient 
    sf::Texture buttonTexture;

    // This stores the lamb image
    // to be the turn indicator
    sf:: Texture turnSkin;

    // This is the turn indicator
    // object itself that gets the lamb image
    // texture
    sf:: RectangleShape turnIndicator;   

    // This is the rectangle object that 
    // is the roll button 
    sf::RectangleShape button;

    // These are vectors that store all of the 
    // numbers on each respective grid
    std:: vector< sf::Text> grid1Num;
    std:: vector< sf::Text> grid2Num;

    // This is text that overlays the 
    // roll button to 
    // prompt the user to 
    // press space to roll the dice
    sf::Text roll;

    // This text prompts the user to input their name on
    // the title screen.
    sf::Text instructionText;

    // This text stores the text that is being 
    // typed dynamically
    sf::Text nameText;

    // This is text for displaying each player's name 
    // on their respective grid
    sf::Text displayName;
    sf::Text displayName2;


    
    // This stores the player names 
    std::string userInput[2];

    // This checks if each player has entered their names
    bool nameEntered[2] = {false, false};
    
    // Index for player names that are inputed 
    // Will increment when Player1 has their name inputed and 
    // INcrement again when player2 has their name inputed to 
    // Transition to game screen.
    int i;

    
    // This is text for display this "Score: " 
    // on the screen to indicate a scorer on 
    // each grid
    sf:: Text score1Display;
    sf:: Text score2Display;   

    // While this is the acutal number that is displayed 
    // after "Score:"
    sf:: Text score1;
    sf:: Text score2;

    // Create a DiceRollAnimation instance
    DiceRollAnimation diceRoll;  

    int diceNum;
    bool firstTurn;
    int diceRolls;

    // Text used to display text of the 
    // winner of the game.
    sf:: Text declareWinner;
    
    // Text used to display the game name
    // on the title screen.
    sf:: Text titleName;

    // label above the turn indicator
    // to explain what the turn indicator image
    // means
    sf:: Text turnText;



    public:

    Game(sf::RenderWindow &w) : grid1(3, 3, 125.f, 120.f, 80.f), grid2(3, 3, 125.f, 800.f - 25.f, 80.f), window(&w),
    turnIndicator(sf:: Vector2f(150.f, 200.f)), button(sf:: Vector2f(200.f, 100.f)), roll("Space", font, 50)
    ,instructionText("Enter your Players' name:", font, 24), nameText("", font, 24), displayName("", font, 45)
    , displayName2("", font, 45), score1("Score: ", font, 45), score2("Score: ", font, 45), score1Display("Score: ", font, 45)
    ,score2Display("Score: ", font, 45), diceRoll("media/animations/dice_roll/", "frame_", sf::milliseconds(50))
    , declareWinner("", font, 60), titleName("Knucklebone", titleFont, 150), turnText("Turn", font, 45)

    {
    height = 1200;
    width = 800;

    loadAssets();

    // Set sthe position and color of the game tile
    titleName.setPosition(sf::Vector2f(200.f, 10.f));
    titleName.setFillColor(sf::Color::White);

    // Set sthe position and color of the turn indicator label
    turnText.setPosition(sf::Vector2f(590.f, 350.f));
    turnText.setFillColor(sf::Color::White);

    // Set sthe position and texture of the turn indicator 
    turnIndicator.setPosition(sf::Vector2f(550.f, 450.f));
    turnIndicator.setTexture(&turnSkin);

    // Set sthe position and texture of the roll button 
    button.setPosition(535.f,630.f);
    button.setTexture(&buttonTexture);

    //Fills in 9 indexs with empty text 
    grid1Num.resize(9, sf::Text("0", font, 45));
    grid2Num.resize(9, sf::Text("0", font, 45));

    // Set sthe position and texture of the roll button text
    roll.setPosition(565.f, 640.f);
    roll.setFillColor(sf::Color::White);

    // Prompts for player name input
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    // Set sthe position and color of the typed text in the 
    // player input screen 
    nameText.setPosition(350, 200);
    nameText.setFillColor(sf::Color::Green);


    // Set sthe position and color of the  player names 
    // that will be displayed above their respective 
    // grid during the game
    displayName.setPosition(300, 25);
    displayName.setFillColor(sf::Color::Yellow);

    displayName2.setPosition(950, 25);
    displayName2.setFillColor(sf::Color::Yellow);


    // Setting up the win declaration text.
    declareWinner.setPosition(380.f,630.f);
    declareWinner.setFillColor(sf::Color::White);

    // Sets up the position and color of the score that 
    // will be displayed under each grid. 
    // the score is displaying each player's total score
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


    // Sets names of players to nothing and
    // their checker to false to indicate
    // no names have been entered
    userInput[0] = {""};
    userInput[1] = {""};
    nameEntered[0] = {false};
    nameEntered[1] = {false};

    // Index for which player has entered their name
    // 0 representing player1
    // 1 repsenting player2
    i = 0;
   
    // Set the dice number to 0 so
    // player cannot one use 
    // previous dice roll on their own grid
    // and forcing player to have to roll once to 
    // start the game
     diceNum = 0;

     // checker for if its player1's turn
     firstTurn = true;

     // count for how many dice rolls are left per
     // player so player cannot do infinite dice rolls
     diceRolls = 1;


    }

    void loadAssets()
    {

        
        
        if (!titleFont.loadFromFile("media/extra/titleFont.ttf")) 
        {
        std::cerr << "Error: Could not load texture 'titleFont.ttf'\n";

        }

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
        

        // Checks for mouse input
        if(event.type == sf:: Event:: MouseButtonPressed && event.mouseButton.button == sf:: Mouse::Left)
            {

                // Stores the mouse posiiton of the mouse click
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                // This ensures that the player
                // has rolled a new dice because once a player has rolled
                // and placed the number down diceNum becomes 0 
                // making it to where a player cannot use their opponets last 
                // dice roll on their own grid
                if(diceNum > 0)
                {
                    // This checks if it is the first player's turn
                    if(firstTurn)
                    {
                        
                        // Places the dice number the player roll onto an cell
                        // if it is emepty 
                        if(grid1.putNumOnClickedCell(mousePos, diceNum))
                        {
                            
                            //This gives the player a dice roll allow them to roll
                            // otherwise the roll animation/function would not run
                            // this is in place to prevent rerolling dices
                            diceRolls++;

                            // This onlys players to place numbers on cells while
                            // no grid are fully filled
                            if ( grid1.countFillGrid() < 9  && grid2.countFillGrid() < 9)
                            {
                                // This logic check if the lastly dice number placement 
                                // can destroy the opponents column
                                int lastClickedCellIndexP1 = grid1.getLastClickedCellIndex();
                                grid2.checkCanDestroyColumn(lastClickedCellIndexP1, diceNum);

                                // Have to check if cells in column can be shifted down or there will
                                // be floating cells after a destroyed column
                                grid2.shiftCellsDown();
                            }
                            grid1Num = grid1.getGridNum();
                            diceNum = 0;
                            firstTurn = !firstTurn;
                        }
                        
                    }

                    //This runs whenever its the second player's turn
                    else if(!firstTurn)
                    {
  
                        // Places the dice number the player roll onto an cell
                        // if it is emepty 
                        if(grid2.putNumOnClickedCell(mousePos, diceNum))
                        {

                            //This gives the player a dice roll allow them to roll
                            // otherwise the roll animation/function would not run
                            // this is in place to prevent rerolling dices
                            diceRolls++;

                            // This onlys players to place numbers on cells while
                            // no grid are fully filled
                            if(grid2.countFillGrid() < 9 && grid1.countFillGrid() < 9)
                            {
                                // This logic check if the lastly dice number placement 
                                // can destroy the opponents column
                                int lastClickedCellIndexP2 = grid2.getLastClickedCellIndex();
                                grid1.checkCanDestroyColumn(lastClickedCellIndexP2, diceNum);

                                // Have to check if cells in column can be shifted down or there will
                                // be floating cells after a destroyed column
                                grid1.shiftCellsDown();

                            }

                            grid2Num = grid2.getGridNum();
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
                    if(grid2.countFillGrid() < 9 && grid1.countFillGrid() < 9)
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

        // This will make the game remain on the title screen or
        //  until both player has entered their 
        // names
         if (!nameEntered[i] && i < 2) 
        {
            window->draw(titleName);
            window->draw(instructionText);
            window->draw(nameText);
        } 
        
        // This is the game screen
        // that appears after both players have entered their names 
        // 
        else
        {
            // If none of the grids are filled, 
            // Continue the game loop
            if(grid2.countFillGrid() < 9 && grid1.countFillGrid() < 9)
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

                // Displays the turn indicator label
                window->draw(turnText);

                // Displays the turn indicator 
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

                // Displays both players' score on the bottom of their grid
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

            // If one of the grids are filled, 
            // Show who the winner is of the game and stop
            // the game loop
            if(grid2.countFillGrid() >= 9 || grid1.countFillGrid() >= 9)
            {
                // Makes a copy of the vector of Text 
                // Containing all of the numbers on a single grid
                grid1Num = grid1.getGridNum();
                grid2Num = grid2.getGridNum();

                // Displays the grid and the numbers in each of the 
                // grid cells
                grid1.draw(*window);
                grid2.draw(*window);

                //Displays both players' names
                window->draw(displayName);
                window->draw(displayName2);

                // Displays both players' score on the bottom of their grid
                window->draw(score1Display);
                window->draw(score2Display);


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

                // Checks which player has the higher score and 
                // declares them the winner through the text display.
                if(player[0].getScore() > player[1].getScore())
                {
                    declareWinner.setString(player[0].getName() + " has won the game.");
                }

                else if(player[0].getScore() < player[1].getScore())
                {
                    declareWinner.setString(player[1].getName() + " has won the game.");
                }

                window->draw(declareWinner);

            }
            

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

