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
        bool check_row(int,int);
        bool check_col(int,int);
        bool check_sector(int,int,int);
        bool is_legal(int,int,int);
        bool is_complete();
        int find_open_row();
        int find_open_col();

        void dancing_starter();
        void dancing_links();
        int cover_matrix_index(int,int,int);
        vector<vector<int> > create_cover_matrix();
        int sector_constraints(vector<vector<int> >,int);
        int box_constraints(vector<vector<int> >,int);
        int col_constraint(vector<vector<int> >,int);
        int row_constraint(vector<vector<int> >,int);
        int cell_constraint(vector<vector<int> >,int);
        vector<vector<int> > convert();

};

class DancingNode{
    private:
        DancingNode* up, *down, *left, *right;
        ColumnNode* column;

    public:
        DancingNode(){ up = down = left = right = this;};
        DancingNode(ColumnNode c) {DancingNode();column = c;};
        DancingNode* linkDown(DancingNode* node);
        DancingNode* linkRight(DancingNode* node);
        void removeLeftRight();
        void reinsertLeftRight();
        void removeTopDown();
        void reinsertTopDown();
        void cover();
        void uncover();

};

class ColumnNode : DancingNode{
    public:
        int size;
        string name;

        ColumnNode(string n);
};