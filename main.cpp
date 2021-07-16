#include <iostream>
#include "sudoku.h"

using namespace std;

int main(){

    int n = 9;


    cout << "Welcome to the Sudoku Solver" << endl << endl;


	string filename = "test_board.txt";
	ifstream ifile;
/*
	while (true){
		cout << "Please enter a txt file name:	";

		cin >> filename;
		ifile.open(filename);
		if (!ifile){
			cout << "File name: " << filename << " does not exist" << endl;
			continue;
		} else break;
	}
	ifile.close();

    cout << endl << "Please enter the number of rows and columns:   ";
    cin >> n;
    */

    Sudoku board(filename,n);
    board.back_starter();





    return 0;
}