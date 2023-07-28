#include "Tax_PGG.h"
using namespace std;

Tax_PGG::Tax_PGG(const double R, const double B,
	const double tax, const double gp, bool Two , bool Grid ){

	// c, r, beta, T, Gp
	c = 1;
	r = R;
	beta = B;
	T = tax;
	Gp = gp;

	grid = Grid;

	Strategy = new int[LL];

	// 0 for D, 1 for C, 2 for PD, 3 for PC
	for(int i = 0; i < 4; i++)
		Cate_Player[i] = 0;

	if(Two){
		for(int i = 0; i < LL; i++){
			Strategy[i] = rand() % 2;

			Cate_Player[Strategy[i]] ++;
		}		
	}
	else{
		for(int i = 0; i < LL; i++){
			Strategy[i] = rand() % 4;

			Cate_Player[Strategy[i]] ++;
		}
	}


	Neighbour = new int *[LL];
	for(int i = 0; i < LL; i++)
		Neighbour[i] = new int[4];

	for(int i = 0; i < LL; i++){
		Neighbour[i][0] = (i - L + LL ) % LL; //North
		Neighbour[i][1] = (i + L) % LL;
		Neighbour[i][2] = (i + 1) % LL;
		Neighbour[i][3] = (i - 1 + LL) % LL;
	}//initialise the neighbour



}

Tax_PGG::~Tax_PGG(){
	delete Strategy;
	for(int i = 0; i < LL; i++){
		delete [] Neighbour[i];
	}
	delete [] Neighbour;
}


double Tax_PGG::one_game(const int cent,const int target){
	// N0 for D, N1 for C, N2 for PD, N3 for PC
	double Nl[4] = {0.0, 0.0, 0.0,0.0};
	// c, r, beta, T, Gp

	Nl[Strategy[cent]] += 1.0;

	for(int i = 0; i < 4; i++){
		Nl[Strategy[Neighbour[cent][i]]] += 1.0;
	}

	if (Strategy[target] == 0){ // D
		return ( r * (Nl[3] + Nl[1])/5 - beta * (Nl[3] + Nl[2]) -T);
	}
	if (Strategy[target] == 1){ // C
		return ( r  * (Nl[3] + Nl[1])/5 - 1 -T);
	}
	if (Strategy[target] == 2){ // PD
		return ( r * (Nl[3] + Nl[1])/5 + (5 * T)/(Nl[3] + Nl[2]) - Gp -T - beta * (Nl[3] + Nl[2]) );
	}	

	if (Strategy[target] == 3){ // PC
		return ( r * (Nl[3] + Nl[1])/5 - 1 + (5 * T)/(Nl[3] + Nl[2]) - Gp -T);
	}

	return 0;
}

double Tax_PGG::centre_game(const int cent){
	double profit = one_game(cent,cent);
	for(int i = 0; i <4; i++){
		profit += one_game(Neighbour[cent][i],cent);
	}
	return profit;
}


int Tax_PGG::game(bool ptf){

	FILE *file;
	if(ptf){
		char path[100];
		
		sprintf(path,"r_%04d_b_%04d_T_%04d_G_%04d.dat", 
		(int)((r + 0.000001) * 100),
		(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
		(int)((Gp + 0.000001) * 100));

		printf("Now file:%s\n",path);
		file = fopen(path,"a+");
	}

	double rate[4] = {0.0, 0.0, 0.0,0.0};
	double previous[5][4];
	int iter = 20001;
	int gap = 100;
	bool stop_all_0 = true;

	for(int i = 0; i < iter; i++){
		bool stop_all = true;

 
		if(i % gap == 0){
			for (int j = 0; j < 4; ++j)
				rate[j] = (double) Cate_Player[j] / LL;

			if(ptf)
				fprintf(file, "%06d %.4f %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2],rate[3]);
			printf( "%06d %.4f %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2],rate[3]);

			double pert = 0.02;
			for(int j = 1; j < 5; j++)
				for(int k = 0; k < 3; k ++)
					previous[j-1][k] = previous[j][k];
			for(int k = 0; k < 3; k++)
				previous[4][k] = rate[k];

			if(i > iter/2){
				stop_all_0 = true;

				for(int j = 0; j < 5; j++)
					for(int k = 0; k < 4; k ++)
						if(abs(rate[k] - previous[j][k]) > pert){
							stop_all_0 = false;
						}
			}
			else{
				stop_all_0 = false;
			}
		}

		for (int j = 0; j < 4; j++)
			if(rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
				stop_all = false;

		if(stop_all || stop_all_0)
			continue;

		if(grid && i % gap == 0){
			char path2[100];
			sprintf(path2,"r_%04d_b_%04d_T_%04d_G_%04d_i_%05d.dat", 
					(int)((r + 0.000001) * 100),
					(int)((beta + 0.000001) * 100), (int)((T + 0.000001) * 100),
					(int)((Gp + 0.000001) * 100),
					i);

			FILE *gfile = fopen(path2,"a+");	
			for(int j = 0; j < LL;j++)
				fprintf(gfile, "%d", Strategy[j]);

		}

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;

			int y = Neighbour[x][rand() % 4];
			if (Strategy[x] == Strategy[y])
				continue;

			double x_earn = centre_game(x);
			double y_earn = centre_game(y);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp((y_earn - x_earn)/K) ) ){
				Cate_Player[ Strategy[y] ] --;
				Strategy[y] = Strategy[x];
				Cate_Player[ Strategy[y] ] ++;
			}

		}
	}
	if(ptf)
		fclose(file);

	return 0;
}

