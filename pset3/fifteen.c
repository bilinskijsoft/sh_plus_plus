/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

bool isInMassive(int num) {
    for (int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            if (board[i][j]==num) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    srand48((long) time(NULL));
    int random = 0;
    
    for (int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            board[i][j]=-1;    
        }
    }
    
    for (int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            do {
                random = drand48() * (d*d);
            } while (isInMassive(random));
            board[i][j]=random;
        }
    }
    
    /**
    * Init for debuging
    */
    
    // int k=d*d;
    // for (int i=0;i<d;i++) {
    //     for (int j=0;j<d;j++) {
    //         k--;
    //         if (d*d % 2 == 0 && k==2) {
    //             board[i][j]=1;    
    //         }
    //         else if (d*d % 2 == 0 && k==1) {
    //             board[i][j]=2;    
    //         }
    //         else {
    //             board[i][j]=k;    
    //         }
    //     }
    // }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            if (d >3) {
                if (board[i][j]!=d*d) {
                    if (board[i][j]>9){
                        printf("%d ", board[i][j]);
                    }
                    else {
                        printf(" %d ", board[i][j]);
                    }
                }
                else {
                    printf(" _ ");
                }   
            }
            else {
                if (board[i][j]!=0) {
                    printf("%d ", board[i][j]);
                }
                else {
                    printf("_ ");
                }
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tile_i=-1;
    int tile_j=-1;
    for (int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            if (tile==board[i][j]) {
                tile_i=i;
                tile_j=j;
            }
        }
    }
    
    if (tile < d*d) {
        if (board[tile_i-1][tile_j]==0 && tile_i>0) {
            board[tile_i-1][tile_j]=tile;
            board[tile_i][tile_j]=0; 
            return true;
        }
        else if(board[tile_i+1][tile_j]==0 && tile_i<d-1) {
            board[tile_i+1][tile_j]=tile;
            board[tile_i][tile_j]=0; 
            return true;
        }
        else if(board[tile_i][tile_j-1]==0 && tile_j>0) {
            board[tile_i][tile_j-1]=tile;
            board[tile_i][tile_j]=0;    
            return true;
        }
        else if(board[tile_i][tile_j+1]==0 && tile_j<d-1) {
            board[tile_i][tile_j+1]=tile;
            board[tile_i][tile_j]=0;    
            return true;
        }
    }
    return false; 
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int k=0;
    for (int i=0;i<d;i++) {
        for (int j=0;j<d;j++) {
            k++;
            if (board[i][j]!=k && k<d*d) {
                return false;
            }
        }
    }

    
    return true;
}
