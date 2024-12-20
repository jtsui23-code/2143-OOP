
#include <locale.h>
#include <ncurses.h>
#include <cstring>
#include "button_class.hpp"
#include "color_class.hpp"
#include "dice_class.hpp"
#include "grid_class.hpp"
#include "input_class.hpp"
#include "logger_class.hpp"
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Player {
    string name;
    int score;

   public:
    Player(string n) : name(n), score(0) {}
    void addScore(int s) { score += s; }
    int getScore() { return score; }
    string getName() { return name; }
};

class Game {

};

int main() {
    srand(time(0));
    setlocale(LC_ALL, "");  // Enable Unicode support
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor
    clear();
    refresh();

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();

    colorful();

    Logger::setFilePath("log.txt");

    int rows, cols, size;
    int ch;
    int name1,name2;

    getmaxyx(stdscr, rows, cols);

    string text = "ROLL";

    size = strlen(text.c_str()) + 2;

    Logger::log("vals", vector<int>({size, 3, (rows / 2), ((cols - size) / 2)}));

    // Button button(text, 2, 1, Frame({size, 3, (rows / 2), ((cols - size) / 2)}));
    Button button(text, 5, 32, Frame({3, size, 10, 15}));
    button.draw_button();

    Grid grid(1, 10);
    grid.refreshGrid();

    DiceViz dice(3, 30);

    dice.setBorderColor(11);
    dice.setDotColor(5);
    
    WINDOW *nameWin = newwin(5, cols - 4, rows / 4, 2);  // 5 rows, full width of the terminal minus margins
    box(nameWin, 0, 0);  // Draw border for the window
    wrefresh(nameWin);
    
    mvwprintw(nameWin, 1, (cols - 18) / 2, "Enter Player1's name:");  // Prompt text centered
    wrefresh(nameWin);

    //This prompts the user to input their name
    Input input("Enter your name: ", 3,30, rows - 2, (cols + 30)/2);
    string playerName[2];

    input.printBorder();
    input.printInput(rows - 2, (cols + 30)/2 + 15);
    bool playerNamed[] = {false, false};
    

    int posX = (cols -30)/2 + 26;
    int posY = 1;
    int i = 0;

    while (true) {
        ch = getch();

        if (!playerNamed[i])
        {
        playerName[i] = input.getInput();

        if (ch == '\n' || ch == KEY_ENTER)
        {
            Logger::log("Player's name is: ", playerName[i]);
            mvwprintw(nameWin,rows/2, (cols - playerName[i].length())/2, "Player1: %s", playerName[i].c_str());
            wrefresh(nameWin);
            if(!playerNamed[1])
            {
            delwin(nameWin);
            nameWin = nullptr; 
            refresh();
            playerNamed[i] = true;


            nameWin = newwin(5, cols - 4, rows / 4, 2);
            box(nameWin, 0, 0);
            mvwprintw(nameWin, 1, (cols - 18) / 2, "Enter Player2's name:");
            wrefresh(nameWin);
        
            // Reset input variables if needed
            i++;
            posX = (cols - 30) / 2 + 26;

                
            }
            else if (i == 1)
            {
            delwin(nameWin);
            nameWin = nullptr; 
            refresh();

            }
            
        }

        else if (ch == 127 || ch == KEY_BACKSPACE || ch == 8)
        {
            if(!playerName[i].empty())
            {
                playerName[i].pop_back();
                posX--;
                
            }

                mvwaddch(nameWin, posY, posX, ' ');
                mvwprintw(nameWin, posY, (cols - playerName[i].length())/ 2, "%s", playerName[i].c_str());
                if (!playerNamed[1])
                {
                wrefresh(nameWin);
                posX--;

                }
                
        }

        else if (ch >= 32 && ch <= 126)
        {
            playerName[i] += static_cast<char>(ch);
            posX++;
        }
            mvwprintw(nameWin, posY, posX, "%s", playerName[i].c_str());
            wrefresh(nameWin);
        }
        
        if (ch == 'q' || ch == 'Q') 
        {
            break;
        } 
        
        else if (ch == KEY_MOUSE) 
        {
            MEVENT event;
            Logger::log("Mouse pressed", "true");
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    Logger::log("clicked", vector<int>({event.y, event.x}));
                    if (button.clicked(event.y, event.x)) 
                    {
                        button.draw_button();
                        Logger::log("drawing button", "true");
                        dice.animate_dice(30);
                        dice.draw_dice(dice.getLastDiceValue());
                        button.toggle();
                    }

                    if (grid.clicked(event.y, event.x - 1)) 
                    {
                        Logger::log("clicked grid", "true");
                        dice.clear();
                        grid.addValue(event.y, event.x - 1, dice.getLastDiceValue());  // Mark click location
                        grid.refreshGrid();
                    }
                }
            }
        }
        Logger::log("Key pressed", to_string(ch));
        button.draw_button();
        refresh();
    }

    // while (true) {
    //     // mvprintw(rows / 2, (cols / 2) - strlen(text.c_str()), text.c_str());
    //     ch = getch();

    //     if (ch == 'q' || ch == 'Q') {
    //         break;
    //     } else if (ch == KEY_MOUSE) {
    //         MEVENT event;
    //         Logger::log("Mouse pressed", "true");
    //         if (getmouse(&event) == OK) {
    //             if (event.bstate & BUTTON1_CLICKED) {
    //                 Logger::log("clicked", vector<int>({event.y, event.x}));
    //                 if (button.clicked(event.y, event.x)) {
    //                     button.draw_button();
    //                     Logger::log("drawing button", "true");
    //                     dice.animate_dice(30);
    //                     // dice.refresh();
    //                 }
    //                 if (grid.clicked(event.y, event.x - 1)) {
    //                     Logger::log("clicked grid", "true");
    //                     grid.addValue(event.y, event.x, rand() % 6 + 1);  // Mark click location
    //                 }
    //             }
    //         }
    //     }
    //     Logger::log("Key pressed", to_string(ch));
    //     button.draw_button();
    //     refresh();
    // }
    clear();
    endwin();
    return 0;
}