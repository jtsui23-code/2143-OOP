#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 4: Animations");

    // Load textures for animation frames
    std:: string frameNum[2] = {"00", "0"};
    int g = 0;
    std::vector<sf::Texture> textures;
    for (int i = 1; i <= 24; ++i) { // Assume dice frames are named frame1.png to frame6.png
        sf::Texture texture;
        if (i > 9)
        {
            g = 1;
        }
        if (!texture.loadFromFile("media/animations/dice_roll/frame_" + frameNum[g] +  std::to_string(i) + ".png")) {
            std::cerr << "Error loading frame_" << frameNum[g] << i << ".png" << std::endl;
            return -1;
        }
        textures.push_back(texture);
    }

    // Create a sprite to display the current frame
    sf::Sprite sprite;
    sprite.setTexture(textures[0]); // Start with the first frame
    sprite.setPosition(300.f, 200.f);

    // Timing variables
    sf::Clock clock;
    const sf::Time frameDuration = sf::milliseconds(12); // 200ms per frame
    size_t currentFrame = 0;
    bool fullAnimation = false;
    bool pressed = false;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {

                    pressed = true;
                    fullAnimation = false;
                    currentFrame = 0;
                }
            }
        }
        if (!fullAnimation && pressed)
        {
// Update animation frame
            if (clock.getElapsedTime() >= frameDuration) 
            {
                clock.restart(); // Reset the clock

                // Advance to the next frame
                currentFrame++;

                    if (currentFrame == 24) 
                    { // Stop after 24 frames
                        fullAnimation = true;
                        currentFrame = 0;
                        sprite.setTexture(textures[currentFrame]);
                        pressed = false;
                    } 
                    else 
                    {
                    sprite.setTexture(textures[currentFrame]);
                    }
            }
        }
        

        // Render
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}