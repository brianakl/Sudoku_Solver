#pragma SUDOKU_H

#define UNASSIGNED 0

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

//creates a n x n sudoku board numbered 1-n
//0 represents a blank
class Sudoku{

    private:
        int n;
        string fileName;
        vector<vector<int> > Board;

    public:
        Sudoku(string,int n = 9);
        void reset_board();
        void print_board(vector<vector<int> >);
        void back_starter();
        bool back_tracking();
        void dancing_starter();
        void dancing_links();
        bool check_row(int,int);
        bool check_col(int,int);
        bool check_sector(int,int,int);
        bool is_legal(int,int,int);
        bool is_complete();
        int find_open_row();
        int find_open_col();

        int cover_matrix_index(int,int,int);
        int create_cover_matrix();
        int sector_constraints(int (&array)[],int);
        int col_constraint(int (&array)[],int);
        int row_constraint(int (&array)[],int);
        int cell_constraint(int (&array)[],int);
        int convert(int (&array)[],int);

};