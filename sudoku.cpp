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

    int root_n = sqrt(n);
    int start_row = r - r % root_n;
    int start_col = c - c % root_n;

    //cout << start_row << " " << start_col << endl;
    

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
    if(back_tracking()){
        cout << "Back tracking solution:" << endl;
        print_board(Board);
    } else {
        cout << "No solution" << endl;
    }

}


bool Sudoku::back_tracking(){

    if (is_complete())
        return true;

    int row = find_open_row();
    int col = find_open_col();


    for (int num = 1; num <= n; num++){

        if (is_legal(num,row,col)){
            Board[row][col] = num;
        }

        if (Board[row][col] == 0)
            continue;

        if (back_tracking())
            return true;

        Board[row][col] = 0;
    }


    return false;


}

/*
dancing links is an algorithm where the possible choices for each square are linked lists
for that constraint
*/
void Sudoku::dancing_starter(){

}


void Sudoku::dancing_links(){

}

int Sudoku::cover_matrix_index(int num, int row, int col){
    return (row-1) * n * n + (col - 1) * n + (num - 1);
}

vector<vector<int> > Sudoku::create_cover_matrix(){
    int size = n * n;
    
    vector<vector<int> > matrix(n*n*n, vector<int>(n*n*4));
    int h = 0;
    h = cell_constraint(matrix,h);
    h = row_constraint(matrix,h);
    h = col_constraint(matrix,h);
    box_constraints(matrix,h);

    return matrix;
}

int Sudoku::box_constraints(vector<vector<int> > matrix, int h){
    int box_size = sqrt(n);
    for (int r = 1; r <= n; r += box_size){
        for (int c = 1; c <= n; c += box_size){
            for (int num = 1; num <= n; n++, h++){
                for (int rowdelta = 0; rowdelta < box_size; rowdelta++){
                    for (int coldelta = 0; coldelta < box_size; coldelta++){
                        int index = cover_matrix_index(num, r + rowdelta, c + coldelta);
                        matrix[index][h] = 1;
                    }
                }
            }
        }
    }
    return h;
}


int Sudoku::row_constraint(vector<vector<int> > matrix,int h){

    for (int row = 1; row <= n; row++) {
      for (int num = 1; num <= n; num++, h++) {
        for (int column = 1; column <= n; column++) {
          int index = cover_matrix_index(row, column, n);
            matrix[index][h] = 1;
        }
      }
    }
	
    return h;
}

int Sudoku::col_constraint(vector<vector<int> > matrix, int h){

    for (int column = 1; column <= n; column++) {
      for (int num = 1; num <= n; num++, h++) {
        for (int row = 1; row <= n; row++) {
          int index = cover_matrix_index(row, column, n);
          matrix[index][h] = 1;
        }
      }
    }
	
    return h;
}

int Sudoku::cell_constraint(vector<vector<int> > matrix, int h){

    for (int row = 1; row <= n; row++) {
      for (int column = 1; column <= n; column++, h++) {
        for (int num = 1; num <= n; num++) {
          int index = cover_matrix_index(row, column, n);
          matrix[index][h] = 1;
        }
      }
    }

    return h;
}

vector<vector<int> > Sudoku::convert(){
    vector<vector<int> > coverMatrix = create_cover_matrix();

    for (int row = 1; row <= n; row++) {
      for (int column = 1; column <= n; column++) {
        int n = Board[row - 1][column - 1];

        if (n != 0) {
          for (int num = 1; num <= n; num++) {
            if (num != n) {
                for(int i = 0; i < n; i++){
                    coverMatrix[cover_matrix_index(num,row,column)][i] = 0;
                }
            }
          }
        }
      }
    }

    return coverMatrix;

}

DancingNode* DancingNode::linkDown(DancingNode* node){
    node->down = down;
    node->down->up = node;
    node->up = this;
    down = node;
    return node;
}

DancingNode* DancingNode::linkRight(DancingNode* node){
    node->right = right;
    node->right->left = node;
    node->left = this;

    return node;
}

void DancingNode::removeLeftRight(){
    left->right = right;
    right->left = left;
}

void DancingNode::reinsertLeftRight(){
    left->right = this;
    right->left = this;
}

void DancingNode::removeTopDown(){
    up->down = down;
    down->up = up;
}

void DancingNode::reinsertTopDown(){
    up->down = this;
    down->up = this;
}

ColumnNode::ColumnNode(string n){
    DancingNode(*this);
    size = 0;
    name = n;
    
}

void ColumnNode::cover(){
    removeLeftRight();

    for(DancingNode* i = down; i != this; i = i->down){
        for (DancingNode* j = i->right; j != i; j = j->right){
            j->removeTopDown();
            j->column->size--;
        }
    }
}

void ColumnNode::uncover(){

    for(DancingNode* i = up; i != this; i = i->up){
        for (DancingNode* j = i->left; j != i; j = j->left){
            j->column->size++;
            j->reinsertTopDown();
        }
    }
    reinsertLeftRight();
}

//creating a quadruple linked list
ColumnNode* DLX::createDLXvec(vector<vector<int> > cover){
    int nbColumns = cover[0].size();

    ColumnNode* headerNode = new ColumnNode("header");

    vector<ColumnNode*> colNodes;

    for(int i = 0; i < nbColumns; i++){
        ColumnNode* n = new ColumnNode(i + "");
        colNodes.push_back(n);
        headerNode->linkRight(n);
    }

    headerNode = headerNode->right->column;

    for (auto it : cover){
        DancingNode* prev = nullptr;
        for(int j = 0 ; j < nbColumns; j++){
            if (it[j] == 1){
                ColumnNode* col = colNodes[j];
                DancingNode* newNode = new DancingNode(col);
                if (prev == nullptr){
                    prev = newNode;
                }

                col->up->linkDown(newNode);
                prev = prev->linkRight(newNode);
                col->size++;

            }
        }
    }

    headerNode->size = nbColumns;

    return headerNode;
}

//implementing the algorithm
void DLX::process(int k){

}

