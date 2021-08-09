#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <time.h>
#define NORTHx  0
#define NORTHy  -1
#define SOUTHx  0
#define SOUTHy  1
#define WESTx   -1
#define WESTy   0
#define EASTx   1
#define EASTy   0

using namespace std; //For easy usage of standard library - primarily for cout.
int field[16]{ 0 }; //The playing field - a one dimensional array.
int compfield[16]{ 0 }; //The playingfield for comparing whether something changed.
bool doclose = false; // Boolean that defines whether window should close or not.

// Above: Important global variables. Below: Declaration of variables for the different functions. Done in order to prevent redeclaration of variables on every call on the functions. 
// No need to do this for main, considering it only ever gets called once anyways.

//Function addnumb()

int a;   //a = Starting number.
int num; // num = The index of where in the playing field the number spawns.
int ind; // ind = index

bool voll = false;  // True if field is full (no 0 in field), else False.
int startnumb[2] = { 2, 4 }; // For randomized choice between 2 and 4.

//Function move()
int index; // Index for field[].
int num1;      // First number, in this case the one in the middle. e.g. [num3, num1, num2]
int y, x;      // y = index / 4, where y is (0-3) | x = index % 4where x is (0-3)
int ya, xa;    // ya = y + movd[1], where ya is (0-3) | xa = y + movd[0], where xa is (0-3)
int num2;      // Second number, in this case the one to the right. e.g. [num3, num1, num2]
int yb, xb;    // yb = y - movd[1], where yb is (0-3) | xb = x - movd[0], where xb is (0-3)
int num3;      // Third number, in this case the one to the left. e.g. [num3, num1, num2]
bool inbounds1;// Used for the actual inbound check.
bool inbounds2;// Used for the actual inbound check.

/// <summary>
/// Testing function used to output the complete playingfield - not required to play the game.
/// </summary>
/*void output_test()
{
    for (int i = 0; i < 16; i++) //i = index
    {
        cout << field[i] << '!';
        cout << compfield[i] << ' ';
    };
    cout << "    ";
}*/

/// <summary>
/// Adds a number to an empty (0) spot in the field.
/// </summary>
void addnumb()
{
	srand(time(0));
        ind = 0;
        voll = false;
    while (voll == false)
    {
        if (field[ind] == 0 && ind != 16)
            voll = true;
        else if (ind == 16)
            {doclose = true;
             cout << "You lost!";
             return;}
        ind++;
    }
    
    do {a = rand() % 2;
		num = rand() % 16;}
    while(field[num] != 0);
	field[num] = startnumb[a];
}

/// <summary>
/// Most important function for 2048 to work.
/// <para /> movd[] defines in which direction the checks happen, and whether the check happens from top to bottom, or from the bottom to the top. Example; see line XX.
/// <para /> inboundmov and inboundcom only decide which of two possible things happen - combine or move.
/// </summary>
/// <param name="movd">= Array where movd[0] = x and movd[1] = y. </param>
/// <param name="inboundmov">= Parameter used to tell whether move happens.</param>
/// <param name="inboundcom">= Parameter used to tell whether combine happens.</param>
void move(int movd[2], bool inboundmov, bool inboundcom)
{
    inbounds1 = inboundmov,
    inbounds2 = inboundcom;
    if (movd[0] == 1 || movd[1] == 1) // Decides whether direction is top to bottom or bottom to top.
    {
        for (index = 0; index <= 15; index++) //Top to bottom.
        {
            num1 = index;
            y = index / 4;
            x = index % 4;
            ya = y + movd[1];
            xa = x + movd[0];
            num2 = ya * 4 + xa;
			yb = y - movd[1];
			xb = x - movd[0];
			num3 = yb * 4 + xb;

			//cout << num1 << ' ' << '!' << ' ' << num2 << ' ';
			if ((movd[0] == 1 && x == 3) || (movd[1] == 1 && y == 3))
				inbounds1 = false;
            if (field[num1] != 0 && field[num2] == 0 && inbounds1 == true )
            {
                field[num2] = field[num1];
                field[num1] = 0;
			}
            if ((movd[0] == 1 && x == 0) || (movd[1] == 1 && y == 0))
				inbounds2 = false;
            if (field[num1] != 0 && field[num3] != 0 && field[num1] == field[num3] && inbounds2 == true)
            {
                field[num3] = field[num3] + field[num1];
                field[num1] = 0;
            }
			inbounds1 = inboundmov;
			inbounds2 = inboundcom;
        }
    }
    if (movd[0] == -1 || movd[1] == -1)
    {
        for (index = 15; index > -1; index--) //Bottom to top.
        {
            num1 = index;
            y = index / 4;
            x = index % 4;
            ya = y + movd[1];
            xa = x + movd[0];
            num2 = ya * 4 + xa;
            yb = y - movd[1];
            xb = x - movd[0];
            num3 = yb * 4 + xb;

			//cout << num1 << ' ' << '!' << ' ' << num2 << ' ';
            if ((movd[0] == -1 && x == 0) || (movd[1] == -1 && y == 0))
                inbounds1 = false;
            if (field[num1] != 0 && field[num2] == 0 && inbounds1 == true)
            {
                field[num2] = field[num1];
                field[num1] = 0;
            }
            if ((movd[0] == -1 && x == 3) || (movd[1] == -1 && y == 3))
                inbounds2 = false;
            if (field[num1] != 0 && field[num3] != 0 && field[num1] == field[num3] && inbounds2 == true)
            {
                field[num3] = field[num3] + field[num1];
                field[num1] = 0;
            }
			inbounds1 = inboundmov;
			inbounds2 = inboundcom;
        }
    }
}

