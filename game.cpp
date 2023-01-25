//============================================================================
// Name        : .cpp
// Author      : FAST CS Department HASSAN RASOOL
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Battleship.
//============================================================================

#ifndef Battleship_CPP_
#define Battleship_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

#define SUBTRACT 200

// global variables
string name;
char grid[9][9]; // backend player1 grid // idea : use DMA here and pointers
char computer_grid[9][9]; // backend computer grid
bool bool_main_menu = true;
bool bool_game_menu = false;
bool bool_leaderboard_menu = false;
int selected_ship; // variable to select either of the ship of a certain size i.e. 4,3,2,1
int remapped_x; 
int remapped_y;
int map_x;
int map_y;
int helper_x;
int helper_y;
int old_x;
int old_y;
int selected_ship2;
bool ship4 = false;
bool ship3[2] = {false, false};
bool ship2[3] = {false, false, false};
bool ship1[4] = {false, false, false, false};
bool AUTO = false;
bool computer_ship4 = false;
bool computer_ship3[2] = {false, false};
bool computer_ship2[3] = {false, false, false};
bool computer_ship1[4] = {false, false, false, false};
bool battle_mode = false;
int missile_fire_x;
int missile_fire_y;
bool turn = false;
bool bool_name = false;
int comupters_correct_hits=0;
int players_correct_hits = 0;
int players_score=0;
int consecutive_miss=0;
int balance = 500;
string winner; // variable to hold winners name
bool bool_winner = true;

//Function prototypes
void mainMenu();
void gameMenu();
void displayBoard(); // idk
void displayBattleships(); // idk
void DrawTriangle(int, int, int, int, int, int); // helper draw triangle function
void DrawRectangle(int, int, int, int);
void placement(); // draws ship on grid after they have been placed
bool place_on_backend_grid(int, int, string); // place ship on our backend grid after they have been placed on the front end grid
void error(); // displays an error when ship cannot be placed on grid
void prompt(); // displays which battle ship has been selected
void clear_prompt(); // clears error prompts and ships after they are placed
void display_backend_grid(string); // helper function for backend logic
void battle_start(); 
void player1_battleships(); // display placed battleships on battlefield
void randomly_place_battleships(string); // auto
bool check_ship(string);
void computer_frontend_grid();
void players_frontend_grid();
void display_name();
void get_name();
void displayWinner(); // this function displays the name of the winner on the screen
void reset_variables(); // this function resets all global variables before starting next round of game to avoid any errors
void view_leaderboard();
// void view_balance();

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


int xI = 400, yI = 400;

void drawObject() {
	DrawSquare(xI, yI, 20, colors[WHITE]);
	glutPostRedisplay();
}


