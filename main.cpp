


//----HASSAN NAQVI---//
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
int main()
{
    int score = 0;
    int scr = 0;

    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "Tetris");
    Texture obj1, obj2, obj3, obj4;

    //------ADDING MUSIC-------//
    
    Music music;                                                    // ddeclaring music
    if (!music.openFromFile("Tetris.ogg"))
    {
        cout << "Error"; // error
    }
    music.setLoop(true);
    music.play();
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadow.png");

    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj4);           //New sprite for shadow
    int delta_x = 0, colorNum = 1;

    bool start = false;
    float timer = 0;
    bool button = false;

    float delay = 0.3;
    bool rotate = 0;
    Clock clock;

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //----MY VARIABLES------//
        bool button = false;
 


        int level = 1;                                                  //Convert number and words in string so they can be stored and displayed on screen
        Font arial;                                             
        arial.loadFromFile("arial.ttf");
        ostringstream showLevel;
        showLevel << "Level: " << level;

        Text textLevel;
        textLevel.setCharacterSize(20); // POLISHINNG
        textLevel.setPosition(230, 120);
        textLevel.setFont(arial);
        textLevel.setString(showLevel.str());
        textLevel.setFillColor(Color::Yellow);

        // Displaying Score

        arial.loadFromFile("arial.ttf");
        std::ostringstream myScore;
        myScore << "Score: " << score;

        Text textScore;
        textScore.setCharacterSize(20); // POLISHINNG
        textScore.setPosition({230, 150});
        textScore.setFont(arial);
        textScore.setString(myScore.str());
        textScore.setFillColor(Color::Yellow);

     
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            {                                           // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                    rotate = true;                      // Rotation gets on
                else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                    delta_x = -1;                       // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                    delta_x = 1;                        // Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space) // Check if the other key pressed is SPACE key
                    button = true;

                else if (e.key.code == Keyboard::Down)  // Check if the other key pressed is UP key
                    delay = 0.01;                       // Moves Fast
                else if (e.key.code == Keyboard::Enter) // Check if the other key pressed is ENTER key
                {
                    start = true;
                    timer = 0;
                }
            }

            
        } 

        ///////////////////////////////////////////////
        ///* START CALLING YOUR FUNCTIONS HERE *///
        
        CompleteLine();
        fallingPiece(timer, delay, colorNum);
        //fallspace(button);
        movement(delta_x);
        rotation(rotate);
        myshadow();

        ///////*********** Quit GAME ***************//
        {
            int i = 0, count = 0;
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j])
                {
                    obj3.loadFromFile("img/gameover.jpg");
                }
            }
        }

        //***********SCOREEEEE********//

        ///* YOUR CALLING STATEMENTS END HERE *///


        //To calculate the score according to rubics values//
        {
            for (int k = 1; k == 1; k++)
            {
                score = 0;
                for (int i = M - 1; i > 0; i--)
                {
                    int C = 0;
                    for (int j = 0; j < N; j++)
                    {

                        if (gameGrid[i][j])
                        {
                            
                            C++;
                         
                        }
                    }
                    if (C == N)
                    {
                        score++;
          
                    }
                }
                if (score == 1)
                    scr += 10;
                if (score == 2)
                    scr += 30;
                if (score == 3)
                    scr += 60;
                if (score == 4)
                    scr += 100;
            }

            
        }
        // By reinitialization the changed variables, the same idea is applied to new and next piece//
        delay = 0.3;
        delta_x = 0;
        rotate = 0;
        button = false;


        myScore.str("");
        myScore << "Score " << scr;
        textScore.setString(myScore.str());
        // cout << score << endl;



        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }

        for (int i = 0; i < 4; i++)
        {

            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }

        for (int i = 0; i < 4; i++)
        {
            int b = rand() % 7;                                                     //Same things done for shadow as well
            shadow.setTextureRect(IntRect(b * 18, 0, 18, 18));
            shadow.setPosition(yourshadow[i][0] * 18, yourshadow[i][1] * 18);
            shadow.move(28, 31);
            window.draw(shadow);
        }

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        window.draw(textLevel);
        window.draw(textScore);

        //---The Window that now Contains the Frame is Displayed---//

        window.display();
    }
    return 0;
}
