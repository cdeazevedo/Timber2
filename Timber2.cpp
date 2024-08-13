// Timber2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>
using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
// WHERE IS PLAYER?
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{
    // set random seed
    srand(static_cast<unsigned>(time(0)));
    int number = (rand() % 100);
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!!", Style::Default);
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    const float TREE_HORIZONTAL_POSITION = 810;
    const float TREE_VERTICAL_POSITION = 0;

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee{ textureBee };
    spriteBee.setPosition(2000, 800);
    bool beeActive = false;
    float beeSpeed{ 0.0f };

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1{ textureCloud };
    Sprite spriteCloud2{ textureCloud };
    Sprite spriteCloud3{ textureCloud };

    spriteCloud1.setPosition(2000, 0);
    spriteCloud2.setPosition(2000, 250);
    spriteCloud3.setPosition(20000, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float CLOUD_SPEED = 100.0f;


    std::vector<Sprite> clouds{ spriteCloud1, spriteCloud2, spriteCloud3 };
    std::vector<bool> cloudsActive{ cloud1Active, cloud2Active, cloud3Active };
  

    Clock clock;

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;

    int score = 0;
    Text messageText;
    Text scoreText;

    Font font;
    if (!font.loadFromFile("C:/Development/Timber2/fonts/KOMIKAP_.ttf")) {
        std::cout << "Font load failed!" << std::endl;
        return 0;
    }
    

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press ENTER to start!");
    scoreText.setString("Score: 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // center the message on the screen
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            paused = false;
            score = 0;
            timeRemaining = 6;
            
        }

        window.clear(); // clear the display

        // make new things to the display 
        if (!paused)
        {

            Time dt = clock.restart();
            
              // IF game isn't paused, reduce size of timeBar by timeBardWidthPer second * dt.asSeconds?
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(
                Vector2f(
                    timeBarWidthPerSecond * timeRemaining, timeBarHeight)
            );
        
            if (timeRemaining <= 0.0f) {
                paused = true;

                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(
                    textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f
                );

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // setup the bee
            if (!beeActive) {

                beeSpeed = static_cast<float>((rand() % 200) + 200);

                float height = static_cast<float>((rand() % 500) + 500);
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - beeSpeed * dt.asSeconds(),
                    spriteBee.getPosition().y
                );

                if (spriteBee.getPosition().x < -100) { beeActive = false; }
            }
            // setup the clouds in an array if you can
            for (size_t i = 0; i < clouds.size(); i++)
            {
                if (!cloudsActive[i]) {



                    float cloudHeight = static_cast<float>(rand() % 301);
                    float cloudStart = static_cast<float>((rand() % 2000) + 2000);
                    clouds[i].setPosition(cloudStart, cloudHeight);
                    clouds[i].setScale(0.5f + (cloudHeight / 300.0f), 0.5f + (cloudHeight / 300.0f)); // Scaling based on speed
                    cloudsActive[i] = true;

                }
                else {
                    clouds[i].setPosition(
                        clouds[i].getPosition().x - CLOUD_SPEED * dt.asSeconds(),
                        clouds[i].getPosition().y
                    );
                }

                if (clouds[i].getPosition().x < -500) { cloudsActive[i] = false; }

                std::stringstream ss;
                ss << "Score: " << score;
                scoreText.setString(ss.str());

                // update the branch sprites
                for (int i = 0; i < NUM_BRANCHES; i++)
                {
                    //
                }
            }
        }

        window.draw(spriteBackground);
        for (const auto& cloud : clouds) {
            window.draw(cloud);
        }
        window.draw(spriteTree);
        window.draw(spriteBee);
       
        window.draw(scoreText);
        if(paused) { window.draw(messageText); }
        if (!paused) 
        {
            window.draw(timeBar); 
        }
       

        window.display(); //  draw them to the window
    }
    std::cout << "Hello World!\n";
}