bool flag = true;
void moveObject() {
	
	if (xI > 10 && flag) {
		xI -= 10;
		// cout << "going left";
		if(xI < 100)
			
			flag = false;

	}
	else if (xI < 1010 && !flag) {
		// cout << "go right";
		xI += 10;
		if (xI > 900)
			flag = true;
	}
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim red and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Red Square
	DrawSquare(400, 20, 40, colors[RED]);
	
	//Green Square
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
	
	drawObject();
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		xI -= 10;

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		xI += 10;
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yI += 10;
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yI -= 10;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (bool_name==false && bool_game_menu==true)
	{
		name += key;
		glutDisplayFunc(display_name);

		if (key == 13) // user inputs enter
		{
			bool_name = true;
			
			glutDisplayFunc(gameMenu);
		}			
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	moveObject();

	// cout << "Timer function called after n number of seconds/milliseconds idk : " << endl;

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	// cout << x << " " << y << endl;
	// glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	// glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		// cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} 
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		// start game , temporary approach
		// glutDisplayFunc(gameMenu);
	}

	if (bool_leaderboard_menu)
	{
		if (x>=500 && x< 570 && y>=720 && y<= 740)
		{
			bool_leaderboard_menu=false;			
			bool_main_menu = true;
			reset_variables();
			glutDisplayFunc(mainMenu);
		}
	}

	// when user clicks on start game in main menu
	if (bool_main_menu == true)
	{
		if(x>=407 && x< 619 && y>=325 && y<= 341) // user clicks on "START NEW GAME"
		{
			bool_game_menu = true;
			bool_main_menu = false;

			glutDisplayFunc(get_name);

			if (bool_name)
			{
				glutDisplayFunc(gameMenu);
				return;
			}
			// glutPostRedisplay();
		}
		else if (x>=401 && x< 647 && y>=275 && y<= 290) // user clicks on "VIEW LEADER BOARD"
		{
			bool_leaderboard_menu = true;
			bool_main_menu = false;
			bool_game_menu = false;
			glutDisplayFunc(view_leaderboard);
			glutPostRedisplay();
		}
		else if (x>=407 && x< 619 && y>=325 && y<= 341) // user clicks on "VIEW BALANCE"
		{
			// glutDisplayFunc(view_balance);
		}
	}

	if (bool_game_menu == true && !AUTO)
	{
		cout << endl << "true" << endl;
		helper_x = x;
		helper_y = y;
		// user clicks on battleship of size 4

		if ( x >= 543 && x <= 735 && y>=256 && y<= 300 && ship4 == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 4;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}
		// user clicks on battle ship of size 3
		else if ((x >= 536 && x <= 685 && y >= 355 && y <= 400) && ship3[0] == false )
		{
			old_x = x;
			old_y = y;
			selected_ship = 3;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}

		else if (x >= 733 && x <= 883 && y >= 356 && y <= 400 && ship3[1] == false )
		{
			old_x = x;
			old_y = y;
			selected_ship = 3;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}

		// user clicks on battle ship of size 2
		else if ((x >= 536 && x <= 632 && y >= 455 && y <= 500) && ship2[0] == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 2;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}

		else if (x >= 685 && x <= 785 && y >= 455 && y <= 500 && ship2[1] == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 2;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;			
		}

		else if (x >= 853 && x <= 953 && y >= 455 && y <= 500 && ship2[2] == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 2;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;			
		}		

		// user clicks on battle ship of size 1
		else if (x >= 534 && x <= 585 && y >= 555 && y <= 595 && ship1[0] == false )
		{
			old_x = x;
			old_y = y;
			selected_ship = 1;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}		

		else if ((x >= 633 && x <= 685 && y >= 555 && y <= 595 && ship1[1] == false))
		{
			old_x = x;
			old_y = y;
			selected_ship = 1;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}	

		else if (x >= 732 && x <= 785 && y >= 555 && y <= 595 && ship1[2] == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 1;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}	

		else if (x >= 835 && x <= 885 && y >= 555 && y <= 595 && ship1[3] == false)
		{
			old_x = x;
			old_y = y;
			selected_ship = 1;
			glutDisplayFunc(prompt);
			glutPostRedisplay();
			return;
		}					

		cout << "Selected ship : " << selected_ship << endl;
		if (selected_ship != 0) // 0 indicates an un selected battleship
		{
			// enter this function only after a ship has been selected
			if (x > 81 && x < 518 && y > 266 && y < 705)
			{
				// user has now clicked inside the grid after selecting a battle ship 
				// map x = clicked x - starting x
				map_x = 274 - SUBTRACT - x;
				map_x /= 50;

				map_y = 250 - y;
				map_y /= 50;

				map_x *= -1;
				map_y *= -1;

				int grid_x = map_y;
				int grid_y = map_x;

				// cout << "You clicked on grid coordinate : " << endl;
				// cout << "x : " << grid_x << endl;
				// cout << "y : " << grid_y << endl;

				bool status;
				// get status whether ship can be placed on grid or not
				// using our backend grid
				status = place_on_backend_grid(grid_x, grid_y, "PLAYER1");

				if (status == true)
				{
					// draw on grid
					helper_x = x;
					helper_y = y;
					selected_ship2 = selected_ship;

					glutDisplayFunc(placement);
					selected_ship = 0;

					// make the ship disappear here...
				}
				else 
				{
					// display an error
					glutDisplayFunc(error);
					glutPostRedisplay();
					selected_ship = 0;
				}
			}
		}
	}

	cout << endl << "MOUSE CLICKED ON COORDINATES : " << endl;
	cout << "X : " << x << endl;
	cout << "Y : " << y << endl;
	selected_ship = 0;

	if (x >= 902 && x <= 947 && y >= 46 && y <= 61 && bool_game_menu) //BATTLE STARTS WHEN USEER CLICKS ON NEXT
	{
		if(ship4 && ship3[0] && ship3[1] && ship2[0] && ship2[1] && ship2[2] && ship1[0] && ship1[1] && ship1[2] && ship1[3] )
		{
			glutDisplayFunc(battle_start);
		}
	}

	// auto placement of battleships when user clicks on the button 'auto'
	if (x >= 895 && x <= 975 && y >= 741 && y <= 770 && bool_game_menu)
	{
		AUTO = true;
		randomly_place_battleships("PLAYER1");
		display_backend_grid("PLAYER 1");

		glutDisplayFunc(battle_start);
		AUTO = false;
	}

	if (battle_mode) // battle mode has now started
	{
		cout << "I am now in battle mode" << endl;
		if (x >= 550 && x <= 1000 && y >= 190 && y <= 640 ) // user has now fired a missle on computer's grid
		{
			// remapped x and remapped y normalize the front end coordinates to backend grid coordinates
			// i.e 550, 190 is remapped to 0,0
			// .....
			remapped_x = (x - 550)/50;
			remapped_y = (y - 190)/50;

			swap(remapped_x, remapped_y);
			missile_fire_x = remapped_x;
			missile_fire_y = remapped_y;
			// cout << "Missile fired on grid coordinate : " << remapped_x << ',' << remapped_y << endl;
			// check_ship("COMPUTER")
			{
				glutDisplayFunc(computer_frontend_grid);
				// glutPostRedisplay();
			}

			// computer's turn
			if (!turn)
				glutDisplayFunc(players_frontend_grid);
			else
				turn = false;
		}
	}

	//BUTTON FOR GOING TO MAIN MENU AFTER WINNING
	//	DrawRectangle(850 ,90, 130, 30 , colors[BLACK]);
	// if( x>=850 && x<=150 && y>= 90 && y<= 120)
	if (x>=725 && x<= 985 && y >= 720 && y <= 759 && bool_winner)
	{
		bool_winner = false;
		bool_main_menu = true;
		bool_game_menu = false;

		cout << "main menu clicked" << endl;

		reset_variables();
		glutDisplayFunc(mainMenu);
	}

	glutPostRedisplay();
}

