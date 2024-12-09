#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "diceRoll.hpp"  // include animation for dice roll
#include "grid.hpp"      // include grid
#include<string>



int calculateScore(const std::vector<sf::Text>&) ;


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
    grid1Num.resize(9, sf::Text());
    grid2Num.resize(9, sf::Text());

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
                        
                        auto cell1 = grid1.getCellPos(mousePos);
                        if(cell1.first != -1 && cell1.second != -1)
                        {


                            float cellSize = grid1.getCellSize();

                            
                            grid1Num[g1].setPosition(cell1.first + cellSize/2.0f - 18.f, cell1.second + cellSize/2.0f - 35.f);
                            grid1Num[g1].setString(std::to_string(diceNum));
                            grid1Num[g1].setFont(font);
                            grid1Num[g1].setCharacterSize(50);
                            grid1Num[g1].setFillColor(sf::Color::White);

                            if ( g1 < 9)
                            {
                                g1++;
                            }
                            diceNum = 0;
                            firstTurn = !firstTurn;
                        }
                    }
                    else if(!firstTurn)
                    {
                        diceRolls++;
  
                        auto cell2 = grid2.getCellPos(mousePos);
                        if(cell2.first != -1 && cell2.second != -1)
                        {

                            std::cout << diceNum << std:: endl;

                            float cellSize = grid2.getCellSize();

                            grid2Num[g2].setPosition(cell2.first + cellSize/2.0f - 18.f, cell2.second + cellSize/2.0f - 28.f);
                            grid2Num[g2].setString(std::to_string(diceNum));
                            grid2Num[g2].setFont(font);
                            grid2Num[g2].setCharacterSize(50);
                            grid2Num[g2].setFillColor(sf::Color::White);
                            
                            if(g2 < 9)
                            {
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

                    diceRoll.startAnimation(); // Start the animation when Space is pressed
                    diceNum = diceRoll.getRandomFrame();
                    diceRolls--;
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


         if (!nameEntered[i] && i < 2) 
        {
            window->draw(instructionText);
            window->draw(nameText);
        } 

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
            grid1.draw(*window);
            grid2.draw(*window);
            window->draw(button);
            window->draw(roll);
            window->draw(displayName);
            window->draw(displayName2);
            window->draw(score1Display);
            window->draw(score2Display);
            diceRoll.draw(*window);           // Draw the dice animation

            for(int a = 0; a < grid1Num.size(); a++)
            {
                window->draw(grid1Num[a]);
            }
            for (int b = 0; b < grid2Num.size(); b++)
            {
                window->draw(grid2Num[b]);

            }

            int sc1 = calculateScore(grid1Num);
            int sc2 = calculateScore(grid2Num);

            score1.setString(std::to_string(sc1));
            score2.setString(std::to_string(sc2));

            window->draw(score1);
            window->draw(score2);

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
        int gridRow = 3;
        int gridCol = 3;

        // An array of maps 
        // the key of the map is the number that 
        // appears in the colmn and its pair is the frequency 
        // of that number appearing in a colmn
        // ex) a colmn of 2 2 5
        // the map would look like {2: 2, 5:1}
        std::map<int, int> frequencyCounter[gridCol];

        // Loops through the grid and count frequncy of numbers
        // per column

        for (int r = 0; r < gridRow; r++)
        {
            for(int c = 0; c < gridCol; c++)
            {

                int index = r * gridRow + c;

                if (!gridNumbers[index].getString().isEmpty()) 
                {
                    try 
                    {
                        int value = std::stoi(gridNumbers[index].getString().toAnsiString());


                        // [c] access a specific index in the array of maps
                        // so in the first iteration of the nested for loop 
                        // this will access the first map in the array of maps { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
                        // then it will set the key of that map to the value of the cell in the grid
                        // then it will increment the how many times it has seen that value in the map by 1
                        // which is indicated by the ++ in frequencyCounter[c][value]++;

                        // Ex) the second column filled with 3 4 3 
                        // this would pick the second map in the array { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
                        // then it would make a key {3:2, 4:1} and having incremented it twice
                        frequencyCounter[r][value]++;


                    } 
                    catch (const std::exception& e) 
                    {
                        std::cerr << "Error converting text to number: " << e.what() << std::endl;
                    }
                }
            }
        }

        

        // Calucate score based on multiplier 

        for(int col = 0; col < gridCol; col++)
        {



            // Iterates through the array of maps 
            // then goes through the whole map that its focuses on 
            // first iteration it will go through the first map 
            // { 1.{_:_, _:_}, 2.{_:_, _:_}, 3.{_:_, _:_}}
            for(const auto& pair: frequencyCounter[col])
            {
                int number = pair.first;
                int frequency = pair.second;

                if (frequency > 1) // Apply multiplier if the number appears more than once
                {
                    score += number * frequency;
                }

                else
                {
                    score += number; // Add the number directly if it appears only once
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

