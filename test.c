#include<stdio.h>

int main(int argc, char *argv[]){
	fputs("\033[5;10H",stdout);
	fputs("\033[5;10HHello\n",stdout);

	return 0;
}
