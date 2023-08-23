#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>


#define K 1.2
#define L 1000
#define LL (L*L)

class Tax_PGG{
public:
	double c;
	double r;
	double beta;
	double T;
	double Gp;

	bool grid;
	char dir_name[100];

	int Cate_Player[4];
	
	int *Strategy;
	int **Neighbour;

	Tax_PGG(const double R, const double B,
	const double tax, const double gp, bool Two = false, bool Grid = false);
	~Tax_PGG();
	//double unit_game(const int cent,const int target);
	double one_game(const int cent,const int target);
	double centre_game(const int cent);
	int game(bool ptf);
};
