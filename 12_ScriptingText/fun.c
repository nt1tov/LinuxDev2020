/* COMMENT:: prog, 1.1.7: Mon Dec  7 16:56:10 UTC 2020 */
#include <stdio.h>
#include "outlib.h"

void output(char *str) {
        printf("%d: %s\012", Count++, str);
}

void usage(char *prog) {
    fprintf(stderr, "%s v%.2f: Print all arguments\012\t"\
                "Usage: %s arg1 [arg2 […]]\012", prog, VERSION, prog);
}
