#include "sudoku.h"

using namespace std;

Sudoku::Sudoku(string fileName, int n){

    ifstream ifile;
    ifile.open(fileName);
    if (!ifile){
        cout << "File name: " << fileName << " does not exist" << endl;
    exit(1);
    }

    this->n = n;

    for(int i = 0; i < n; i++){
        Board.push_back(vector<int>());
        for (int j = 0; j < n; j++){
            int t = 0;
            ifile >> t;
            Board[i].push_back(t);
        }
    }

    cout << "Starting Board:" << endl;
    print_board(Board);

}

void Sudoku::print_board(vector<vector<int> > b){
    for (int i = 0; i < n; i++){
        if (i % 3 == 0 && i != 0)
            cout << "---------------------" << endl;
        for (int j = 0; j < n; j++){
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::reset_board(){
    ifstream ifile;
    ifile.open(fileName);
    Board.empty();

    for(int i = 0; i < n; i++){
        Board.push_back(vector<int>());
        for (int j = 0; j < n; j++){
            int t = 0;
            ifile >> t;
            Board[i].push_back(t);
        }
    }

    cout << "Starting Board:" << endl;
    print_board(Board);
}

//checks if the number num exists in row r
bool Sudoku::check_row(int num, int r){

    for (int i = 0; i < n; i++){
        if (Board[r][i] == num)
            return false;
    }
    return true;
}

bool Sudoku::check_col(int num, int c){
    for (int i = 0; i < n; i++){
        if(Board[i][c] == num)
            return false;
    }
    return true;
}

bool Sudoku::check_sector(int num, int r, int c){

    int start_row, start_col, root_n;
    root_n = sqrt(n);
    start_row = r - r % root_n;
    start_col = c -c % root_n;
    

    for (int i = 0; i < root_n; i++){
        for (int j = 0; j< root_n; j++){
            if (Board[start_row + i][start_col + j] == num)
                return false;
        }
    }
    return true;
}


bool Sudoku::is_legal(int num, int r, int c){
    return check_row(num,r) && check_col(num,c) && check_sector(num,r,c);
}

bool Sudoku::is_complete(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (Board[i][j] == 0)
                return false;
        }
    }
    return true;
}

int Sudoku::find_open_row(){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (Board[i][j] == 0)
                return i;
        }
    }
    return -1;
}

int Sudoku::find_open_col(){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (Board[i][j] == 0)
                return j;
        }
    }
    return -1;
}


void Sudoku::back_starter(){
    back_tracking();

    cout << "Back tracking solution:" << endl;
    print_board(Board);
}


bool Sudoku::back_tracking(){


  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (Board[row][col] == 0) {
        for (int number = 1; number <= n; number++) {
          if (is_legal(row, col, number)) {
            Board[row][col] = number;
          
            if (back_tracking()) {
              return true;
            } else {
              Board[row][col] = 0;
            }
          }
        }
		
        return false;
      }
    }
  }
  
  return true;

/*
    if (is_complete())
        return true;

    int row = find_open_row();
    int col = find_open_col();

    //cout << row << " " << col << endl;


    for (int num = 1; num <= n; num++){

            //cout << "seg fault" << endl;
        if (is_legal(num,row,col)){
            Board[row][col] = num;

        }

        if (Board[row][col] == 0)
            continue;

        if (back_tracking())
            return true;

        Board[row][col] = 0;
    }

    //print_board(Board);

    return false;

    */

}