void clear_prompt() //THIS FUNCTION CLEARS THE BATTLESHIPS WHEN THEY ARE PPLACED ON CORRECT PLACES
{
	helper_x = old_x;
	helper_y = old_y;
	//FOR BATTLESHIP SIZE 4
	if(helper_x>=543 && helper_x <= 735 && helper_y>=256 && helper_y<= 300)
	{
		ship4 = true;
		DrawRectangle(543, 540, 200, 60, colors[TURQUOISE]);
	}
	//FOR BATTLESHIP SIZE 3
	else if( (helper_x >= 536 && helper_x <= 685 && helper_y >= 355 && helper_y <= 400) )
	{
		ship3[0] = true;
		DrawRectangle(535 , 440, 150, 60,colors[TURQUOISE]);
	}
	else if( helper_x >= 733 && helper_x <= 883 && helper_y >= 356 && helper_y <= 400 ) 
	{
		ship3[1] = true;
		DrawRectangle(735 , 440, 150, 60,colors[TURQUOISE]);
	}
	//FOR BATTLESHIP SIZE 2
	else if( helper_x >= 536 && helper_x <= 632 && helper_y >= 455 && helper_y <= 500) 
	{
		ship2[0] = true;
		DrawRectangle(535, 330, 100, 60,colors[TURQUOISE]);
	}
	else if( (helper_x >= 685 && helper_x <= 785 && helper_y >= 455 && helper_y <= 500)) 
	{
		ship2[1] = true;
		DrawRectangle(685, 330, 100, 60,colors[TURQUOISE]);
	}
	else if ((helper_x >= 853 && helper_x <= 953 && helper_y >= 455 && helper_y <= 500)) 
	{
		ship2[2] = true;
		DrawRectangle(845, 330, 100, 60,colors[TURQUOISE]);
	}
	//FOR BATTLESHIP SIZE 1
	else if ((helper_x >= 534 && helper_x <= 585 && helper_y >= 555 && helper_y <= 595)) 
	{
		ship1[0] = true;
		DrawRectangle(535, 245, 100, 60,colors[TURQUOISE]);
	}

	else if ((helper_x >= 633 && helper_x<= 685 && helper_y >= 555 && helper_y <= 595)) 
	{
		ship1[1] = true;
		DrawRectangle(633, 245, 100, 60,colors[TURQUOISE]);
	}

	else if (helper_x>= 732 && helper_x <= 785 && helper_y >= 555 && helper_y <= 595) 
	{
		ship1[2] = true;
		DrawRectangle(730, 245, 100, 60,colors[TURQUOISE]);
	}

	else if (helper_x >= 835 && helper_x <= 885 && helper_y >= 555 && helper_y <= 595)
	{
		ship1[3] = true;
		DrawRectangle(835, 245, 100, 60,colors[TURQUOISE]);
	}

	DrawRectangle(593, 840-745, 271, 30, colors[TURQUOISE]);	// clear selected ship prompt at bottom

	glutSwapBuffers();
}

void prompt()
{
	// cout << "HELPER X : " << helper_x << endl;
	// cout << "HELPER Y : " << helper_y << endl;
	
	DrawString(600, 100, "Selected Ship of Length " + to_string(selected_ship), colors[WHITE]);	
	glutSwapBuffers();
}

void error()
{
	string error = "Ship Cannot be placed here! Try another place";
	DrawString(300, 700, error, colors[RED]);	

	glutSwapBuffers();

	sleep(1); // string disappears after 2 seconds

	DrawRectangle(290, 840-152, 487, 30, colors[TURQUOISE]);

	/*
		(290, 125)		(777, 115)
		(290, 155)		(777, 155)
	*/

	selected_ship = 0;
	glutSwapBuffers();
}

