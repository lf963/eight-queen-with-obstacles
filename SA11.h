#include <vector>
#include <math.h>
#include <climits>
#include <ctime>
using namespace std;

int getCollision(vector<string> &nursery, int &nurserySize){
	int CollisionNum = 0, treeIndex, ans = 0;	// number of collision

	for(int row=0; row<nurserySize; row++){	// horizontal collision
		treeIndex = nurserySize-1;
		for(int col=0; col<nurserySize; col++){
			if(nursery[row][col] == '2')
				treeIndex = nurserySize-1;
			
			else if(nursery[row][col] == '1'){
				for(int anothercol=col+1; anothercol<=treeIndex; anothercol++){
					if(nursery[row][anothercol] == '2')
						treeIndex = anothercol;
								
					else if(nursery[row][anothercol] == '1')
						CollisionNum++;
								
				}
			}
		}
	}
	//cout << "horizontal = " << CollisionNum << endl;
	for(int col=0; col<nurserySize; col++){	   // vertical collision
		treeIndex = nurserySize-1;
		for(int row=0; row<nurserySize; row++){
			if(nursery[row][col] == '2')
				treeIndex = nurserySize-1;

			else if(nursery[row][col] == '1'){
				for(int anotherrow = row+1; anotherrow<=treeIndex; anotherrow++){
					if(nursery[anotherrow][col] == '2')
						treeIndex = anotherrow;
						
					else if(nursery[anotherrow][col] == '1')
						CollisionNum++;
				}
			}
		}
	}

	//cout << "vertical = " << CollisionNum << endl;
	for(int line=0; line<2*nurserySize-1; line++){	//45 degree, line start from left upper
		int treecol = max(0,line-nurserySize+1);
		int col = min(nurserySize-1,line);
		for(int row = line-col; row<nurserySize && col>=0; row++,col--){
			if(nursery[row][col] == '2')
				treecol = max(0,line-nurserySize+1);
			
			else if(nursery[row][col] == '1'){
				for(int anothercol = col-1, anotherrow = row+1;anothercol>=treecol;anothercol--,anotherrow++){
					if(nursery[anotherrow][anothercol] == '1')
						CollisionNum++;
					
					else if(nursery[anotherrow][anothercol] == '2')
						treecol = anothercol;
				}
			}
		}
	}
	for(int line=0; line<2*nurserySize-1; line++){	//135 degree, line start from right upper
		int col = max(0,nurserySize-1-line);
		int treecol = 2*nurserySize-2-line-col;
		for(int row=line+col-nurserySize+1;row<nurserySize && col<nurserySize;row++,col++){
			if(nursery[row][col] == '2'){
				treecol = min(2*nurserySize-2-line,nurserySize-1);
			}
			else if(nursery[row][col] == '1'){
				for(int anothercol=col+1, anotherrow = row+1; anothercol<=treecol; anothercol++, anotherrow++){
					if(nursery[anotherrow][anothercol] == '1')
						CollisionNum++;
					else if(nursery[anotherrow][anothercol] == '2')
						treecol = anothercol;
				}
			}
		}
	}
	return CollisionNum;
}


pair<int,int> getRandom(char PickOrPut,int &nurserySize,vector<string> &nursery){
	random_device rd;	//non-deterministic seed
    mt19937 mt(rd());	//mt: engine
    std::uniform_int_distribution<int> dist(0,nurserySize-1);//distibution from min to max, inclusive
	pair<int,int> chess(dist(mt),dist(mt));	//run engine
	while(nursery[chess.first][chess.second] != PickOrPut){
		chess.first = dist(mt);
		chess.second = dist(mt);
	}
	return chess;
}


bool initializeNursery(int &nurserySize, vector<string> &nursery, int babySize){
	for(int i=0; i<nurserySize; i++){
		for(int j=0; j<nurserySize; j++){
			
			if(nursery[i][j] == '0' && babySize>0){
				nursery[i][j] = '1';
				babySize--;
				
			}
		}
	}
	return babySize==0?true:false;
}


bool SA(int &nurserySize, vector<string> &nursery, int babySize){
	if(initializeNursery(nurserySize,nursery,babySize)){
		int maxRound = 999999999;
	    int t = 0;
	    double temperature = pow(nurserySize,5);
		double annealingRate = 0.9999;

	    while(t < maxRound){
	    	cout << "--------------------" << endl;
	    	cout << "t = " << t << endl;

	    	t++;
	    	int OriginalCollNum = getCollision(nursery,nurserySize);
	    	cout << "OriginalCollNum = " << OriginalCollNum << endl;
	        if (OriginalCollNum == 0)
	            return true;

	        pair<int,int> pick = getRandom('1',nurserySize,nursery);//pick one random lizard on board
			cout << "pick " << pick.first << " " << pick.second << endl;
			nursery[pick.first][pick.second] = '0';
			pair<int,int> put = getRandom('0',nurserySize,nursery);//put one random lizard on board
			
			cout << "put " << put.first << " " << put.second << endl;
			
			nursery[put.first][put.second] = '1';
			int NewCollNum = getCollision(nursery,nurserySize);
			
			cout << "NewCollNum = " <<  NewCollNum << endl;
			temperature = max(temperature * annealingRate,0.02);	//decrease temperature
			cout << "temperature = " << temperature << endl;
			if(NewCollNum < OriginalCollNum)
				continue;
			else{
				double deltaE = -1*(NewCollNum - OriginalCollNum);
				double acceptProbability = min(exp(deltaE/temperature), 1.0);
				
				random_device rd;
    			mt19937 mt(rd());
    			uniform_real_distribution<double> dist(0.0, 1.0);
				double probability  = dist(mt);
	            cout << "deltaE = " << deltaE << endl;
	            cout << "acceptProbability = " << acceptProbability << endl;
	            cout << "probability = " << probability << endl;
	            if (probability <= acceptProbability)
	                continue;
	            else{
					nursery[pick.first][pick.second] = '1';
					nursery[put.first][put.second] = '0';
	            }
			}
	        
	     }
	}
	
	return false;

}