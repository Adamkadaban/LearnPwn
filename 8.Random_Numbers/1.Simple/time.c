#include <stdlib.h>
#include <time.h> 
#include <stdio.h>


int main(){
	time_t seconds;

	seconds = time(NULL);
	srand(seconds);

	int randomValue;
	for(int i = 0; i < 30; i++){
		randomValue = rand();
		randomValue = randomValue & 0xf;

		printf("%d\n",randomValue);
	}
}
