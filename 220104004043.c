#include <stdio.h>
#define N 50 /*  variable for initializing the map*/
typedef struct
{
    char Map[N][N];
    int Width;
    int Height;
} Forest;

typedef struct
{
    int Coord_X;
    int Coord_Y;
    int Number_of_Bottle;
    int not_used_bottle;
} Botanist;

void init_game(Forest *forest, Botanist *botanist) /*function that initialize the game according to the init.txt file*/
{
    FILE *fp = fopen("init.txt", "r");
    char comma;
    /*getting the forest information from the file*/
    fscanf(fp, "%d,%d", &(*forest).Width, &(*forest).Height);
    fscanf(fp, "%d,%d,%d ", &(*botanist).Coord_X, &(*botanist).Coord_Y, &(*botanist).not_used_bottle);
    /*get the map*/
    int row = 0, column = 0;
    while (fscanf(fp, "%c,", &comma) != EOF)
    {
        if (comma == '\n')
        {
            row++;
            column = 0;
        }
        else
        {
            (*forest).Map[row][column++] = comma;
        }
    }
    fclose(fp);
}

void display_forest(Forest *forest, Botanist *botanist) /*function that displays the last view of the forest*/
{
    /*display the informations*/
    printf("Collected flowers: %d\n", (*botanist).Number_of_Bottle);
    printf("Not used bottle number: %d\n", (*botanist).not_used_bottle);
    printf("Botanist coordinates: (%d,%d)\n", (*botanist).Coord_X, (*botanist).Coord_Y);

    /*display the forest last view*/
    int i, j;
    for (i = 0; i < (*forest).Width; i++)
    {
        for (j = 0; j < (*forest).Height; j++)
        {
            printf("%c", (*forest).Map[i][j]);
            if (j != (*forest).Height - 1)
                printf(","); /*seperates the trees and other things*/
        }
        printf("\n");
    }
}

int is_over(Forest *forest, Botanist *botanist) /*function that says there is a flowers or not*/
{
    int flag = 0; /*flag for checking flowers*/
    int i, j;

    for (i = 0; i < (*forest).Width; i++)
    {
        for (j = 0; j < (*forest).Height; j++)
        {
            if ((*forest).Map[i][j] == 'X') /*if it finds a rare flower then returns 1*/
                flag = 1;
        }
    }
    return flag;
}

void search(Forest *forest, Botanist *botanist) /*function that searchs for the flowers*/
{
    char direction;
    int flag = is_over(forest, botanist); /*check for the flowers*/

    if (flag == 1)
    {
        printf("Enter a direction (r:right, l:left, u:up, d:down): ");
        scanf(" %c", &direction);
        printf("\n");

        int xCo = botanist->Coord_X;
        int yCo = botanist->Coord_Y;

        switch (direction) /*update new coordinates according to the user's choice*/
        {
        case 'r':
            yCo += 1;
            break;
        case 'l':
            yCo -= 1;
            break;
        case 'u':
            xCo -= 1;
            break;
        case 'd':
            xCo += 1;
            break;
        default:
            printf("INVALID DIRECTION\n");
        }

        if (forest->Map[xCo][yCo] == ' ') /*according to the user's choice look for possibilities*/
        {
            (*forest).Map[botanist->Coord_X][botanist->Coord_Y] = ' ';
            (*botanist).Coord_X = xCo; /*update new coordinates for the structure*/
            (*botanist).Coord_Y = yCo;
            (*forest).Map[(*botanist).Coord_X][(*botanist).Coord_Y] = 'B'; /*update botanist's new place*/
        }
        else if ((*forest).Map[xCo][yCo] == 'X') /*if you find a rare flower update the values of theese variables*/
        {
            (*botanist).Number_of_Bottle += 1;
            (*botanist).not_used_bottle -= 1;
            (*forest).Map[xCo][yCo] = ' ';
            printf("I've found it!\n");
        }
        else
        {
            printf("WARNING: YOU HIT A TREE\n");
        }
        display_forest(forest, botanist); /*display the forest according to the choice after all the processes*/
        search(forest, botanist);         /*Ask for input until there are no flowers left */
    }
    else /*if there is no flowers left save the last view of the forest and information in last.txt file*/
    {
        FILE *fp = fopen("last.txt", "w");
        fprintf(fp, "Size of the game: %d X %d\n", forest->Width, forest->Height);
        fprintf(fp, "Collected flowers: %d\n", botanist->Number_of_Bottle);
        fprintf(fp, "Not used bottle number: %d\n", botanist->not_used_bottle);
        fprintf(fp, "Botanist coordinates: (%d,%d)\n", botanist->Coord_X, botanist->Coord_Y);
        int i, j;
        for (i = 0; i < forest->Width; i++)
        {
            for (j = 0; j < forest->Height; j++)
            {
                fprintf(fp, "%c", forest->Map[i][j]);
                if (j != forest->Height - 1)
                    fprintf(fp, ",");
            }
            if (i != forest->Width - 1)
                fprintf(fp, "\n");
        }
        fclose(fp);

        printf("GAME OVER!!!\n"); /*end of the game*/
    }
}

int main()
{
    Forest forest;
    Forest *fp = &forest; /*pointer for change things in function not local makes it global(but local only in main function)*/
    Botanist botanist;
    Botanist *bp = &botanist; /*pointer for change things in function not local makes it global(but local only in main function)*/
    (*bp).Number_of_Bottle = 0;

    init_game(fp, bp);      /*initialize*/
    display_forest(fp, bp); /*displaying*/
    search(fp, bp);         /*game is starting*/
    return 0;
}