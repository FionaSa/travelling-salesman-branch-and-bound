
/*
 * Variables
 */

int size =  5;

int result;

int *finalpath;


struct Node_s
{
    int id;
    int cost;
    int level;
    int *path;
    int **mat;
    int coldiag;
    struct Node_s *left, *right;
    struct Node_s  *up;

}Node_t;


/*
 * Functions
 */

void getconfig();

int resolve(int **mat);

void copypath(int **mat,int** matrix);

int getmin(int **mat, int x, int *firstmin, int *secondmin);

struct Node_s* insert(struct Node_s *tree, struct Node_s *node);
