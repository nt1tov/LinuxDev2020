/* COMMENT:: prog, 1.1.7: Mon Dec  7 16:56:10 UTC 2020 */
#include <stdio.h>
#include "outlib.h"
int main(int argc, char *argv[]) {
  int i;
        if((Count = argc)>1) {
                output("<INIT>");
             for(i=1; i<argc; i++)
                 output(argv[i]);
              output("<DONE>");
     }
     else
          usage(argv[0]);
       return 0;
}
