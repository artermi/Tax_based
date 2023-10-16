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

int parse_last(char* filename){

	FILE *file;
  	file = fopen(filename, "r");

  	int bufferlength = 255;
  	char buffer[bufferlength];

  	while( fgets(buffer,bufferlength,file) ){
  		continue;
  	}
  	char* token;
  	token = strtok(buffer," ");

   	token = strtok(NULL," ");
  	float d = atof(token);
  	token = strtok(NULL," ");
  	float c = atof(token);
  	token = strtok(NULL," ");
  	float pd = atof(token);
  	token = strtok(NULL," ");
  	float pc = atof(token);

  	fclose(file);

  	int index = 0;
  	index += 1 * (d > 0.000001) + 2 * (c > 0.000001) + 4 * (pd > 0.000001) +8 * (pc > 0.0000001);


	return index;
}

bool different_neighbour(double r, double beta,double T,double Gp){
	double r_north = r + 0.2;
	double r_south = r - 0.2;
	double beta_east = beta + 0.1;
	double beta_west = beta - 0.1;

	char file_n[100];
	char n_file[100];
	char s_file[100];
	char e_file[100];
	char w_file[100];

	sprintf(file_n,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r + 0.000001) * 100),
		(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));
	printf("%s\n",file_n);

	int ind_o = parse_last(file_n);

	sprintf(n_file,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r_north + 0.000001) * 100),
		(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));
	int ind_n = parse_last(n_file);

	sprintf(s_file,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r_south + 0.000001) * 100),
		(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));
	int ind_s = parse_last(s_file);

	sprintf(e_file,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r + 0.000001) * 100),
		(int)((beta_east + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));
	int ind_e = parse_last(e_file);

	sprintf(w_file,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r + 0.000001) * 100),
		(int)((beta_west + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));
	int ind_w = parse_last(w_file);


	if(ind_o == ind_n && ind_o == ind_s && ind_o == ind_e && ind_o == ind_w)
		return false;

	return true;


}


int main(int argc, char** argv){
	srand(time(NULL));


	for(double r = 3.2; r < 4.81; r += 0.2 ){
		for(double beta = 0.1; beta < .91; beta += 0.1){
			for (double T = 0; T < 1.01; T += 0.1){
				for(double Gp = 0; Gp < 1.01; Gp += 0.1){
					different_neighbour(r,beta,T,Gp);
				}
			}

		}
	}


	return 0;
}