void placement() // int map_x, int map_y, int x, int y)
{
	// this re-draws the whole grid after a change is made i.e. a ship is placed
	int temp = 0;
{
	int x = helper_x;
	int y = helper_y;
	for (int i=1; i<10; i++)
	{
		DrawString(294 - SUBTRACT + temp, 600, to_string(i), colors[BLUE]);
		temp += 50;
	}

	temp = 0;
	for(int i=65; i<74; i++)
	{
		string t;
		t += char(i);
		DrawString(234 - SUBTRACT, 550 - temp, t, colors[BLUE]);
		temp += 50;
	}

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 274 - SUBTRACT, 583,  274  - SUBTRACT, 133 , 10 , colors[TURQUOISE] );// VERTICAL 1
	DrawLine( 274 - SUBTRACT , 583 ,  724 - SUBTRACT , 583 , 10 , colors[TURQUOISE] ); //HORIZONTAL 1
	DrawLine( 724 - SUBTRACT , 583 , 724 - SUBTRACT , 133 , 10 , colors[TURQUOISE] ); //VERTICAL 2
	DrawLine( 274 - SUBTRACT , 133 ,  724 - SUBTRACT , 133 , 10 , colors[TURQUOISE] ); // HORIZONTAL 2

	//INNER LINES VERTICAL
	temp = 50;
	for( int i=0 ; i<9 ; i++)
	{
		DrawLine( 274+temp - SUBTRACT , 583,  274+temp - SUBTRACT , 133 , 2 , colors[TURQUOISE] );// VERTICAL 
		temp+=50;
	}

	//INNER LINES HORIZONTAl
	temp = 0;
	for( int i=0 ; i<9 ; i++)
	{
		DrawLine( 274 - SUBTRACT , 583+temp,  724  - SUBTRACT, 583+temp, 2 , colors[TURQUOISE] );// VERTICAL 
		temp-=50;
	}
}

	// now draw ship on the selected coordinates

	remapped_x = 74 + 50 * (map_x);
	remapped_y = 254 + 50 * map_y;

	// find next immediate ceil for x and y
	// for x starting from 74
	temp = 74;
	while (remapped_x > temp)
	{
		temp += 50;
	}
	remapped_x = temp;

	// for y starting from 254
	temp = 254;
	while (remapped_y > temp)
	{
		temp += 50;
	}
	remapped_y = temp;

	cout << "REMAPPED COORDINATES : " << endl;
	cout  << remapped_x << endl;
	cout << remapped_y << endl;

	// now we have the coordinates 
	// we can draw battleship on the grid

	int width = (selected_ship2 -1 ) * 50;

	DrawRectangle(remapped_x+50, 840-remapped_y-50, (width*-1), 50, colors[NAVY]);	
	int x_coordinate = (remapped_x + 50) - 50 * selected_ship2;
	DrawTriangle(x_coordinate, 840-remapped_y-25, x_coordinate + 50, 840-remapped_y, x_coordinate+50, 840-remapped_y-50, colors[NAVY]);

	glutDisplayFunc(clear_prompt);

	glutSwapBuffers(); // do not modify this line..
}

void gameMenu()
{
	bool_game_menu = true;
	// AUTO = true;
	//PLAYER NAME
	//BATTLESHIP COLOR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// DrawString(400, 700, "Start game", colors[NAVY] )	

	displayBoard();

	glutSwapBuffers();	
}

void DrawRectangle(int x_rectangle, int y_rectangle, int width, int height) // draw battleship helper function
{
	// Draws a rectangle of the specified color
	DrawRectangle(x_rectangle, y_rectangle, width, height, colors[NAVY]);
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) // draw battleship helper function
{
// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	DrawTriangle(x1, y1, x2, y2, x3, y3, colors[NAVY] ); 
}

void displayBattleships()
{
	// // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	// DrawTriangle( 743, 565 , 783, 585 , 783 , 545, colors[MISTY_ROSE] ); 

	// // Draws a rectangle of the specified color
	// DrawRectangle(783, 545, 200, 40, colors[RED]);

	// battleship of length 4
	DrawTriangle(743 - SUBTRACT, 565 , 783 - SUBTRACT, 585 , 783 - SUBTRACT , 545, colors[NAVY]);
	DrawRectangle(783 - SUBTRACT, 545, 150, 40), colors[NAVY];

	// TWO BATTLE SHIPS OF LENGTH 3

	int temp = 0;
	for (int i=0; i<2; i++)
	{
		DrawTriangle(743 + temp - SUBTRACT, 465, 783 + temp - SUBTRACT, 485, 783 + temp - SUBTRACT, 445, colors[NAVY]);
		DrawRectangle(783 + temp - SUBTRACT, 445, 100, 40, colors[NAVY]);

		temp += 200;		
	}

	// THREE BATTLESHIPS OF LENGTH 2
	temp = 0;
	for (int i=0; i<3; i++)
	{
		DrawTriangle(743 + temp - SUBTRACT, 365, 783 + temp - SUBTRACT, 385, 783 + temp - SUBTRACT, 345, colors[NAVY]);
		DrawRectangle(783 + temp - SUBTRACT, 345, 50, 40), colors[NAVY];

		temp += 150;				
	}

	// FOUR BATTLESHIPS OF LENGTH 4
	temp = 0;
	for (int i=0; i<4; i++)
	{
		DrawTriangle(743 + temp - SUBTRACT, 265, 783 + temp - SUBTRACT, 285, 783 + temp - SUBTRACT, 245), colors[NAVY];


		temp += 100;				
	}


	// drawObject();
	glutSwapBuffers(); // do not modify this line..	

}

