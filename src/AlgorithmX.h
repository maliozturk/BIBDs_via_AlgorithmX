//
// Created by muhammet on 12/22/20.
//

#ifndef BLOCK_DESIGNS_V_ALGORITHMX_ALGORITHMX_H
#define BLOCK_DESIGNS_V_ALGORITHMX_ALGORITHMX_H
#define MAX_ROW 1000
#define MAX_COL 1000
#include <string>

struct Node {
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

static double SOLUTION_COUNT = 0;

static struct Node *header = new Node();
static bool ProbMat[MAX_ROW][MAX_COL];
static struct Node Matrix[MAX_ROW][MAX_COL];
static std::vector<struct Node *> solutions;


class AlgorithMX{
public:
    static void fillProbMat(std::vector<std::vector<int>> arrays) {
        std::vector<std::vector<int>>::iterator row;
        std::vector<int>::iterator col;
        int r = 0;
        for (row = arrays.begin(); row != arrays.end(); row++) {
            r++;
            for (col = row->begin(); col != row->end(); col++) {
                ProbMat[r][*col - 1] = true;
            };

        };
    };

    static int getRight(int i, int nRow, int nCol) { return (i + 1) % nCol; }

    static int getLeft(int i, int nRow, int nCol) { return (i - 1 < 0) ? nCol - 1 : i - 1; }

    static int getUp(int i, int nRow, int nCol) { return (i - 1 < 0) ? nRow : i - 1; }

    static int getDown(int i, int nRow, int nCol) { return (i + 1) % (nRow + 1); }

    static void cover(struct Node *targetNode) {
        struct Node *row, *rightNode;

        struct Node *colNode = targetNode->column;

        colNode->left->right = colNode->right;
        colNode->right->left = colNode->left;

        for (row = colNode->down; row != colNode; row = row->down) {
            for (rightNode = row->right; rightNode != row;
                 rightNode = rightNode->right) {
                rightNode->up->down = rightNode->down;
                rightNode->down->up = rightNode->up;

                Matrix[0][rightNode->colID].nodeCount -= 1;
            }
        }
    }

    static void uncover(struct Node *targetNode) {
        struct Node *rowNode, *leftNode;

        struct Node *colNode = targetNode->column;

        for (rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up) {
            for (leftNode = rowNode->left; leftNode != rowNode;
                 leftNode = leftNode->left) {
                leftNode->up->down = leftNode;
                leftNode->down->up = leftNode;

                Matrix[0][leftNode->colID].nodeCount += 1;
            }
        }

        colNode->left->right = colNode;
        colNode->right->left = colNode;
    }

    static Node *getMinColumn() {
        struct Node *h = header;
        struct Node *min_col = h->right;
        h = h->right->right;
        do {
            if (h->nodeCount < min_col->nodeCount) {
                min_col = h;
            }
            h = h->right;
        } while (h != header);

        return min_col;
    };

    static void search(int k) {
        struct Node *rowNode;
        struct Node *rightNode;
        struct Node *leftNode;
        struct Node *column;
        if (header->right == header) {
            SOLUTION_COUNT++;
            //write_solution_to_file(7, 3);
            return;
        }

        column = getMinColumn();

        cover(column);

        for (rowNode = column->down; rowNode != column;
             rowNode = rowNode->down) {
            solutions.push_back(rowNode);

            for (rightNode = rowNode->right; rightNode != rowNode;
                 rightNode = rightNode->right)
                cover(rightNode);

            search(k + 1);

            solutions.pop_back();

            column = rowNode->column;
            for (leftNode = rowNode->left; leftNode != rowNode;
                 leftNode = leftNode->left)
                uncover(leftNode);
        }

        uncover(column);
    }

    static Node *createToridolMatrix(int nRow, int nCol) {
        for (int i = 0; i <= nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                if (ProbMat[i][j]) {
                    int a, b;

                    if (i) Matrix[0][j].nodeCount += 1;

                    Matrix[i][j].column = &Matrix[0][j];

                    Matrix[i][j].rowID = i;
                    Matrix[i][j].colID = j;


                    a = i;
                    b = j;
                    do { b = getLeft(b, nRow, nCol); } while (!ProbMat[a][b] && b != j);
                    Matrix[i][j].left = &Matrix[i][b];

                    a = i;
                    b = j;
                    do { b = getRight(b, nRow, nCol); } while (!ProbMat[a][b] && b != j);
                    Matrix[i][j].right = &Matrix[i][b];

                    a = i;
                    b = j;
                    do { a = getUp(a, nRow, nCol); } while (!ProbMat[a][b] && a != i);
                    Matrix[i][j].up = &Matrix[a][j];

                    a = i;
                    b = j;
                    do { a = getDown(a, nRow, nCol); } while (!ProbMat[a][b] && a != i);
                    Matrix[i][j].down = &Matrix[a][j];
                }
            }
        }

        header->right = &Matrix[0][0];

        header->left = &Matrix[0][nCol - 1];

        Matrix[0][0].left = header;
        Matrix[0][nCol - 1].right = header;
        return header;
    }

    static void findSolutions(int starting_point, int nr, int nc, const std::vector<std::vector<int>> &given_array) {
        int nRow = nr;
        int nCol = nc;


        for (int i = 0; i <= nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                if (i == 0) ProbMat[i][j] = true;
                else ProbMat[i][j] = false;
            }
        }
        fillProbMat(given_array);
        createToridolMatrix(nRow, nCol);
        search(starting_point);
    }

    static void solve_design_problem(std::vector<int> vKlets) {
        int v = vKlets[0];
        int k = vKlets[1];
        std::vector<std::vector<int>> pairs = Combinations::combs(v, 2);
        std::vector<std::vector<int>> combs = Combinations::combs(v, k);
        std::vector<std::vector<int>> Inc_Matrix = IncidenceMatrix::getIncidenceMatrix(combs, pairs);
        std::vector<std::vector<int>> Design = IncidenceMatrix::getSets(Inc_Matrix);
        findSolutions(0, combs.size(), pairs.size(), Design);
    }

    static void write_solution_to_file(int v, int k)
    {
        std::ofstream myFile;
        myFile.open(std::to_string(v)+"_"+std::to_string(k)+"_1_BIBDs.txt", std::ios_base::app);
        
        std::vector<std::vector<int>> combs = Combinations::combs(v,k);
        
        std::vector<struct Node*>::iterator i;
        for(i = solutions.begin(); i!=solutions.end(); i++) {
            int val = (*i)->rowID;
            myFile << val << " ";
        }
        myFile << "\n";
        myFile.close();
        
    }

};

#endif //BLOCK_DESIGNS_V_ALGORITHMX_ALGORITHMX_H
