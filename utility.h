#include <vector>
using namespace std;

vector<vector<int>> emptyCombination(string rowX, int &nurserySize){
	//find the combination of empty cell on row x
	vector<vector<int>> combination(1);	//put all combination here
	int combSize = combination.size();
	for(int i=0; i<nurserySize; i++){
		if(rowX[i] == '2'){
			combSize = combination.size();
			continue;
		}
		if(rowX[i] == '3')
			continue;
		for(int j=0; j<combSize; j++){
			combination.push_back(combination[j]);
			combination.back().push_back(i);
		}
	}
	return combination;
}

bool check(vector<string> &nursery, int x, vector<int> &emptyCell, int &nurserySize){
	int emptyCellSize = emptyCell.size();
	for(int y=0; y<emptyCellSize; y++){
		for(int i=x-1; i>=0; i--){	//check all rows on column y
			if(nursery[i][emptyCell[y]] == '2')
				break;
			if(nursery[i][emptyCell[y]] == '1')
				return false;
		}
		
		for(int i=x-1, j=emptyCell[y]-1 ; i>=0 && j>=0; i--, j--){  //check diagonal toward upper left
			if(nursery[i][j] == '2')
				break;
			if(nursery[i][j] == '1')
				return false;
	    }  
		for(int i=x-1, j=emptyCell[y]+1 ; i>=0 && j<nurserySize; i--, j++){   //check diagonal toward upper right
			if(nursery[i][j] == '2')
				break;
			if(nursery[i][j] == '1')
				return false;
		}
	}
	return true;
}