/** Seehwan yoo

	Copy right is with seehwan.yoo@dankook.ac.kr

	Do not modify this comment. The source code comes with AS-IS.
	I allow re-distribution of this source code only under the education purpose.
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "list.h"

// simple line editor

/*  when it begins, starts with command mode
	1. At command mode, we can move cursor, save file or exit program.
	initial cursor position is 1,1
		1) key input for moving cursor
			'h' : left 
			'j' : down 
			'k' : up 
			'l' : right
		2) key input for changing mode : 'i'
		3) key input for saving file : 'w'
		4) key input for exiting program : 'q'

	2. At Input_mode, we can write any character.
		1) key input for delete : Tab 
		2) change mode to command mode : escape key
  
*/

enum MODES {
	COMMAND_MODE,
	INPUT_MODE
};

extern const int max_line;
extern const int max_col;

int main(int argc, char * argv[])
{
	char buff[255];
	enum MODES mode = COMMAND_MODE;

	int cur_line = 1;
	int cur_col = 1;
	const int min_line = 1;
	const int min_col = 1;
	int ret;
	int s_num;
	char key;
	int loop = 1;
	LIST* line_data = createList();
	InsertLine(line_data,0);
	ListNode* Templine;
//	int select;
	char* message[4] = {"--INSERT--   ","--COMMAND--   ","----EXIT?   ","---SAVE---     "};

	int m_num = 1;
	FILE* fp = fopen("TEST.txt","r+");

	if(fp == NULL){
		fp = fopen("TEST.txt","w");
		s_num = 0;
//		printf("ERROR OPEN FILE");
//		exit(100);
	}
	else
		s_num = 1;

	/* some initialization */
	fputs("\033[2J", stdout);
	fputs("\033[26;70H  1:  1",stdout);
	fputs("\033[26;1H--COMMAND--",stdout);
	fputs("\033[1;1H", stdout);

	if(s_num ==1)
		open_list(line_data,fp);

	fputs("\033[1;1H", stdout);

	struct termios oldt, curt, newt;

	tcgetattr ( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  

	/* now, we get input */
	while (loop) {

	key = getchar();
	ret = feof(stdin);
	if (ret != 0) {
		printf ("EOF\n");
		return 0;
	}
	ret = ferror(stdin);
	if (ret != 0) {
		printf ("ERROR getchar() by %d\n", ret);
		return 0;
	}

	if (mode == COMMAND_MODE) {
	switch (key) {
	case 'i':
	case 'I':
		mode = INPUT_MODE;
		m_num = 0;
		tcgetattr ( STDIN_FILENO, &curt );
		newt = curt;
		newt.c_lflag |= ( ECHO );
		tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
		break;
	/* make movement with the following keys */
	case 'h':
	case 'H':
		m_num = 1;
		cur_col--;
		if (cur_col < min_col){ 
			if(cur_line == min_line)cur_col = min_col;
			else{
				cur_col = max_col;
				cur_line--;
			}
		}
		break;
	case 'j':
	case 'J':
		m_num = 1;
			Templine = SearchLine(line_data,cur_line);
		if (Templine->next ==NULL)
			InsertLine(line_data,cur_line);
		cur_line++;
		if (cur_line > max_line) cur_line = max_line;
		break;
	case 'k':
	case 'K':
		m_num = 1;
		cur_line--;
		if (cur_line < min_line) cur_line = min_line;
		break;
	case 'l':
	case 'L':
		m_num = 1;
		cur_col++;
		if (cur_col > max_col) {
			cur_col = 1;
			cur_line++;
			if (cur_line > max_line) cur_line = max_line;
		}
		break;
	case 'q':
	case 'Q':
		m_num = 2;
		sprintf(buff,"\033[%d;%dH%s",26,1,message[m_num]);
		fputs(buff,stdout);
		sprintf(buff,"\033[%d;%dH%3d:%3d",26,70,cur_line,cur_col);
		fputs(buff,stdout);
		fputs("\033[26;12H",stdout);
		key = getchar();
		switch(key)
			case 'Y':
			case 'y':
				loop = 0;
				break;
			default :
				loop = 1;
				m_num = 1;
				break;
	case 'w':
	case 'W':
		m_num = 3;
		save_list(line_data,fp);
		break;
	case 'd':
	case 'D':
		printf("\033[26;1H:Delete Line?:");
		key = getchar();
		switch(key){
			case 'Y':
			case 'y':
				DeleteLine(line_data,cur_line);
				printf("\033[2J");
				printf("\033[1;1H");
				print_Data(line_data,1,0);
			break;
		}
	}	// end switch

	// end COMMAND_MODE
	} else if (mode == INPUT_MODE) {
	switch (key) {
	case 27: // escape key code
		mode = COMMAND_MODE;
		m_num = 1;
		tcgetattr ( STDIN_FILENO, &curt );
		newt = curt;
		newt.c_lflag &= ~( ECHO | ECHOE);
		newt.c_lflag &= ~(ECHOCTL);
		tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
		break;
//	case 9://tab key = backspace
//		mode = INPUT_MODE;
//		DeleteData(line_data,cur_line,cur_col);
//		print_Data(line_data,cur_line,cur_col);
//		cur_col--;		
//		if(cur_col < min_col){
//			if(cur_line<min_line)
//				cur_col = min_col;
//			else{
//			cur_col = max_col;
//			cur_line--;
//			}
//		}
//		break;
	case 10://enter
		mode = INPUT_MODE;
//		EnterLine(line_data,cur_line,cur_col);
		Templine = SearchLine(line_data,cur_line);
		if(Templine->next == NULL)
			InsertLine(line_data,cur_line);
		cur_line++;
		cur_col = min_col;
		if(cur_line > max_line)	cur_line = max_line;
		break;
	case 32:
		key = 94;
	default:
		mode = INPUT_MODE;
		//save data;
		InsertData(line_data,cur_line,cur_col-1,key);
		print_Data(line_data,cur_line,cur_col);
		//calibrate cursor
		cur_col++;
		if (cur_col > max_col) {
			cur_col = 1;
			cur_line++;
			if (cur_line > max_line) cur_line = max_line;
		}
		break;
	}	// end switch
	// end INPUT_MODE
	}
	sprintf(buff,"\033[%d;%dH%s",max_line+1,1,message[m_num]);
	fputs(buff,stdout);
	sprintf(buff, "\033[%d;%dH%3d:%3d", max_line+1, 70, cur_line, cur_col);
	fputs(buff, stdout);
//	if(key == 9){
//		sprintf(buff, "\033[%d;%dH \b", cur_line, cur_col);//cur_col
//		fputs(buff, stdout);
//	}
//	else if(key==10){
//		sprintf(buff, "\033[%d;%dH%d",cur_line,cur_col,cur_line);
//		fputs(buff,stdout);
//	}
//	else{
//		sprintf(buff,"\033[%d;1H%2d", cur_line, cur_line);
//		fputs(buff, stdout);
		sprintf(buff,"\033[%d;%dH", cur_line, cur_col);
		fputs(buff, stdout);
//	}
//	KEY_view(line_data);
	}	// end while
 
	if(fclose(fp) == EOF){
		printf("ERROR closing file.\n");
		exit(101);
	}

	/* return termio back */ 
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

	return 0;
}
