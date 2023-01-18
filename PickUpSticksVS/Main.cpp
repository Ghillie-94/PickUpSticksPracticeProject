#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

int main()
{
    // --------------------------------------------------
     // Setup
     // --------------------------------------------------
#pragma region Setup

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Player_Stand.png");
    sf::Texture grassTexture;
    grassTexture.loadFromFile("Assets/Grass.png");
    sf::Texture stickTexture;
    stickTexture.loadFromFile("Assets/Stick.png");

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);
    sf::Sprite stickSprite;
    stickSprite.setTexture(stickTexture);

    std::vector<sf::Sprite> grassSprites;
    std::vector<sf::Sprite> stickSprites;
    int numGrassSpritesToAdd = 5;

    //sprite origin point setup
    grassSprite.setOrigin(grassTexture.getSize().x / 2, grassTexture.getSize().y / 2);
    stickSprite.setOrigin(stickTexture.getSize().x / 2, stickTexture.getSize().y / 2);

    for (int i = 0; i < numGrassSpritesToAdd; ++i)
    {
        
        int colourTint = 100 + rand() % 155;
        float grassScaler = 1 + rand() % 2;
        grassSprite.setScale(grassScaler, grassScaler);
        grassSprite.setPosition(sf::Vector2f(grassScaler * grassTexture.getSize().x/2 + rand() % (int)(window.getSize().x - grassScaler * grassTexture.getSize().x), grassScaler * grassTexture.getSize().y/2 + rand() % (int)(window.getSize().y - grassScaler * grassTexture.getSize().y)));
        grassSprite.setColor(sf::Color(colourTint, colourTint, colourTint));
        grassSprites.push_back(grassSprite);
    }
    float stickRotation = rand() % 359;
    stickSprite.setPosition(sf::Vector2f(stickTexture.getSize().x/2 + rand() % (window.getSize().x - stickTexture.getSize().x), stickTexture.getSize().y/2 + rand() % (window.getSize().y - stickTexture.getSize().y)));
    stickSprite.setRotation(stickRotation);
    stickSprites.push_back(stickSprite);
    

    // Position setup
    playerSprite.setPosition(sf::Vector2f(0.0f + playerTexture.getSize().x / 2, 100.0f));

    // colour setup
    //playerSprite.setColor(sf::Color(250,250,250));

    //Rotation Example
    //playerSprite.setRotation(270);

    //Scale Example
    //playerSprite.setScale(3.0f, 3.0f);

    //origin Example
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);

    //load fonts
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");

    //create text objects
    //game title
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");
    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setFillColor(sf::Color(227, 121, 59));
    gameTitle.setOutlineThickness(2);
    gameTitle.setOutlineColor(sf::Color::Black);
    gameTitle.setStyle(sf::Text::Bold);
    gameTitle.setPosition(window.getSize().x / 2.0f - textWidth/2.0f, 10.0f);
    
    

    //Score label
    sf::Text scoreLabel;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString("Score: ");
    scoreLabel.setPosition(0.0f, 0.0f);

    //Audio setup
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();


#pragma endregion

    while (window.isOpen())
    {

        // --------------------------------------------------
        // Event Polling
        // --------------------------------------------------
#pragma region Event Polling

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

#pragma endregion


        // --------------------------------------------------
        // Drawing
        // --------------------------------------------------
#pragma region Drawing

        window.clear(sf::Color(61, 204, 90));

        // Draw all the things
        for (int i = 0; i < grassSprites.size(); ++i)
            window.draw(grassSprites[i]);
        for (int i = 0; i < stickSprites.size(); ++i)
            window.draw(stickSprites[i]);
        window.draw(playerSprite);

        window.draw(gameTitle);

        window.draw(scoreLabel);

        window.display();

#pragma endregion

    }

    return 0;
}