void DisplayGrid()
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim red and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	DrawRectangle(0, 0, 1020, 840, colors[TURQUOISE]);
	DrawRectangle(74, 135, 450, 450, colors[WHITE]);

	int temp = 0;
	for (int i=1; i<10; i++)
	{
		DrawString(294 - SUBTRACT + temp, 600, to_string(i), colors[BLUE]);
		temp += 50;
	}

	temp = 0;
	for(int i=65; i<74; i++)
	{
		string t;
		t += char(i);
		DrawString(234 - SUBTRACT, 550 - temp, t, colors[BLUE]);
		temp += 50;
	}

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 274 - SUBTRACT, 583,  274  - SUBTRACT, 133 , 10 , colors[TURQUOISE] );// VERTICAL 1
	DrawLine( 274 - SUBTRACT , 583 ,  724 - SUBTRACT , 583 , 10 , colors[TURQUOISE] ); //HORIZONTAL 1
	DrawLine( 724 - SUBTRACT , 583 , 724 - SUBTRACT , 133 , 10 , colors[TURQUOISE] ); //VERTICAL 2
	DrawLine( 274 - SUBTRACT , 133 ,  724 - SUBTRACT , 133 , 10 , colors[TURQUOISE] ); // HORIZONTAL 2

	//INNER LINES VERTICAL
	temp = 50;
	for( int i=0 ; i<9 ; i++)
	{
		DrawLine( 274+temp - SUBTRACT , 583,  274+temp - SUBTRACT , 133 , 2 , colors[TURQUOISE] );// VERTICAL 
		temp+=50;
	}

	//INNER LINES HORIZONTAl
	temp = 0;
	for( int i=0 ; i<9 ; i++)
	{
		DrawLine( 274 - SUBTRACT , 583+temp,  724  - SUBTRACT, 583+temp, 2 , colors[TURQUOISE] );// VERTICAL 
		temp-=50;
	}

	// if(ship4 && ship3[0] && ship3[1] && ship2[0] && ship2[1] && ship2[2] && ship1[0] && ship1[1] && ship1[2] && ship1[3] ) //THIS PLAYS NEXT WHEN ALL THE BATTLESHIPS ARE PLACED
	{
		DrawString(900, 780, "Next", colors[WHITE]);
	}

	// Auto
	DrawString(900, 80, "AUTO", colors[WHITE]);

	displayBattleships();
	glutSwapBuffers(); // do not modify this line..
}

void displayBoard()
{
	int * n = new int;
	int * m = new int;

	*n = 14;
	*m = 24;


	glutDisplayFunc(DisplayGrid);
	glutSwapBuffers(); // do not modify this line..
}

void display_backend_grid(string player)
{
	cout << "------------------------------------" << "Displaying Battle grid of " << player << "------------------------------------" << endl << endl;
	if (player == "COMPUTER")
	{
		cout << "  ";
		for (int i=1; i<10; i++)
			cout << i << "  ";
		cout << endl;

		int temp = 65;
		for (int i=0; i<9; i++)
		{
			cout << char(temp) << "  ";
			temp++;
			for (int j=0; j<9; j++)
			{
				cout << computer_grid[i][j] << "  ";
			}
			cout << endl;
		}
		return;
	}
	cout << "  ";
	for (int i=1; i<10; i++)
		cout << i << "  ";
	cout << endl;

	int temp = 65;
	for (int i=0; i<9; i++)
	{
		cout << char(temp) << "  ";
		temp++;
		for (int j=0; j<9; j++)
		{
			cout << grid[i][j] << "  ";
		}
		cout << endl;
	}
}


void mainMenu() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawRectangle(0, 0, 1020, 840, colors[TURQUOISE]);

	DrawString(380, 700, "BATTLE SHIP GAME", colors[NAVY]);
	DrawString(400, 600, "MAIN MENU", colors[NAVY]);
	DrawString(400, 550, "VIEW LEADERBOARD", colors[NAVY]);
	DrawString(400, 500, "START NEW GAME", colors[NAVY]);
	DrawString(400, 450, "VIEW BALANCE", colors[NAVY]);
	DrawString(400, 400, "OPTIONS", colors[NAVY]);

	bool_winner = false;
	// bool_game_menu = true;
	// bool_main_menu = true;

	glutSwapBuffers();
}

