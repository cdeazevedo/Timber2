// Timber2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
int main()
{
    // set random seed
    //srand((int)time(0));
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
    Sprite beeSprite{ textureBee };
    beeSprite.setPosition(0, 800);
    bool beeActive = false;
    float beeSpeed{ 0.0f };

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1{ textureCloud };
    Sprite spriteCloud2{ textureCloud };
    Sprite spriteCloud3{ textureCloud };

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        window.clear(); // clear the display

        // make new things to the display 

        Time dt = clock.restart();

        // setup the bee
        if (!beeActive) {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            srand((int)time(0));
            float height = (rand() % 500) + 500;
            beeSprite.setPosition(2000, height);
            beeActive = true;
        }
        else {
            beeSprite.setPosition(
                beeSprite.getPosition().x - beeSpeed * dt.asSeconds(),
                beeSprite.getPosition().y
            );

            if (beeSprite.getPosition().x < -100) { beeActive = false; }
        }

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(beeSprite);

        window.display(); //  draw them to the window
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
