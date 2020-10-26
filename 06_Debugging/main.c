#include <stdlib.h>



int main(){

	int *ptr = malloc(20);
	free(ptr);
	free(ptr);
	return 0;
}
