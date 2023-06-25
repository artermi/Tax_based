#include "Tax_PGG.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double r=1;
	double beta=1;
	double T=1;
	double Gp=1;

	
	printf("Now doing Tax_PGG with (c,r,beta,T,Gp) = (%f,%f,%f,%f,%f)\n",
		c,r,beta,T,Gp);

	for(double b = 1; b < 2.01; b += 0.05 ){
		char file_n[100];
		sprintf(file_n,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r + 0.000001) * 100),
		(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));

		FILE *file;
  		file = fopen(file_n, "r");

		if (file) {
			fclose(file);
			printf("file:'%s' exists\n",file_n);
			usleep(100000);
			continue;
		}

		file = fopen(file_n, "w");
		fclose(file);

		Tax_PGG gameOBJ(r,beta,T,Gp);
		gameOBJ.game(false);

	}


	return 0;
}
