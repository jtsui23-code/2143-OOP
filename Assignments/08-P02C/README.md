## 08-P02C - Knucklebone With Ncurses
### Jack Tsui
### Description:
I have implemented a popup window that prompts for the names of both the first and second players. However, I have a segmentation fault error when I enter the second player's name in the input window. 

### Files:
|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | [game.cpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/game.cpp)        | This runs the program for the knucklebone game.      |
|   2   | [main.exe](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/main)          | This is the compiled game.                       |
|   3  | [button_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/button_class.h)          | This is the implementation file for button.                       |
|   4   | [color_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/color_class.hpp)          | This is the implementation for colors.                       |
|   5   | [dice_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/dice_class.hpp)          | This is the implementation for the dice.                       |
|   6  | [grid_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/grid_class.hpp)          | This is the implementation for the grid.                       |
|   7   | [input_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/input_class.hpp)          | This is the implementation for input.                       |
|   8   | [logger_class.hpp](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/logger_class.hpp)          | This is the implementation for the logger.                       |
|   9   | [log.txt](https://github.com/jtsui23-code/2143-OOP/blob/main/Assignments/08-P02C/log.txt)          | This is the log text file.                       |




### Instructions:

- Compile the program
- Run the program using the terminal

### Example:
  - g++ -std=c++11 -o [write the name of exe you want] game.cpp -lncurses
  - ./[name of exe] 
