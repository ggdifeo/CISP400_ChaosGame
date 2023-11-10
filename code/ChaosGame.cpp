// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // loads font into program
    Font font;
    if (!font.loadFromFile("font.ttf")) 
    {
        // Displays message to user if font doesn't load
        cout << "Error loading font!" << endl;
        // returns error and exits program
        return -1;
    }

    Text text;

    text.setFont(font);
    text.setCharacterSize(60); //sets text size
    text.setFillColor(Color::White); // sets text color
    text.setPosition(10, 10); //positions text

    Text titleText;
    
    titleText.setFont(font);
    titleText.setCharacterSize(150);
    titleText.setFillColor(Color(210, 43, 41));
    titleText.setOutlineColor(Color::White);
    titleText.setOutlineThickness(2);
    float windowWidth = static_cast<float>(vm.width); //defines a float windowWidth that determines the size of the window / game screen. the static_case<float> converts vm.width to integer for better precision in centering the text
    const FloatRect titleTextBounds = titleText.getLocalBounds(); //Gets dimensions of the screen
    float titleTextWidth = titleTextBounds.width; //New float to specify we just want to know the width 
    float titleTextXPos = (windowWidth - titleTextWidth) / 2.0f; //centers the x axis by finding the half/middle point
    titleText.setPosition(titleTextXPos, 140); //sets new position but keeps y axis fixed pos
    
    titleText.setString("CHAOS GAME"); //adds title screen 

    Text shadowText;

    shadowText.setFont(font);
    shadowText.setCharacterSize(150);
    shadowText.setFillColor(Color(112, 43, 34));
    const FloatRect shadowTextBounds = shadowText.getLocalBounds(); //Gets dimensions of the screen
    float shadowTextWidth = shadowTextBounds.width; //New float to specify we just want to know the width 
    float shadowTextXPos = (windowWidth - shadowTextWidth) / 2.0f; //centers the x axis by finding the half/middle point
    shadowText.setPosition(shadowTextXPos, 160); //sets new position but keeps y axis fixed pos
    shadowText.setString("CHAOS GAME"); 

    Text startText;

    startText.setFont(font);
    startText.setCharacterSize(50);
    startText.setFillColor(Color::White);
    const FloatRect startTextBounds = startText.getLocalBounds(); //Gets dimensions of the screen
    float startTextWidth = startTextBounds.width; //New float to specify we just want to know the width 
    float startTextXPos = (windowWidth - startTextWidth) / 2.0f; //centers the x axis by finding the half/middle point
    startText.setPosition(startTextXPos, 450); //sets new position but keeps y axis fixed pos
    startText.setString("PRESS ANY KEY TO PLAY!");

    bool titleScreen = true; //Establishes title screen seperate from game (true = shows title screen)

    int step = 1; //Set the step variable to 1

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }

            if (event.type == Event::KeyPressed && titleScreen) 
            {
                titleScreen = false;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    //right now user has to click 3 times for blue dots, and then another time to initiate the matrix
                    else if(points.size() == 0 && step == 1 && vertices.size() >= 3)
                    {
                        ///fourth click
                        ///push back to points vector
                        step = 2;

                        
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        if (titleScreen)
        {
            window.draw(shadowText);
            window.draw(titleText);
            window.draw(startText);
        }
        else if (step == 1)
        {
            text.setString("STEP 1: CLICK TO ADD 3 STARTING POINTS ON SCREEN, \n THEN CLICK AGAIN TO CREATE IMAGE."); 
            window.draw(text);
        }

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        window.display();
    }
}