bool place_on_backend_grid(int map_x1, int map_y1, string player) {
	// cout << "Grid X : " << map_x1 << endl;
	// cout << "Grid Y : " << map_y1 << endl;

	// char** temp; //idea
	if (player=="COMPUTER")
	{
		if(computer_ship4 && computer_ship3[0] && computer_ship3[1] && computer_ship2[0] && computer_ship2[1] && computer_ship2[2] && computer_ship1[0] && computer_ship1[1] && computer_ship1[2] && computer_ship1[3])
			return true;
		int length = selected_ship;

		cout << "SELECTED SHIP IN BACKEND GRID PLACE FUNCTION : " << selected_ship << endl;

		// overlapping ships check
		int temp = length;
		while(temp >= 0)
		{
			if (computer_grid[map_x1][map_y1 - temp] == 'C')
			{
				return false;
			}
			temp--;
		}

		// place on backend grid
		if (map_y1 - length >= -1)
		{		
			while(length > 0)
			{
				computer_grid[map_x1][map_y1] = 'C';
				map_y1--;
				length--;
			}
			// display_backend_grid();
			return true;
		}

		// else
		return false;
	}
	else
	{
		int length = selected_ship;

		cout << "SELECTED SHIP IN BACKEND GRID PLACE FUNCTION : " << 	selected_ship << endl;

		// overlapping ships check
		int temp = length;
		while(temp >= 0)
		{
			if (grid[map_x1][map_y1 - temp] == 'A')
			{
				return false;
			}
			temp--;
		}

		// place on backend grid
		if (map_y1 - length >= -1)
		{		
			while(length > 0)
			{
				grid[map_x1][map_y1] = 'A';
				map_y1--;
				length--;
			}
			// display_backend_grid();
			return true;
		}

		// else
		return false;
	}
}

void battle_start()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//COMPLETE GRID
	DrawRectangle(0, 0, 1020, 840, colors[TURQUOISE]);

	// SCORE BOARD
	// DrawRectangle

	//USER'S GRID
	DrawString(225, 670, "PLAYER 1", colors[NAVY]);
	DrawLine(50,200, 50 , 650, 10, colors[WHITE]);
	DrawLine(50,200, 500 , 200, 10, colors[WHITE]);
	DrawLine(500,200, 500 , 650, 10, colors[WHITE]);
	DrawLine(50,650, 500 , 650, 10, colors[WHITE]);

	glutDisplayFunc(player1_battleships);

	//COMPUTER'S GRID
	DrawString(700, 670, "COMPUTER", colors[NAVY]);
	DrawLine(550,200, 550 , 650, 10, colors[WHITE]);
	DrawLine(550,200, 1000 , 200, 10, colors[WHITE]);
	DrawLine(1000,200, 1000 , 650, 10, colors[WHITE]);
	DrawLine(550,650, 1000 , 650, 10, colors[WHITE]);

	for (int i=0; i<1020; i+=50)
	{
		DrawLine(0, i, 1020, i, 2, colors[WHITE]); // horizontal grid
		DrawLine(i, 0, i, 840, 2, colors[WHITE]);  // vertical grid
	}

	randomly_place_battleships("COMPUTER");
	display_backend_grid("COMPUTER");


	battle_mode = true;

	DrawString(470, 750, "Battle Start", colors[NAVY]);

	glutSwapBuffers();

}

void player1_battleships()
{
	for (int i=0; i<9; i++)
	{
		for (int j=0; j<9; j++)
		{
			if (grid[i][j] == 'A')
			{
				// draw a rectangle here
				remapped_x = 50 + 50*i;
				remapped_y = 200 + 50*j;

				swap(remapped_x, remapped_y);

				// cout << "(i, remapped_y) \t (j, remapped_x)" << endl;
				// cout << i << ',' << remapped_y << '\t' << j << ',' << remapped_x << endl;
				DrawRectangle(remapped_x-150, 800-remapped_y-150, 50, 50, colors[NAVY]);
			} 
		}
	}

	glutSwapBuffers();
}

