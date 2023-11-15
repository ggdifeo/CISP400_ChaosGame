// Gabriel DiFeo && Karissa Merrill 

// Headers 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random> // need for uniform

//Namespace Declarations
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	// Create and open a window for the game
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices; //stores the points that make the corners of the shape (blue dots)
    vector<Vector2f> points; // stores the points that start populating during the game itself 
    vector<CircleShape> stars; // stars on the title screen
 
    vector<Color> colors = {
    Color::Magenta,
    Color::Yellow,
    Color::Cyan,
};
    size_t colorIndex = 0; // index to keep track of the current colour from colors Vector (above)

    default_random_engine generator; // Random number generator // website: https://www.sfml-dev.org/tutorials/1.6/system-random.php
    uniform_int_distribution<int> uniform_dist(0, 5); // during the fractal itself this is helping with the algorithm of the points being selected


    // Font for Chaos Game
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
    text.setCharacterSize(60); //Sets text size
    text.setFillColor(Color::White); //Sets text color
    text.setPosition(10, 10); //Positions text

    Text titleText;
    
    titleText.setFont(font);
    titleText.setCharacterSize(250);
    titleText.setFillColor(Color(210, 43, 41));
    titleText.setOutlineColor(Color::White);
    titleText.setOutlineThickness(2);
    titleText.setPosition(150, 140);
    titleText.setString("CHAOS GAME"); //Adds title screen 

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
		
	// One Event valid at a time
	// Poll event is also the wait event
	// KeyPressed event is when key is pressed and then released (SFML)
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
			
            //Exits title screen ONLY if user presses a key (NO CLICKY)
            if (event.type == Event::KeyPressed && titleScreen) 
            {
                titleScreen = false;
            }

            if (!titleScreen && event.type == sf::Event::MouseButtonPressed) // User cannot click here -> Additionally, checks if no-title screen
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    

                    if(vertices.size() < 6) // We're mouse clicking the verticies // adds new one when the end user clicks 
                    {
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    //right now user has to click 6 times for blue dots, and then another time to initiate the matrix and changes us to step 2;
                    else if(points.size() == 0) 
                    {
                        step = 2;
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));  
                    }
                }
            }
        }
		
	// If you press escape it exits the game / HOWEVER UBUNTU full screen caused this to fail on me!
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


	// Just making sure we have AT LEAST 1 point in the "points" vector
        if(points.size() > 0) 
        {
	    // Generating 50 new points 
            for (int i = 0; i < 50; i++) 
            {
                int randomSelection = uniform_dist(generator); // Picks one of the vertices  (0 - 5)
                Vector2f pick_random_vertex = vertices[randomSelection]; // Selects a random vertices from randomSelection in the vector for the calculations below 
                Vector2f last_point = points.back(); // Gets the last element of a vector

                Vector2f direction = pick_random_vertex - last_point; // Literally pointing from the starting point to the end point for the next point 

                Vector2f new_point = last_point + (2.0f / 3.0f) * direction; //Calculates a 2/3 of the way point (not exactly mid-way, but it works)

                points.push_back(new_point); // Adds the point to the points vector
            }
        }

        // Plays rainbow title text animation at title screen (TITLE SCREEN)
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
            text.setString("CLICK TO ADD 6 STARTING POINTS ON SCREEN, \n THEN CLICK AGAIN TO CREATE IMAGE."); 
            window.draw(text);
        }
        else
        {
            text.setString("ENJOY THE FRACTAL PATTERN!\nPRESS 'ESC' TO EXIT WHEN DONE"); 
            window.draw(text);

	    // Using size_t because well it can be the size of anything really and we don't need any more errors
            for (size_t i = 0; i < points.size(); ++i) {
            CircleShape point(2);
            point.setPosition(points[i]);

            Color color = colors[colorIndex];

            point.setFillColor(color);
            window.draw(point);

            colorIndex = (colorIndex + 1) % colors.size();
        }
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