/// <summary>
/// Very simple way of checking whether someone won. Could be better, but this was required, yet not my goal.
/// </summary>
void wincheck()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        if (field[i] == 8192)
        {
            cout << "You won!";
            doclose = true;
        }
    }
}

/// <summary>
/// The main part of the programm. Initializes the window in a 720x720 resolution, then creates the 'cells' wherein the numbers lie.
/// <para /> The higher the number, the more the background becomes red. Stops with complete red at 2048, though by then most people would stop playing anyways. 
/// <para /> 8192 is the limit of displayable numbers, and as such anyone who reaches it automatically wins.
/// </summary>
/// <returns> Returns 0 when succesfully completed. </returns>
int main()
{
    sf::Font font;
    font.loadFromFile("arial.ttf");

    float size = 720.0/4;

    sf::RenderWindow window(sf::VideoMode(720, 720), "2048 game");
    sf::RectangleShape shape(sf::Vector2f(size,size));
    
    
    shape.setOutlineColor(sf::Color(0, 0, 0, 255));
    shape.setOutlineThickness(-2);
    
    int textsize = size*0.43;
    sf::Text dtext(to_string(field[0]), font); //Display text
    dtext.setCharacterSize(textsize);
    dtext.setStyle(sf::Text::Bold);
    dtext.setFillColor(sf::Color());
    addnumb();  //Very first number that is required to start the game.

    int passarmov[2];   //Passing array for movement.
    int passarcom[2];   //Passing array for combining.
    double color = 0;   //Changeable variable for color in order to accomplish the change from Yellow to Red for the backgrounds of the cells with higher numbers.
    int repeata, repeat;//repeata and repeat are to repeat everything enough times to truly move and combine everything that is possible.
    int x, y;           // x and y are for displaying the cells.
    int i;              //i = index.

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
		if (event.type == sf::Event::Closed)
			window.close();                         //Close window when pressing the close button in the top right corner.

        if (event.type == sf::Event::KeyPressed)
            {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // If W is pressed, move and combine into north.
            {
                copy(begin(field), end(field), begin(compfield));
                passarmov[0] = NORTHx; // Movement from bottom to the top.
                passarmov[1] = NORTHy;
                passarcom[0] = SOUTHx; // Combine is the reverse direction, so in this case top to bottom. Always reverse of the movement.
                passarcom[1] = SOUTHy;
                for (repeat = 0; repeat < 5; repeat++) // Repeat eveything 4 times - just to be completely sure that everything happens as it should.
                {
                    for (repeata = 0; repeata < 4; repeata++) // Repeat move with passarmov 3 times.
                    {
                        move(passarmov, true, false);
                    }
                    move(passarcom, false, true);
                }
                for (i = 0; i < 16; i++) 
                {
                    if (field[i] != compfield[i]) // Compare pre movement field with post movement field to decide whether a change happened. If something changed, add number. Otherwise, nothing happens.
                    {
                        addnumb();
                        break;
                    }
                }
                wincheck(); // Check for the wincondition only after moving things.
                if (doclose == true) // Needed in order to close the window using the wincheck.
                    window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                copy(begin(field), end(field), begin(compfield));
                passarmov[0] = SOUTHx; // Movement from top to bottom.
                passarmov[1] = SOUTHy;
                passarcom[0] = NORTHx; // Combine in reverse direction.
                passarcom[1] = NORTHy;
				for (repeat = 0; repeat < 5; repeat++) // Repeat eveything 4 times - just to be completely sure that everything happens as it should.
				{
					for (repeata = 0; repeata < 4; repeata++) // Repeat move with passarmov 3 times.
					{
						move(passarmov, true, false);
					}
					move(passarcom, false, true);
				}
				for (i = 0; i < 16; i++)
				{
					if (field[i] != compfield[i]) // Compare pre movement field with post movement field to decide whether a change happened. If something changed, add number. Otherwise, nothing happens.
					{
						addnumb();
						break;
					}
				}
				wincheck(); // Check for the wincondition only after moving things.
				if (doclose == true) // Needed in order to close the window using the wincheck.
					window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                copy(begin(field), end(field), begin(compfield));
                passarmov[0] = EASTx; // Movement from left to right.
                passarmov[1] = EASTy;
                passarcom[0] = WESTx; // Combine is in reverse, in this case from right to left.
                passarcom[1] = WESTy;
				for (repeat = 0; repeat < 5; repeat++) // Repeat eveything 4 times - just to be completely sure that everything happens as it should.
				{
					for (repeata = 0; repeata < 4; repeata++) // Repeat move with passarmov 3 times.
					{
						move(passarmov, true, false);
					}
					move(passarcom, false, true);
				}
				for (i = 0; i < 16; i++)
				{
					if (field[i] != compfield[i]) // Compare pre movement field with post movement field to decide whether a change happened. If something changed, add number. Otherwise, nothing happens.
					{
						addnumb();
						break;
					}
				}
				wincheck(); // Check for the wincondition only after moving things.
				if (doclose == true) // Needed in order to close the window using the wincheck.
					window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                copy(begin(field), end(field), begin(compfield));
                passarmov[0] = WESTx; // Movement from right to left.
                passarmov[1] = WESTy;
                passarcom[0] = EASTx; // Combine in reverse direction.
                passarcom[1] = EASTy;
				for (repeat = 0; repeat < 5; repeat++) // Repeat eveything 4 times - just to be completely sure that everything happens as it should.
				{
					for (repeata = 0; repeata < 4; repeata++) // Repeat move with passarmov 3 times.
					{
						move(passarmov, true, false);
					}
					move(passarcom, false, true);
				}
				for (i = 0; i < 16; i++)
				{
					if (field[i] != compfield[i]) // Compare pre movement field with post movement field to decide whether a change happened. If something changed, add number. Otherwise, nothing happens.
					{
						addnumb();
						break;
					}
				}
				wincheck(); // Check for the wincondition only after moving things.
				if (doclose == true) // Needed in order to close the window using the wincheck.
					window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }
        }
    
        window.clear(); // Clears old cells.
        for (y = 0; y < 4; y++)
        {
            for (x = 0; x < 4; x++)
            {
                if (field[y * 4 + x] != 0) // Changes color for the current cell according to the number in the field with the according index, but only if it's not a 0.
                    color = log2(field[y * 4 + x]); 
                shape.setPosition(sf::Vector2f(0, y * size));
                shape.move(sf::Vector2f(size * x, 0));
                if (color == 0) // If color didn't change, set the fillcolor back to white.
                    shape.setFillColor(sf::Color(255,255,255,255));
                if (color != 0) //If the color changed, change the fillcolor accordingly on the gradient from yellow to red.
                    shape.setFillColor(sf::Color(255, 255 - color * 24, 0, 255));
                window.draw(shape);
                color = 0; //Sets color back to 0 after every cell.

                dtext.setString(to_string(field[y*4+x])); // Set display text string to the number in the field at the current index.
                
                // Following code is in order to make sure the text is centered.
                sf::FloatRect rectBounds = shape.getGlobalBounds();
                sf::FloatRect textBounds = dtext.getGlobalBounds();
                dtext.setPosition(rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2), 0);
                dtext.move(sf::Vector2f(0, y * size + size / 5));
                window.draw(dtext);
            };
        };
        window.display(); // Display the new cells.
    }
    return 0;
}