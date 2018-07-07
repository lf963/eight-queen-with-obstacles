#include <vector>
#include <queue>
using namespace std;
struct boardState{
	vector<string> board;
	int babyRemain, currentRow;
	boardState(vector<string> b, int n, int r): board(b), babyRemain(n), currentRow(r){} 
};

bool BFS(int &nurserySize, vector<string> &nursery, int babySize){
	queue<boardState> myQueue;
	boardState boardNode(nursery,babySize,-1);
	myQueue.push(boardNode);
	
	while(!myQueue.empty()){
		boardState firstNode = myQueue.front();
		int row = firstNode.currentRow;
		if(firstNode.babyRemain == 0){
			nursery = firstNode.board;
			return true;
		}
		else if(row < nurserySize-1 && firstNode.babyRemain > 0){	// not reach bottome of tree
			vector<vector<int>> emptySubset = emptyCombination(firstNode.board[row+1],nurserySize);
			int emptySubsetSize = emptySubset.size();
			for(int i=0; i<emptySubsetSize; i++){//i: situation number. iterative all situation on row
				if(check(firstNode.board,row+1,emptySubset[i],nurserySize)){
					int cellSize = emptySubset[i].size();
					boardState boardNode(firstNode.board,firstNode.babyRemain-cellSize,row+1);
					for(int col=0; col<cellSize; col++){//put all lizards on row x under situation i
						boardNode.board[row+1][emptySubset[i][col]] = '1'; 
						for(int r=row+2; r<nurserySize; r++){	//expand power toward down
							if(boardNode.board[r][emptySubset[i][col]] == '2')
								break;
							if(boardNode.board[r][emptySubset[i][col]] == '0')
								boardNode.board[r][emptySubset[i][col]] = '3';
						}

						//expand power toward lower left
						for(int r=row+2, j=emptySubset[i][col]-1; r<nurserySize && j>=0; r++, j--){
							if(boardNode.board[r][j] == '2')
								break;
							if(boardNode.board[r][j] == '0')
								boardNode.board[r][j] = '3';
						}
						//expand power toward lower right
						for(int r=row+2, j=emptySubset[i][col]+1; r<nurserySize && j<nurserySize; r++, j++){
							if(boardNode.board[r][j] == '2')
								break;
							if(boardNode.board[r][j] == '0')
								boardNode.board[r][j] = '3';
						}
					}

					//check reach goal or not before push into queue
					if(boardNode.babyRemain == 0){
						nursery = boardNode.board;
						return true;
					}
					myQueue.push(boardNode);
				}
			}
		}
		//else	reach bottom of tree but baby still remains: do nothing
		
		myQueue.pop();
	}
	return false;
}