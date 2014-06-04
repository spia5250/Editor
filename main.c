/*	Seehwan yoo

	Copy right is with seehwan.yoo@dangook.ac.kr
	Do not modify this comment. The source code comes with AS-IS.
	I allow re-distribution of this source code only under the education pur pose.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"

/*
	Basic Editor

	When it begins, starts with command mode
	At command mode, we can move cursor or save and terminate  program.
	initial cursor position is 1,1
	cursor moves left, up, down, right by 'h','j','k','l'
	save file by 'w'
	terminate by 'q'
	if we enter the 'i', we can change mode to input mode.

	At input mode, we can write any letter.
	if we enter the escape key, we can change mode to command mode.

*/

enum MODES {COMMAND_MODE,INPUT_MODE};

int main(int argc, char * argv[]){

	char buff[255];
	enum MODES mode = COMMAND_MODE;
	int cur_line = 1;
	int cur_col = 1;
	const int min_line = 1;
	const int min_col = 1;
	const int max_line = 20;
	const int max_col = 80;
	int key, ret;
//	char data[20][80];
	LIST data = createList();

    /* some initialization */
	fputs("\033[2J", stdout);
	fputs("\033[1;1H", stdout);
	


return 0;
}
