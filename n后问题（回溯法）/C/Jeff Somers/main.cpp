#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32

#define MAX_BOARDSIZE 21
typedef unsigned __int64 SOLUTIONTYPE;

#else
#define MAX_BOARDSIZE 18
typedef unsigned long SOLUTIONTYPE;

#endif
#define MIN_BOARDSIZE 2
SOLUTIONTYPE g_numsolutions = 0;
void printtable(int boardsize, int* aQueenBitRes, SOLUTIONTYPE numSolution)
{
    int i, j, k, row;

    /*  We only calculated half the solutions, because we can derive
    the other half by reflecting the solution across the "Y axis". */
    for (k = 0; k < 2; ++k)
    {
#ifdef WIN32
        printf("*** Solution #: %I64d ***\n", 2 * numSolution + k - 1);
#else
        printf("*** Solution #: %d ***\n", 2 * numSolution + k - 1);
#endif
        for ( i = 0; i < boardsize; i++)
        {
            unsigned int bitf;
            
            bitf = aQueenBitRes[i];

            row = bitf ^ (bitf & (bitf - 1)); /* get least significant bit */
            for ( j = 0; j < boardsize; j++)
            {
                /* keep shifting row over to the right until we find the one ¡®1¡® in
                the binary representation.  There will only be one ¡®1¡®. */
                if (0 == k && ((row >> j) & 1))
                {
                    printf("Q ");
                }
                else if (1 == k && (row & (1 << (boardsize - j - 1)))) /* this is the board reflected across the "Y axis" */
                {
                    printf("Q ");
                }
                else
                {
                    printf(". ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

void Nqueen(int board_size)
{
    int aQueenBitRes[MAX_BOARDSIZE]; /* results */
    int aQueenBitCol[MAX_BOARDSIZE]; /* marks colummns which already have queens */
    int aQueenBitPosDiag[MAX_BOARDSIZE]; /* marks "positive diagonals" which already have queens */
    int aQueenBitNegDiag[MAX_BOARDSIZE]; /* marks "negative diagonals" which already have queens */
    int aStack[MAX_BOARDSIZE + 2]; /* we use a stack instead of recursion */
    register int* pnStack;


    register int numrows = 0; /* numrows redundant - could use stack */
    register unsigned int lsb; /* least significant bit */
    register unsigned int bitfield; /* bits which are set mark possible positions for a queen */
    int i;
    int odd = board_size & 1; /* 0 if board_size even, 1 if odd */
    int board_minus = board_size - 1; /* board size - 1 */
    int mask = (1 << board_size) - 1; /* if board size is N, mask consists of N 1¡®s */


    /* Initialize stack */
    aStack[0] = -1; /* set sentinel -- signifies end of stack */

    /* NOTE: (board_size & 1) is true iff board_size is odd */
    /* We need to loop through 2x if board_size is odd */
    for (i = 0; i < (1 + odd); ++i)
    {
        /* We don¡®t have to optimize this part; it ain¡®t the
        critical loop */
        bitfield = 0;
        if (0 == i)
        {
            int half = board_size>>1; /* divide by two */
            bitfield = (1 << half) - 1;
            pnStack = aStack + 1; /* stack pointer */

            aQueenBitRes[0] = 0;
            aQueenBitCol[0] = aQueenBitPosDiag[0] = aQueenBitNegDiag[0] = 0;
        }
        else
        {
            bitfield = 1 << (board_size >> 1);
            numrows = 1; /* prob. already 0 */

            /* The first row just has one queen (in the middle column).*/
            aQueenBitRes[0] = bitfield;
            aQueenBitCol[0] = aQueenBitPosDiag[0] = aQueenBitNegDiag[0] = 0;
            aQueenBitCol[1] = bitfield;

            /* Now do the next row.  Only set bits in half of it, because we¡®ll
            flip the results over the "Y-axis".  */
            aQueenBitNegDiag[1] = (bitfield >> 1);
            aQueenBitPosDiag[1] = (bitfield << 1);
            pnStack = aStack + 1; /* stack pointer */
            *pnStack++ = 0; /* we¡®re done w/ this row -- only 1 element & we¡®ve done it */
            bitfield = (bitfield - 1) >> 1; /* bitfield -1 is all 1¡®s to the left of the single 1 */
        }

        /* this is the critical loop */
        for (;;)
        {
            /* could use
            lsb = bitfield ^ (bitfield & (bitfield -1));
            to get first (least sig) "1" bit, but that¡®s slower. */
            lsb = -((signed)bitfield) & bitfield; /* this assumes a 2¡®s complement architecture */
            if (0 == bitfield)
            {
                bitfield = *--pnStack; /* get prev. bitfield from stack */
                if (pnStack == aStack) { /* if sentinel hit.... */
                    break ;
                }
                --numrows;
                continue;
            }
            bitfield &= ~lsb; /* toggle off this bit so we don¡®t try it again */

            aQueenBitRes[numrows] = lsb; /* save the result */
            if (numrows < board_minus) /* we still have more rows to process? */
            {
                int n = numrows++;
                aQueenBitCol[numrows] = aQueenBitCol[n] | lsb;
                aQueenBitNegDiag[numrows] = (aQueenBitNegDiag[n] | lsb) >> 1;
                aQueenBitPosDiag[numrows] = (aQueenBitPosDiag[n] | lsb) << 1;
                *pnStack++ = bitfield;
                 /* We can¡®t consider positions for the queen which are in the same
                column, same positive diagonal, or same negative diagonal as another
                queen already on the board. */
                bitfield = mask & ~(aQueenBitCol[numrows] | aQueenBitNegDiag[numrows] | aQueenBitPosDiag[numrows]);
                continue;
            }
            else
            {
                /* We have no more rows to process; we found a solution. */
                /* Comment out the call to printtable in order to print the solutions as board position*/
                /* printtable(board_size, aQueenBitRes, g_numsolutions + 1);  */
                ++g_numsolutions;
                bitfield = *--pnStack;
                --numrows;
                continue;
            }
        }
    }

    /* multiply solutions by two, to count mirror images */
    g_numsolutions *= 2;
}

/* Print the results at the end of the run */
void printResults(time_t* pt1, time_t* pt2)
{
    double secs;
    int hours , mins, intsecs;

    printf("End: \t%s", ctime(pt2));
    secs = difftime(*pt2, *pt1);
    intsecs = (int)secs;
    printf("Calculations took %d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));

    /* Print hours, minutes, seconds */
    hours = intsecs/3600;
    intsecs -= hours * 3600;
    mins = intsecs/60;
    intsecs -= mins * 60;
    if (hours > 0 || mins > 0)
    {
        printf("Equals ");
        if (hours > 0)
        {
            printf("%d hour%s, ", hours, (hours == 1) ? "" : "s");
        }
        if (mins > 0)
        {          
            printf("%d minute%s and ", mins, (mins == 1) ? "" : "s");
        }
        printf("%d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));

    }
}

/* main routine for N Queens program.*/
int main(int argc, char** argv)
{
    time_t t1, t2;
    int boardsize;

    if (argc != 2) {
        printf("N Queens program by Jeff Somers.\n");
        printf("\tallagash98@yahoo.com or jsomers@alumni.williams.edu\n");
        printf("This program calculates the total number of solutions to the N Queens problem.\n");
        printf("Usage: nq <width of board>\n"); /* user must pass in size of board */
        return 0;
    }
 
    boardsize = atoi(argv[1]);

    /* check size of board is within correct range */
    if (MIN_BOARDSIZE > boardsize || MAX_BOARDSIZE < boardsize)
    {
       printf("Width of board must be between %d and %d, inclusive.\n",
            MIN_BOARDSIZE, MAX_BOARDSIZE );
        return 0;
    }

    time(&t1);
    printf("N Queens program by Jeff Somers.\n");
    printf("\tallagash98@yahoo.com or jsomers@alumni.williams.edu\n");
    printf("Start: \t %s", ctime(&t1));

    Nqueen(boardsize); /* find solutions */
    time(&t2);

    printResults(&t1, &t2);

    if (g_numsolutions != 0)
    {
#ifdef WIN32
        printf("For board size %d, %I64d solution%s found.\n", boardsize, g_numsolutions, (g_numsolutions == 1 ? "" : "s"));
#else
        printf("For board size %d, %d solution%s found.\n", boardsize, g_numsolutions, (g_numsolutions == 1 ? "" : "s"));
#endif
    }
    else
    {
        printf("No solutions found.\n");
    }

    return 0;
}
