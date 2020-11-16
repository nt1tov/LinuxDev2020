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

	printf("%s %d %s %d.\n", _("NumFinder can findnumber between"), MIN_NUMBER, _("and") MAX_NUMBER);
	int lhs = MIN_NUMBER;
	int rhs = MAX_NUMBER;

	char buf[BUFSIZE];

	while(rhs-lhs > 1){
		int founded = (rhs+lhs)/2;
		int need2input = 1;

		while(need2input){
			need2input = 0;
			printf("%s %d?", _("Is number greater than"), founded);
			scanf("%10s", buf);
			if(strcmp(_("yes"), buf) == 0){
				lhs = founded;
			}
			else if (strcmp(_("no"), buf) == 0){
				rhs = founded;
			}
			else{
				printf(_("Failed to read. Try again.\n"));
				need2input = 1;
			}
		}
	}
	printf("%s: %d\n", _("Number is found! It is"), rhs);
	return 0;
}
