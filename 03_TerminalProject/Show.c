#include "stdio.h"
#include "ncurses.h"
#include "stdlib.h"
#include "string.h"

#define DX 3

int main(int argc, const char **argv){
	WINDOW *win;
	
 	if (argc != 2){
		printf("Error: expected 2 parameters but %d were given", argc);
		exit(0);
	}

	FILE *fd;	
	fd = fopen(argv[1], "r");
	
	if (!fd){	
		printf("Error: filename  %s cannot be opened", argv[1]);
		exit(0);
	}

	initscr();

	int width = LINES - 2*DX;
	int height = COLS - 2*DX;

	win = newwin(width, height, DX, DX);
	printw("Filename: %s", argv[1]);
	
	refresh();
	scrollok (win, TRUE);
	
	keypad(win, TRUE);
	
	int line_len = height  - 2*DX;
	char **screen_buffer = (char **) malloc(width * sizeof(char *)); 
	printf("ok!");
	char *text_line = (char *) malloc(line_len * sizeof(char));
	for (int i = 0; i < width; ++i){
		fgets(text_line, line_len, fd);
		screen_buffer[i] = (char *) malloc(line_len * sizeof(char));
		strcpy(screen_buffer[i], text_line);
		wprintw(win, "%s", screen_buffer[i]) ;
	}
	box(win, 0, 0);
	wrefresh(win);
	char c;
		
	while((c = wgetch(win)) != 27){
		box(win, 0, 0);
		wrefresh(win);
		if (c == ' '){
			if (feof(fd)){
				wprintw(win, "\n");
			}
			else{
				fgets(text_line, line_len, fd);
				wprintw(win, "%s", text_line);
			}

		}
		
	}
	endwin();	
	free(text_line);
	fclose(fd);
	return 0;
}


