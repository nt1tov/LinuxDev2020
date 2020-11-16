#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define MIN_NUMBER 0
#define MAX_NUMBER 100

#define BUFSIZE 20


int main(int argc, char** argv){

	setlocale (LC_ALL, "");
    if (getenv("PO_LOCAL")){
		bindtextdomain("numfinder", LOCALE_PATH);
	}
	else{
        bindtextdomain("numfinder", "usr/share/locale");
	}
	textdomain ("numfinder");

	printf(_("NumFinder can findnumber between %d and %d"), MIN_NUMBER, MAX_NUMBER);
	int lhs = MIN_NUMBER;
	int rhs = MAX_NUMBER;

	char buf[BUFSIZE];

	while(rhs-lhs > 1){
		int guessed = (rhs+lhs)/2;
		int need2input = 1;

		while(need2input){
			need2input = 0;
			printf(_("Is  number greater than %d?"), guessed);
			scanf("%10s", buf);
			if(strcmp("yes", buf) == 0){
				lhs = guessed;
			}
			else if (strcmp("no", buf) == 0){
				rhs = guessed;
			}
			else{
				need2input = 1;
			}
		}
	}
	printf(_("Number is found! Number is: %d"), rhs);
	return 0;
}
