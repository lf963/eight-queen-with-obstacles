#include <vector>
#include "utility.h"
using namespace std;

bool DFS(int &nurserySize,vector<string> &nursery,int babyRemain, int x){
	if(x<=nurserySize && babyRemain == 0)
		return true;
	if(x == nurserySize && babyRemain > 0)
		return false;

	vector<vector<int>> emptySubset = emptyCombination(nursery[x],nurserySize);
	int emptySubsetSize = emptySubset.size();

	for(int i=0; i<emptySubsetSize; i++){	//i: situation number. iterative all situation on row x
		if(check(nursery,x,emptySubset[i],nurserySize)){
			int cellSize = emptySubset[i].size();
			for(int col=0; col<cellSize; col++){//put all lizards on row x under situation i
				nursery[x][emptySubset[i][col]] = '1'; 
				for(int row=x+1; row<nurserySize; row++){	//expand power toward down
					if(nursery[row][emptySubset[i][col]] == '2')
						break;
					if(nursery[row][emptySubset[i][col]] == '0')
						nursery[row][emptySubset[i][col]] = '3';
				}

				//expand power toward lower left
				for(int row=x+1, j=emptySubset[i][col]-1; row<nurserySize && j>=0; row++, j--){
					if(nursery[row][j] == '2')
						break;
					if(nursery[row][j] == '0')
						nursery[row][j] = '3';
				}
				//expand power toward lower right
				for(int row=x+1, j=emptySubset[i][col]+1; row<nurserySize && j<nurserySize; row++, j++){
					if(nursery[row][j] == '2')
						break;
					if(nursery[row][j] == '0')
						nursery[row][j] = '3';
				}
			}
			if(DFS(nurserySize, nursery,babyRemain-cellSize,x+1))
				return true;

			for(int col=0; col<cellSize; col++){ //take out all lizards on row x under situation i
				nursery[x][emptySubset[i][col]] = '0';
				for(int row=x+1; row<nurserySize; row++){	//retrieve power toward down
					if(nursery[row][emptySubset[i][col]] == '2')
						break;
					if(nursery[row][emptySubset[i][col]] == '3')
						nursery[row][emptySubset[i][col]] = '0';
				}

				//retrieve power toward lower left
				for(int row=x+1, j=emptySubset[i][col]-1; row<nurserySize && j>=0; row++, j--){
					if(nursery[row][j] == '2')
						break;
					if(nursery[row][j] == '3')
						nursery[row][j] = '0';
				}
				//retrieve power toward lower right
				for(int row=x+1, j=emptySubset[i][col]+1; row<nurserySize && j<nurserySize; row++, j++){
					if(nursery[row][j] == '2')
						break;
					if(nursery[row][j] == '3')
						nursery[row][j] = '0';
				}
			}
		}
	}
	
	return false;
}
