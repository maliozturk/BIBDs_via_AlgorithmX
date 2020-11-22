#include <iostream>
#include "vector"
#include "Combinations.h"
#include "IncidenceMatrix.h"

#define MAX_ROW 1000
#define MAX_COL 1000
bool ProbMat[MAX_ROW][MAX_COL];

struct Node
{
public:
    struct Node *left;
    struct Node *right;
    struct Node *up;
    struct Node *down;
    struct Node *column;
    int rowID;
    int colID;
    int nodeCount;
};

struct Node *header = new Node();

struct Node Matrix[MAX_ROW][MAX_COL];

std::vector <struct Node*> solutions;

int nRow = 0,nCol = 0;


int getRight(int i){return (i+1) % nCol; }
int getLeft(int i){return (i-1 < 0) ? nCol-1 : i-1 ; }
int getUp(int i){return (i-1 < 0) ? nRow : i-1 ; }
int getDown(int i){return (i+1) % (nRow+1); }

void cover(struct Node *targetNode)
{
    struct Node *row, *rightNode;

    // get the pointer to the header of column
    // to which this node belong
    struct Node *colNode = targetNode->column;

    // unlink column header from it's neighbors
    colNode->left->right = colNode->right;
    colNode->right->left = colNode->left;

    // Move down the column and remove each row
    // by traversing right
    for(row = colNode->down; row != colNode; row = row->down)
    {
        for(rightNode = row->right; rightNode != row;
            rightNode = rightNode->right)
        {
            rightNode->up->down = rightNode->down;
            rightNode->down->up = rightNode->up;

            // after unlinking row node, decrement the
            // node count in column header
            Matrix[0][rightNode->colID].nodeCount -= 1;
        }
    }
}

void uncover(struct Node *targetNode)
{
    struct Node *rowNode, *leftNode;

    // get the pointer to the header of column
    // to which this node belong
    struct Node *colNode = targetNode->column;

    // Move down the column and link back
    // each row by traversing left
    for(rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up)
    {
        for(leftNode = rowNode->left; leftNode != rowNode;
            leftNode = leftNode->left)
        {
            leftNode->up->down = leftNode;
            leftNode->down->up = leftNode;

            // after linking row node, increment the
            // node count in column header
            Matrix[0][leftNode->colID].nodeCount += 1;
        }
    }

    // link the column header from it's neighbors
    colNode->left->right = colNode;
    colNode->right->left = colNode;
}

Node *getMinColumn()
{
    struct Node *h = header;
    struct Node *min_col = h->right;
    h = h->right->right;
    do
    {
        if(h->nodeCount < min_col->nodeCount)
        {
            min_col = h;
        }
        h = h->right;
    }while(h != header);

    return min_col;
};

double SOLUTION_COUNT = 0;
/*
void plus_Sol_Count()
{


    ofstream myfile;
    myfile.open("7-3-1_results.txt", std::ios_base::app);
    vector<struct Node*>::iterator i;
    for(i = solutions.begin(); i!=solutions.end(); i++) {
        myfile << (*i)->rowID << " ";
    }
    myfile<<"\n";


}
*/
void search(int k)
{
    struct Node *rowNode;
    struct Node *rightNode;
    struct Node *leftNode;
    struct Node *column;
    // if no column left, then we must
    // have found the solution
    if(header->right == header)
    {
        SOLUTION_COUNT++;
        /*plus_Sol_Count();*/
        return;
    }

    // choose column deterministically
    column = getMinColumn();

    // cover chosen column
    cover(column);

    for(rowNode = column->down; rowNode != column;
        rowNode = rowNode->down )
    {
        solutions.push_back(rowNode);

        for(rightNode = rowNode->right; rightNode != rowNode;
            rightNode = rightNode->right)
            cover(rightNode);

        // move to level k+1 (recursively)
        search(k+1);

        // if solution in not possible, backtrack (uncover)
        // and remove the selected row (set) from solution
        solutions.pop_back();

        column = rowNode->column;
        for(leftNode = rowNode->left; leftNode != rowNode;
            leftNode = leftNode->left)
            uncover(leftNode);
    }

    uncover(column);
}

void fillProbMat(std::vector<std::vector<int>> arrays){
    std::vector<std::vector<int>>::iterator row;
    std::vector<int>::iterator col;
    int r = 0;
    for(row=arrays.begin(); row!= arrays.end(); row++){
        r++;
        for(col=row->begin(); col!= row->end(); col++){
            ProbMat[r][*col - 1] = true;
        };

    };
};

Node *createToridolMatrix()
{
    // One extra row for list header nodes
    // for each column
    for(int i = 0; i <= nRow; i++)
    {
        for(int j = 0; j < nCol; j++)
        {
            // If it's 1 in the problem matrix then
            // only create a node
            if(ProbMat[i][j])
            {
                int a, b;

                // If it's 1, other than 1 in 0th row
                // then count it as node of column
                // and increment node count in column header
                if(i) Matrix[0][j].nodeCount += 1;

                // Add pointer to column header for this
                // column node
                Matrix[i][j].column = &Matrix[0][j];

                // set row and column id of this node
                Matrix[i][j].rowID = i;
                Matrix[i][j].colID = j;

                // Link the node with neighbors

                // Left pointer
                a = i; b = j;
                do{ b = getLeft(b); } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].left = &Matrix[i][b];

                // Right pointer
                a = i; b = j;
                do { b = getRight(b); } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].right = &Matrix[i][b];

                // Up pointer
                a = i; b = j;
                do { a = getUp(a); } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].up = &Matrix[a][j];

                // Down pointer
                a = i; b = j;
                do { a = getDown(a); } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].down = &Matrix[a][j];
            }
        }
    }

    // link header right pointer to column
    // header of first column
    header->right = &Matrix[0][0];

    // link header left pointer to column
    // header of last column
    header->left = &Matrix[0][nCol-1];

    Matrix[0][0].left = header;
    Matrix[0][nCol-1].right = header;
    return header;
}


void findSolutions(int starting_point, int nr, int nc, const std::vector<std::vector<int>>& given_array){
    nRow = nr;
    nCol = nc;

    for(int i=0; i<=nRow; i++)
    {
        for(int j=0; j<nCol; j++)
        {
            // if it's row 0, it consist of column
            // headers. Initialize it with 1
            if(i == 0) ProbMat[i][j] = true;
            else ProbMat[i][j] = false;
        }
    }
    fillProbMat(given_array);
    createToridolMatrix();
    search(starting_point);
}
void getDesign_of_Solution(const std::vector<int>& nds, std::vector<std::vector<int>> design, int k){
    for(int i: nds){
        std::cout << "[";
        for(int j=0;j<k;j++){
            if(j==k-1)
                std::cout << design[i][j];
            else
                std::cout << design[i][j] << ",";
        }
        std::cout << "]," << std::endl;
    }
};


void solve_design_problem(int v, int k){
    std::vector<std::vector<int>> pairs = Combinations::combs(v,2);
    std::vector<std::vector<int>> combs = Combinations::combs(v, k);
    std::vector<std::vector<int>> Inc_Matrix = IncidenceMatrix::getIncidenceMatrix(combs,pairs);
    std::vector<std::vector<int>> Design = IncidenceMatrix::getSets(Inc_Matrix);
    findSolutions(0,combs.size(),pairs.size(),Design);
}

int main() {
    int v = 13;
    int k = 4;
    solve_design_problem(v, k);
    std::cout << SOLUTION_COUNT << " solutions found for " <<"("<<v<<","<<k<<",1)"<<" design.";
    return 0;
}