void randomly_place_battleships(string player)
{
	if (player=="COMPUTER")
	{

		cout<<player<<" "<<computer_ship4<<computer_ship3[0]<<computer_ship3[1]<<computer_ship2[0]<<computer_ship2[1]<<computer_ship2[2]<<computer_ship1[0]<<computer_ship1[1]<<computer_ship1[2]<<ship1[3]<<endl;
		for (int i=0 ; i<10; ) // there are 10 battleships in total
		{
			if(computer_ship4 && computer_ship3[0] && computer_ship3[1] && computer_ship2[0] && computer_ship2[1] && computer_ship2[2] && computer_ship1[0] && computer_ship1[1] && computer_ship1[2] && computer_ship1[3])
				break;

			// randomly select a point in grid
			int random_x = rand()%9;
			int random_y = rand()%9;

			// inline selection of ship to place
			if (i==0) selected_ship = 4;
			else if (i==1 || i==2) selected_ship = 3;
			else if (i==3 || i==4 || i==5) selected_ship = 2;
			else selected_ship = 1;

			bool flag = place_on_backend_grid(random_x, random_y, player);
			if (flag) // this indicates that the ship has been placed successfully on the grid
			{
				if (i==0)
					computer_ship4 = true;
				if (i==1)
					computer_ship3[0] = true;
				if (i==2)
					computer_ship3[1] = true;
				if (i==3)
					computer_ship2[0] = true;
				if (i==4)
					computer_ship2[1] = true;
				if (i==5)
					computer_ship2[2] = true;
				if (i==6)
					computer_ship1[0] = true;
				if (i==7)
					computer_ship1[1] = true;
				if (i==8)
					computer_ship1[2] = true;
				if (i==9)
					computer_ship1[3] = true;

				// cout << "-----------SHIP NUMBER " << i+1 << "-----------------" << endl;
				// cout << "Selected ship of length " << selected_ship << " placed on grid randomly at coordinates : " << endl;
				// cout << "RANDOM X : " << random_x << endl;
				// cout << "RANDOM Y : " << random_y << endl;
				// display_backend_grid(player);
				i++;
			}
		}

	}
	else
	{
		cout<<player<<" "<<ship4<<ship3[0]<<ship3[1]<<ship2[0]<<ship2[1]<<ship2[2]<<ship1[0]<<ship1[1]<<ship1[2]<<ship1[3]<<endl;
		for (int i=0 ; i<10; ) // there are 10 battleships in total
		{
			if(ship4 && ship3[0] && ship3[1] && ship2[0] && ship2[1] && ship2[2] && ship1[0] && ship1[1] && ship1[2] && ship1[3])
				break;

			// randomly select a point in grid
			int random_x = rand()%9;
			int random_y = rand()%9;

			// inline selection of ship to place
			if (i==0) selected_ship = 4;
			else if (i==1 || i==2) selected_ship = 3;
			else if (i==3 || i==4 || i==5) selected_ship = 2;
			else selected_ship = 1;

			bool flag = place_on_backend_grid(random_x, random_y, player);
			if (flag) // this indicates that the ship has been placed successfully on the grid
			{
				if (i==0)
					ship4 = true;
				if (i==1)
					ship3[0] = true;
				if (i==2)
					ship3[1] = true;
				if (i==3)
					ship2[0] = true;
				if (i==4)
					ship2[1] = true;
				if (i==5)
					ship2[2] = true;
				if (i==6)
					ship1[0] = true;
				if (i==7)
					ship1[1] = true;
				if (i==8)
					ship1[2] = true;
				if (i==9)
					ship1[3] = true;

				i++;
			}
		}
	}
	battle_mode = true;
}

void displayWinner()
{
	// record scores and file handling
	AUTO = false;
	cout << "We now have a winner among us!!!" << endl << endl << endl;
	battle_mode = false;
	bool_main_menu = true;
	bool_game_menu = false;
	bool_winner = true;

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	DrawRectangle(0 ,0, 1020, 840 , colors[TURQUOISE]);
	
	int x = 200;
	int y = 500;

	if (winner == "THE WINNER IS PLAYER 1! CONGRATULATIONS " )
	{
		DrawString(x+20, y-50 , "YOUR SCORE IS :" +to_string(players_score), colors[BLACK]);
		winner = "THE WINNER IS " + name + "! CONGRATULATIONS ";

		// writing winners name to file
		string temp;
		for (int i=0; i<name.length(); i++)
		{
			// if name[i] is in range of printable ascii characters
			if ((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i]==' ')
			{
				temp += name[i];
			}
		}

		ofstream write; // this is for writing to the file	
		write.open("leaderboard.txt", ios::app);
		write << temp << '\t' << players_score << endl;
		write.close();
	}

	DrawString(x, y, winner, colors[BLACK]);

	DrawRectangle(850 ,80, 130, 40 , colors[BLACK]);
	DrawString(850, 100, " main menu", colors[WHITE]);

	glutSwapBuffers();
}

bool check_ship(string PLAYER) // checks if there is a ship at the missile fired coordinates on computers grid
{
	if(PLAYER == "COMPUTER")
	{
		if (computer_grid[missile_fire_x][missile_fire_y] == 'C')
		{
			players_correct_hits++;
			cout << "PLAYERS CORRECT HITS : " << players_correct_hits << endl;
			players_score += 60;
			if (players_correct_hits==20)
			{
				winner = "THE WINNER IS PLAYER 1! CONGRATULATIONS ";

				balance+= players_score;
				displayWinner();
				glutDisplayFunc(displayWinner);
				glutPostRedisplay();
			}
			return true;
		}
		else 
		{
			consecutive_miss++;
			if (consecutive_miss==2)
			{
				players_score -= 20;
				consecutive_miss=0;
			}
			return false;
		}
	}
	else
	{
		if (grid[missile_fire_x][missile_fire_y] == 'A')
		{
			comupters_correct_hits++;
			cout << "COMPUTERS CORRECT HITS : " << comupters_correct_hits << endl;
			if (comupters_correct_hits==20)
			{
				winner = "THE WINNER IS COMPUTER , BETTER LUCK NEXT TIME :(";
				glutDisplayFunc(displayWinner);
				glutPostRedisplay();
			}
			grid[missile_fire_x][missile_fire_y] = 'X';
			return true;
		}
		else 
		{
			grid[missile_fire_x][missile_fire_y] = 'B';
			return false;
		}
	} 
}

