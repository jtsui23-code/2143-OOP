#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>  // For std::rand and std::srand
#include <ctime>    // For seeding random number generator

class DiceRollAnimation {
private:
    std::vector<sf::Texture> textures; // Stores textures for animation frames
    sf::Sprite sprite;                 // Sprite to display the current frame
    sf::Clock clock;                   // Timer for frame updates
    sf::Time frameDuration;            // Duration of each frame
    size_t currentFrame;               // Index of the current frame
    bool isAnimating;                  // Is the animation playing?
    std::string framePrefix;           // Prefix for frame files
    std::string folderPath;            // Path to the folder containing frames
    size_t randomFrame;                // Random dice side (1-6)
    sf:: Texture ranText;


public:
    // Constructor
    DiceRollAnimation(const std::string& folderPath, const std::string& framePrefix, sf::Time frameDuration = sf::milliseconds(1))
        : folderPath(folderPath), framePrefix(framePrefix), frameDuration(frameDuration), currentFrame(0), isAnimating(false), randomFrame(0) {}

    // Load frames into textures
    bool loadFrames(int start, int end) {
        std::string frameNum[2] = {"00", "0"};
        int g = 0;

        for (int i = start; i <= end; ++i) {
            sf::Texture texture;
            if (i > 9) g = 1;
            std::string fileName = folderPath + framePrefix + frameNum[g] + std::to_string(i) + ".png";

            if (!texture.loadFromFile(fileName)) {
                std::cerr << "Error loading " << fileName << std::endl;
                return false;
            }
            textures.push_back(texture);
        }
        sprite.setTexture(textures[0]); // Start with the first frame
        return true;
    }

    // Start the animation
    void startAnimation() {
        if (!textures.empty()) {
            isAnimating = true;
            currentFrame = 0;
            clock.restart();
            randomFrame = std::rand() % 6 + 1; // Generate a random frame (1-6)
        }
    }

    // Update the animation state
    void update() {
        if (isAnimating && clock.getElapsedTime() >= frameDuration) {
            clock.restart();
            ++currentFrame;

            if (currentFrame >= textures.size()) {
                isAnimating = false; // Stop the animation after the last frame

                ranText.loadFromFile("media/images/" + std:: to_string(randomFrame) + ".png");

                sprite.setTexture(ranText); // Set to the random dice frame
            } else {
                sprite.setTexture(textures[currentFrame]);
            }
        }
    }

    // Set sprite position
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // Draw the sprite
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// // Main function to demonstrate usage
// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Roll Animation");

//     // Seed the random number generator
//     std::srand(static_cast<unsigned>(std::time(nullptr)));

//     // Create a DiceRollAnimation instance
//     DiceRollAnimation diceRoll("media/animations/dice_roll/", "frame_", sf::milliseconds(12));
//     if (!diceRoll.loadFrames(1, 24)) {
//         return -1; // Exit if frame loading fails
//     }
//     diceRoll.setPosition(300.f, 200.f);

//     // Main game loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
//                 diceRoll.startAnimation(); // Start animation on Space key press
//             }
//         }

//         // Update animation
//         diceRoll.update();

//         // Render
//         window.clear(sf::Color::White);
//         diceRoll.draw(window);
//         window.display();
//     }

//     return 0;
// }
