/** @file main.c
 * Numfiner Source Code File
 *
 * It Finds Number using yes/no questions
 */
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

/** Help str */
#define MANUAL _("Numfinder is program for guessing nums\n\
"\n\
"Usage: numfinder [OPTION]\n\
"\n\
    --help      print this help, then end program\n\
"    -r         use roman digits notation\n\
"\n\
"The NumFinder program finds guessed integer [1..100]\n\
"It uses roman and arabic number digit \n\
")

char* roman_numbers[100] = {
  "I",
  "II",
  "III",
  "IV",
  "V",
  "VI",
  "VII",
  "VIII",
  "IX",
  "X",
  "XI",
  "XII",
  "XIII",
  "XIV",
  "XV",
  "XVI",
  "XVII",
  "XVIII",
  "XIX",
  "XX",
  "XXI",
  "XXII",
  "XXIII",
  "XXIV",
  "XXV",
  "XXVI",
  "XXVII",
  "XXVIII",
  "XXIX",
  "XXX",
  "XXXI",
  "XXXII",
  "XXXIII",
  "XXXIV",
  "XXXV",
  "XXXVI",
  "XXXVII",
  "XXXVIII",
  "XXXIX",
  "XL",
  "XLI",
  "XLII",
  "XLIII",
  "XLIV",
  "XLV",
  "XLVI",
  "XLVII",
  "XLVIII",
  "XLIX",
  "L",
  "LI",
  "LII",
  "LIII",
  "LIV",
  "LV",
  "LVI",
  "LVII",
  "LVIII",
  "LIX",
  "LX",
  "LXI",
  "LXII",
  "LXIII",
  "LXIV",
  "LXV",
  "LXVI",
  "LXVII",
  "LXVIII",
  "LXIX",
  "LXX",
  "LXXI",
  "LXXII",
  "LXXIII",
  "LXXIV",
  "LXXV",
  "LXXVI",
  "LXXVII",
  "LXXVIII",
  "LXXIX",
  "LXXX",
  "LXXXI",
  "LXXXII",
  "LXXXIII",
  "LXXXIV",
  "LXXXV",
  "LXXXVI",
  "LXXXVII",
  "LXXXVIII",
  "LXXXIX",
  "XC",
  "XCI",
  "XCII",
  "XCIII",
  "XCIV",
  "XCV",
  "XCVI",
  "XCVII",
  "XCVIII",
  "XCIX",
  "C"
};

/**
 * Change representation of number in arabic digits to roman digits
 * @param num must be between 1 and 100
 * @returns number in roman digits representation char array or null poinTer 
 */
char * arabic2roman(int num) {
  if (num > 0 && num < 100) {
    return roman_numbers[num-1];
  }
  return NULL;
}

/**
 * Change representation of number from roman digits notation to arabic digits notation
 * @param num contains roman number as char array
 * @return arabic number its integer between 1 or 100
 */
int roman2arabic(char *num) {
  for (int i = 0; i < 100; ++i) {
    if (strcmp(num, roman_numbers[i]) == 0) {
      return i+1;
    }
  }
  return -1;
}
int main(int argc, char* argv[]){
	int ROMAN_DIGITS_FLAG = 0;

	setlocale (LC_ALL, "");
    if (getenv("PO_LOCAL")){
		bindtextdomain("numfinder", LOCALE_PATH);
	}
	else{
        bindtextdomain("numfinder", "usr/share/locale");
	}
	textdomain ("numfinder");

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("%s.\n", MANUAL);
		return 0;
	}

	if (argc == 2 && strcmp(argv[1], "-r") == 0) {
		ROMAN_DIGITS_FLAG = 1;
		printf("%s.\n", _("NumFinder can findnumber between I and C"));
	}
	else{
		printf("%s %d %s %d.\n", _("NumFinder can findnumber between"), MIN_NUMBER, _("and"), MAX_NUMBER);
	}

	int lhs = MIN_NUMBER;
	int rhs = MAX_NUMBER;

	char buf[BUFSIZE];

	while(rhs-lhs > 1){
		int founded = (rhs+lhs)/2;
		int need2input = 1;

		while(need2input){
			need2input = 0;
			if (ROMAN_DIGITS_FLAG){
				printf("%s %s?", _("Is number greater than"), arabic2roman(founded));
			}
			else{
				printf("%s %d?", _("Is number greater than"), founded);
			}
			scanf("%10s", buf);
			if(strcmp(_("yes"), buf) == 0){
				lhs = founded;
			}
			else if (strcmp(_("no"), buf) == 0){
				rhs = founded;
			}
			else{
				printf("%s \n", _("Failed to read. Try again."));
				need2input = 1;
			}
		}
	}
	if(ROMAN_DIGITS_FLAG){
		printf("%s: %s\n", _("Number is found! It is"), arabic2roman(rhs));
	}
	else{
		printf("%s: %d\n", _("Number is found! It is"), rhs);
	}
	return 0;
}
