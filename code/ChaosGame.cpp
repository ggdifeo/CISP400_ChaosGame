// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
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
    vector<CircleShape> stars;

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
    titleText.setCharacterSize(250);
    titleText.setFillColor(Color(210, 43, 41));
    titleText.setOutlineColor(Color::White);
    titleText.setOutlineThickness(2);
    titleText.setPosition(150, 140);
    titleText.setString("CHAOS GAME"); //adds title screen 

    Text shadowText;

    shadowText.setFont(font);
    shadowText.setCharacterSize(250);
    shadowText.setFillColor(Color(112, 43, 34));
    shadowText.setPosition(150, 160);
    shadowText.setString("CHAOS GAME"); 

    Text startText;

    startText.setFont(font);
    startText.setCharacterSize(60);
    startText.setFillColor(Color::White); 
    startText.setPosition(500, 500);
    startText.setString("     PRESS ANY KEY TO PLAY!\n\nCREATED BY KARISSA & GABE");

    bool titleScreen = true; //Establishes title screen seperate from game (true = shows title screen)

    int step = 1; //Set the step variable to 1

    Clock rainbowTimer; //clock class with rainbowTimer object, counts at start of program
    float rainbowDuration = 8.0f; //duration BEFORE animation starts

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
            //Exits title screen ONLY if user presses a key
            if (event.type == Event::KeyPressed && titleScreen) 
            {
                titleScreen = false;
            }

            if (!titleScreen && event.type == sf::Event::MouseButtonPressed) //updated line so user cannot click on title screen, must press a key first
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
        // plays rainbow title text animation at title screen
        if (titleScreen && rainbowTimer.getElapsedTime().asSeconds() > rainbowDuration)
        {
            rainbowTimer.restart();
            rainbowDuration = 0.8f;

            // Changes title text to a rainbow effect, switching colors every 0.8 secs
            titleText.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
            shadowText.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));

            //Changes stars in title screen to rainbow effect
            for (int i = 0; i < stars.size(); i++)
            {
                stars[i].setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
            }
        }
        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        if (titleScreen)
        {
            //Customize stars here
            CircleShape star;
            star.setRadius(2);
            star.setPosition(rand() % 1920, rand() % 1080);
            star.setFillColor(Color::White);
            stars.push_back(star);

            //draws out the stars on title screen
            for (int i = 0; i < stars.size(); i++)
            {
                window.draw(stars[i]);
            }

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