#include "Tax_PGG.h"
#include <unistd.h>
using namespace std;

int do_once(double r, double beta, double T, double Gp){
	printf("Now doing Tax_PGG with (r,beta,T,Gp) = (%f,%f,%f,%f)\n",
		r,beta,T,Gp);
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
		return 0;
	}

	file = fopen(file_n, "w");
	fclose(file);

	Tax_PGG gameOBJ(r,beta,T,Gp);
	gameOBJ.game(true);

	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));

	double beta = 0.1;
	double T = 0.4;
	double Gp = 0.8;


	for(double r = 3; r < 5.01; r += 0.02 ){
		do_once(r,beta,T,Gp);

	}


	return 0;
}