//FOR COMMPUTER'S RANDOM GRID
void  computer_frontend_grid() // displays updated computer grid when missile is fired
{
	cout << "(mx, my)" << endl;
	cout << missile_fire_x << ',' << missile_fire_y << endl;

	int x = missile_fire_y * 50 + 550;
	int y = missile_fire_x * 50 + 190;
	
	cout << "remapped fire x, remapped fire y" << endl;
	cout << x << ',' << y << endl;
	
	if (check_ship("COMPUTER"))
	{
		DrawString(x+25, 840-y-25, "X", colors[RED]);
	}
	else
	{
		DrawString(x+25, 840-y-25, "B", colors[BLACK]);
	}

	DrawRectangle(40, 790, 150 , 80, colors[BLACK]);
	DrawString(50, 800, "score : " +to_string(players_score), colors[WHITE]);


	glutSwapBuffers();
}

//FOR DISPLAYING THE PLAYERS GRID
void players_frontend_grid()  
{
	missile_fire_x = rand() % 9;
	missile_fire_y = rand() % 9; 	
	while (grid[missile_fire_x][missile_fire_y] == 'B' || grid[missile_fire_x][missile_fire_y] == 'X')
	{
		missile_fire_x = rand() % 9;
		missile_fire_y = rand() % 9; 
	}
	cout<<"random x and y   "<<missile_fire_x<<"    "<<missile_fire_y;

	int x = missile_fire_y * 50 + 50;
	int y = missile_fire_x * 50 + 190;
	
	if (check_ship("PLAYER1"))
	{
		DrawString(x+25, 840-y-25, "X", colors[RED]);
	}
	else
	{
		DrawString(x+25, 840-y-25, "B", colors[RED]);
	}



	turn = true; // it symbolises that the turn has been made

	glutSwapBuffers();
}

void display_name()
{
	DrawString(600, 500, name, colors[NAVY]);
	glutSwapBuffers();
}

void get_name()
{
	glClearColor (1, 1, 1, 1);
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	DrawRectangle (0,0,1020,840,colors[TURQUOISE]);
	DrawString (400, 500, "Enter your Name : ", colors[BLACK]);


	glutSwapBuffers();
}

void reset_variables()
{
	// global variables
	name="";
	// grid[9][9]; // backend player1 grid // idea : use DMA here and pointers
	// computer_grid[9][9]; // backend computer grid
	for (int i=0; i<9; i++)
	{
		for (int j=0; j<9; j++)
		{
			grid[i][j] = '.';
			computer_grid[i][j] = '.';
		}
	}
	bool_main_menu = true;
	bool_game_menu = false;
	selected_ship = remapped_x = remapped_y = map_x = map_y = helper_x = helper_y = old_x = old_y = selected_ship2 = 0;
	ship4 = false;
	AUTO = computer_ship4 = false;
	battle_mode = false;
	missile_fire_x = missile_fire_y = 0;
	turn = false;
	bool_name = false;
	comupters_correct_hits = players_correct_hits = players_score = consecutive_miss=0;
	balance = 500;
	winner="";
	bool_winner = false;

	ship3[0] = ship3[1] = ship2[0] = ship2[1] = ship2[2] = ship1[0] = ship1[1] = ship1[2] = ship1[3] = false;
	computer_ship3[0] = computer_ship3[1] = computer_ship2[0] = computer_ship2[1] = computer_ship2[2] = computer_ship1[0] = computer_ship1[1] = computer_ship1[2] = computer_ship1[3] = false;
}

void view_leaderboard()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,1,0);
	int x=100, y=800, i=1;
	// get peoples name from file
    ifstream read; // for reading file data
    read.open("leaderboard.txt");

    while(!read.eof())
    {
		string temp_name;
		string temp_score;
		string temp;

        getline(read, temp);
		cout << temp << endl;
		// temp = temp_name;
		// temp_name = "";
		for (int i=0; i<temp.length(); i++)
		{
            if ((temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122) || temp[i]==' ')
            {
                temp_name += temp[i];
            }
            else
            {
                temp_score += temp[i];
            }
		}		
        // cout << to_string(i) << ". " << temp_name << " score :  " << temp_score << endl;

		cout << "temp name : " << temp_name << endl;
		cout << "temp score : " << temp_score << endl;

		if (temp_name == "")
		{
			break;
		}

		string display = to_string(i) + ". " +  temp_name + "---------------------------------------" + temp_score; 
		DrawString(x, y, display, colors[BLACK]);
		y -= 50;
		i++; 
    }

    read.close();

	DrawString(500, 100, "BACK", colors[BLACK]);
	glutSwapBuffers();
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Battleship Game"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// initializing backend player and computer grid
	for (int i=0; i<9; i++)
	{
		for (int j=0; j<9; j++)
		{
			grid[i][j] = '.';
			computer_grid[i][j] = '.';		
		}
	}

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	
	glutDisplayFunc(mainMenu);	
	// glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Battleship_CPP_ */