#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#define NUM_THREADS 4
void Life_printer(int i, int j, char **array)
{
    for (int m = 0; m < i; m++)
    {
        for (int y = 0; y < j; y++)
        {
            printf("|%c", array[m][y]);
        }
        printf("|\n");
    }
}
void replica_to_array(char **replica, char **array, int r, int c)
{
   // #pragma omp parallel for
    for (int i = 0; i < r; i++)
    {
        memcpy(replica[i], array[i], c);
    }
}
void replica_to_array_int(int **replica, int **array, int r, int c)
{
   // #pragma omp parallel for
    for (int i = 0; i < r; i++)
    {
        memcpy(replica[i], array[i], c * sizeof(int));
    }
}
/*neibors counter && adjust*/
void setOrClear(char **array, int **zwisemas, int r, int c, int column, int row)
{
    char state = array[r][c];

    if (state == '*')
    {
        if (c + 1 < column)
            zwisemas[r][c + 1]++;
        if (c - 1 < column && c - 1 >= 0)
            zwisemas[r][c - 1]++;
        if (r + 1 < row)
            zwisemas[r + 1][c]++;
        if (r - 1 < row && r - 1 >= 0)
            zwisemas[r - 1][c]++;
        if (c + 1 < column && r + 1 < row)
            zwisemas[r + 1][c + 1]++;
        if (c - 1 < column && c - 1 >= 0 && r + 1 < row)
            zwisemas[r + 1][c - 1]++;
        if ((c - 1 < column) && (c - 1 >= 0) && (r - 1 < row) && (r - 1 >= 0))
            zwisemas[r - 1][c - 1]++;
        if (r - 1 < row && r - 1 >= 0 && c + 1 < column)
            zwisemas[r - 1][c + 1]++;
    }
    else
    {
        if (c + 1 < column)
            zwisemas[r][c + 1]--;
        if (c - 1 < column && c - 1 >= 0)
            zwisemas[r][c - 1]--;
        if (r + 1 < row)
            zwisemas[r + 1][c]--;
        if (r - 1 < row && r - 1 >= 0)
            zwisemas[r - 1][c]--;
        if (c + 1 < column && r + 1 < row)
            zwisemas[r + 1][c + 1]--;
        if (c - 1 < column && c - 1 >= 0 && r + 1 < row)
            zwisemas[r + 1][c - 1]--;
        if ((c - 1 < column) && (c - 1 >= 0) && (r - 1 < row) && (r - 1 >= 0))
            zwisemas[r - 1][c - 1]--;
        if (r - 1 < row && r - 1 >= 0 && c + 1 < column)
            zwisemas[r - 1][c + 1]--;
    }
}

int main(int argc, char *argv[])
{
    FILE *file_1;
    int r, c;
    char data;
    if (argc == 4 || argc == 3)
    {
        FILE *file_2;
        file_1 = fopen(argv[1], "r");
        fscanf(file_1, "%d", &r);
        fscanf(file_1, "%d", &c);
        char **array = (char **)malloc(r * sizeof(char *));
        char **replica = (char **)malloc(r * sizeof(char *));
        int **zwisemas = (int **)malloc(r * sizeof(int *));
        int **replica_zwisemas = (int **)malloc(r * sizeof(int *));
        for (int i = 0; i < r; i++)
        {
            array[i] = (char *)malloc(c * sizeof(char));
            replica[i] = (char *)malloc(c * sizeof(char));
            zwisemas[i] = (int *)malloc(c * sizeof(int));
            replica_zwisemas[i] = (int *)malloc(c * sizeof(int));
        }
        int k = 0, j = 0;

        for (int i = 0; i < r; i++)
            memset(zwisemas[i], 0, c * sizeof(int));

        while (fscanf(file_1, "%c", &data) == 1 && k < r)
        {
            if (data == '\n' || data == '|')
                continue;

            if (data == ' ')
            {
                array[k][j] = data;
                j++;
                if (j == c)
                {
                    j = 0;
                    k++;
                }
                continue;
            }
            array[k][j] = data;
            setOrClear(array, zwisemas, k, j, c, r);
            j++;
            if (j == c)
            {
                j = 0;
                k++;
            }
        }

        omp_set_dynamic(0);
        omp_set_num_threads(NUM_THREADS);
        int num = atoi(argv[2]);
        /*start the timer */
        double start_time = omp_get_wtime();
        /*for loop for the generations*/
        for (int l = 0; l < num; l++)
        {
            /*copy arrays*/
            replica_to_array(replica, array, r, c);
            replica_to_array_int(replica_zwisemas, zwisemas, r, c);
            #pragma  omp parallel for
            for (int i = 0; i < r; i++)
            {

                for (int j = 0; j < c; j++)
                {
                    if (replica[i][j] == ' ' && replica_zwisemas[i][j] == 0)
                    {
                        continue;
                    }

                    if (replica[i][j] == '*')
                    {
                        int zoune = replica_zwisemas[i][j];
                        if (zoune != 3 && zoune != 2)
                        {
                            array[i][j] = ' ';
                            setOrClear(array, zwisemas, i, j, c, r);
                        }
                    }
                    else
                    {
                        int zoune = replica_zwisemas[i][j];
                        if (zoune == 3)
                        {
                            array[i][j] = '*';
                            setOrClear(array, zwisemas, i, j, c, r);
                        }
                    }
                }
                
            }

        }
        double end_time = omp_get_wtime();

        printf("time : %lf\n", end_time - start_time);

        if (argc == 3)
        {
            Life_printer(r, c, array);
        }
        else if (argc == 4)
        {
            file_2 = fopen(argv[3], "w");
            for (int m = 0; m < r; m++)
            {
                for (int y = 0; y < c; y++)
                {
                    fprintf(file_2, "|%c", array[m][y]);
                }
                fprintf(file_2, "|\n");
            }
            fclose(file_2);
        }
        fclose((file_1));
        /*free the allocated memory*/
        for (int i = 0; i < r; i++)
        {
            char *strptr_1=array[i] ;
            char *strptr_2=replica[i] ;
            int *intptr_1=zwisemas[i] ;
            int *intptr_2=replica_zwisemas[i];
            free(strptr_1);
            free(strptr_2);
            free(intptr_1);
            free(intptr_2);
        }
        free(array);
        free(replica);
        free(replica_zwisemas);
        free(zwisemas);
        /*end of free*/

    }
    else
    {
        fprintf(stderr, "Error give me more arguments.");
    }


    return 0;
}
