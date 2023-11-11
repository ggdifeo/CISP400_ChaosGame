#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    vector<CircleShape> stars;

    default_random_engine generator;
    uniform_int_distribution<int> uniform_dist(0, 2);

    Font font;
    if (!font.loadFromFile("font.ttf")) 
    {
        cout << "Error loading font!" << endl;
        return -1;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(Color::White);
    text.setPosition(10, 10);

    Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(250);
    titleText.setFillColor(Color(210, 43, 41));
    titleText.setOutlineColor(Color::White);
    titleText.setOutlineThickness(2);
    titleText.setPosition(150, 140);
    titleText.setString("CHAOS GAME");

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

    int vertexCount = 0;
    bool titleScreen = true;
    bool enterPressed = false;
    int step = 1;
    Clock rainbowTimer;
    float rainbowDuration = 8.0f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && titleScreen) 
            {
                titleScreen = false;
            }

            if (!titleScreen && event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 10 && step == 1)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

                        if (vertices.size() == 10)
                        {
                            text.setString("");
                            text.setString("You have reached the max vertices.\nPress Enter to set midpoints.");
                            window.draw(text);
                            step = 2;
                        }
                    }
                    else if (step == 2 && enterPressed)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }  
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (step == 1)
                {
                    enterPressed = true;
                }
                else if (step == 2 && points.size() > 0)
                {
                    // Generate fractal pattern for all vertices
                    for (const Vector2f& vertex : vertices)
                    {
                        for (int i = 0; i < 50; i++)
                        {
                            int randomSelection = uniform_dist(generator);
                            Vector2f pick_random_vertex = vertices[randomSelection];
                            Vector2f last_point = vertex;
                            Vector2f calculate_midpoint = (pick_random_vertex + last_point) / 2.0f;
                            points.push_back(calculate_midpoint);
                        }
                    }
                    step = 3; // Move to the next step after generating the fractal pattern
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (points.size() > 0 && step == 3)
        {
            // Draw fractal points
            for (size_t i = 0; i < points.size(); ++i)
            {
                CircleShape point(2);
                point.setPosition(points[i]);
                point.setFillColor(Color::White);
                window.draw(point);
            }
        }

        window.clear();

        if (titleScreen)
        {
            // Customize stars here
            CircleShape star;
            star.setRadius(2);
            star.setPosition(rand() % 1920, rand() % 1080);
            star.setFillColor(Color::White);
            stars.push_back(star);

            // Draws out the stars on the title screen
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
            text.setString("CLICK TO ADD 3 STARTING POINTS ON SCREEN, \n THEN PRESS ENTER."); 
            window.draw(text);
        }
        else if (step == 2)
        {
            text.setString("Step 2: Click where you want midpoints to be.\nPress Enter to generate fractal pattern."); 
            window.draw(text);
        }
        else if (step == 3)
        {
            text.setString("ENJOY THE FRACTAL PATTERN!\nPRESS 'ESC' TO EXIT WHEN DONE"); 
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

    return 0;
}
