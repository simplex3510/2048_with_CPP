#include <iostream>
#include <fstream>
#include "BestScoreManager.hpp"

using namespace std;


void BestScore(int newBest) {
	ifstream fin("bestScore.txt");
	int cuBest = 0;
	if (fin.fail()) {
		cuBest = 0;
		fin >> cuBest;
	}
	fin >> cuBest;
	fin.close();
	ofstream fout("bestScore.txt");

	cout << "cuBest : " << cuBest << endl;
	cout << "newBest : " << newBest << endl;
	if (newBest >= cuBest) {
		fout << newBest << endl;
		cout << "BEST : " << newBest << endl;
	}
	else {
		fout << cuBest << endl;
		cout << "BEST : " << cuBest << endl;
	}
}

int BestSc() {
	ifstream fin("bestScore.txt");
	int cuBest = 0;
	if (fin.fail()) {
		cuBest = 0;
		fin >> cuBest;
	}
	fin >> cuBest;
	fin.close();
	cout << "현재 최고점수" << cuBest << endl;
	return cuBest;
}