#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "homeworkDFS11.h"
#include "homeworkBFS11.h"
#include "homeworkSA11.h"
using namespace std;

void OutputFile(int &nurserySize, vector<string> &nursery, bool result){
	ofstream myOutput;
  	myOutput.open ("output.txt",ios::trunc);
  	if(result){
  		myOutput << "OK";
		cout << "OK" << endl;
		for(int i=0; i<nurserySize; i++){
			myOutput << endl;
			for(int j=0; j<nurserySize; j++){
				if(nursery[i][j] == '3')
					nursery[i][j] = '0';
				myOutput << nursery[i][j];
				cout << nursery[i][j];
			}
			
			cout << endl;
		}
	}
  	else{
  		myOutput << "FAIL";
		cout << "FAIL" << endl;
  	}
  	myOutput.close();
}

int main(){
	clock_t start, stop;
	string algo,line;
	int nurserySize, babySize;	//nurserySize: height & width of nursery, babySize: number of baby lizard
	vector<string> nursery;	//n*n nursery
	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile,algo);	//first read: algorithm
		if(algo.back() == '\r')	//deal with\r
			algo = algo.substr(0,algo.size()-1);
		
		getline(myfile,line);	//second read: nurserySize
		nurserySize = stoi(line);
		getline(myfile,line);	// third read: number of lizards
		babySize = stoi(line);
		while(getline(myfile,line)){
			nursery.push_back(line);
		}
		myfile.close();
		cout << "Number of lizard: " << babySize << endl;
		for(auto row : nursery)
			cout << row << endl;

		start = clock(); //time start
		if(algo == "DFS"){
			cout << "----------DFS------------" << endl;
			OutputFile(nurserySize,nursery,DFS(nurserySize,nursery,babySize,0));

		}
		else if(algo == "BFS"){
			cout << "----------BFS------------" << endl;
			OutputFile(nurserySize,nursery,BFS(nurserySize,nursery,babySize));
		}
		else if(algo == "SA"){
			cout << "----------SA------------" << endl;
			OutputFile(nurserySize,nursery,SA(nurserySize,nursery,babySize));
		}
		else
			cout << "Wrong input" << endl;
		stop = clock(); //time end
		
	}

	else
		cout << "Unable to open file" << endl;; 
	cout << double(stop - start) / CLOCKS_PER_SEC << " seconds" <<endl;
	
	
	
	return 0;
}

