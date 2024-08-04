// Timber2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!!", Style::Default);
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        window.clear(); // clear the display

        // make new things to the display 
        //  Create a texture to hold a graphic on the GPU Texture textureBackground;
        // Load a graphic into the texture textureBackground.loadFromFile("graphics/background.png");
        // Create a sprite Sprite spriteBackground;
        // Attach the texture to the sprite spriteBackground.setTexture(textureBackground);
        // Set the spriteBackground to cover the screen spriteBackground.setPosition(0,0);
        window.draw(spriteBackground);
        
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
