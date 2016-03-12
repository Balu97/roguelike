#include <curses.h>
#include <string.h>
#include "buildnumber.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

//The entity structure defines entitys that are places in the world.
struct entity
{
	int x;
	int y;
};

//The tile structure defines a tile and its properties
struct tile
{
	//If creatures can walk on on a tile goable is to be set to a value not 0.
	char goable;
	char representation; //the char that represents the tile
	int color;
};

//The world structure defines a world in the game with all its properties.
struct world
{
	struct entity player;
	char area[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; //There is currently only one area in the Game.
	struct tile tiles[256]; //All the tiles in the World
};


//This function prepares a world structur for the player.
void generateWorld(struct world *inworld)
{
	//setting the start values for the player
	inworld->player.x = 10;
	inworld->player.y = 10;

	//assigning an area to the world
	char tmp[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"},
		{";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"}
	};

	int i = 0;
	for(i = 0; i < SCREEN_HEIGHT; i++){
		strcpy(inworld->area[i], tmp[i]);
	}

	//Defining all the values for the tiles
	inworld->tiles[';'].goable = 1;
	inworld->tiles[';'].color = 1;
	inworld->tiles[';'].representation = ';';
}

//This funcion prints a tile according to its properties defined in tilesof inworld.
void print_tile(int y, int x, char tile, struct world *inworld)
{
	attron(COLOR_PAIR(inworld->tiles[tile].color));
	mvaddch(y, x, inworld->tiles[tile].representation);
	attroff(COLOR_PAIR(inworld->tiles[tile].color));
}

//The render function is called every game turn
void render(struct world *inworld)
{
	int y;
	int x;
	for(y = 0; y < SCREEN_HEIGHT; y++){
		for(x = 0; x < SCREEN_WIDTH; x++){
			print_tile(y, x, inworld->area[y][x], inworld);
		}
	}
	mvprintw(inworld->player.y, inworld->player.x, "@");
	mvprintw(0, 0, "Build Nr. "BUILD_NUMBER);
	refresh();
}

//Moves the player in a crtain direction
void go_direction(struct world *inworld, int distanceX, int distanceY)
{
	int x = inworld->player.x + distanceX;
	int y = inworld->player.y + distanceY;
	if(inworld->tiles[inworld->area[y][x]].goable){
		inworld->player.x = x;
		inworld->player.y = y;
	}
}

//Updates inworld based on the given input
void update(struct world *inworld, char input)
{
	switch(input){
		case 'w':	go_direction(inworld, 0, -1);
				break;

		case 's':	go_direction(inworld, 0, 1);
				break;

		case 'a':	go_direction(inworld, -1, 0);
				break;

		case 'd':	go_direction(inworld, 1, 0);
				break;
	}
}

int main()
{
	//start of curses initialization
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	//end of curses initialization
	struct world mainWorld;

	generateWorld(&mainWorld);

	char input = '.';

	render(&mainWorld);

	//mainloop
	while(input != 'e'){
		input = getch();
		update(&mainWorld, input);
		render(&mainWorld);
	}

	//cleanup
	endwin();

	return 0;
}
