// Libraries usadas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include "cache.h"

// Função do menu
void ShowMenu()
{
    printf("\n +------------- Menu ---------------+");
    printf("\n |           1 - LOAD               |");
    printf("\n |           2 - CLEAR              |");
    printf("\n |           3 - LIST               |");
    printf("\n |           4 - FOUNDP             |");
    printf("\n |           5 - SEARCH             |");
    printf("\n |           6 - EDIT               |");
    printf("\n |           7 - CENTER             |");
    printf("\n |           8 - AGE                |");
    printf("\n |           9 - SORT               |");
    printf("\n |           10 - STATEC            |");
    printf("\n |           11 - M81               |");
    printf("\n |           12 - SAVE              |");
    printf("\n |           0 - QUIT               |");
    printf("\n +----------------------------------+");
}

// Codigo Principal
int main()
{

    // Adiciona especiais Caracteres
    setlocale(LC_ALL, "Portuguese.utf8");

    // Variaveis de uso do Menu
    int Option = 0;
    Data data[2000];

    // Do While que continua até receber Variavel diferente de 0
    do
    {
        // Invoca a Função de Menu
        ShowMenu();

        printf("\n \n Choose an option: ");

        // Enquanto não for um valor inteiro
        while (scanf("%d", &Option) != 1)
        {
            ShowMenu();
            printf("\n \n Invalid input! Please enter a valid Option: ");
            // Limpa o Input
            while (getchar() != '\n');
        }

        // Menu é selecionado por Switch&Case
        switch (Option)
        {

        // Load File é o Case 1
        case 1:
            char ficheiro[50];
            printf("Enter the name of the file:");
            scanf("%s", ficheiro);
            printf("\n ----------LOAD---------- \n ");
            LoadFile(data, ficheiro);
            break;

        // ClearMemory é o Case 2
        case 2:
            printf("\n ----------CLEAR---------- \n ");
            ClearMemory(data);
            printf("Variables successfully cleared!");
            break;

        // List é o Case 3
        case 3:
            printf("\n ----------LIST---------- \n ");
            List(data);
            break;

        // FoundP é o Case 4
        case 4:
            printf("\n ----------FOUNDP---------- \n");
            FoundP(data);
            break;

        // Search é o Case 5
        case 5:
            printf("\n ----------SEARCH---------- \n");
            Search(data);
            break;

        // EDIT é o Case 6
        case 6:
            printf("\n ----------EDIT---------- \n");
            EditCache(data);
            break;

        // CENTER é o Case 7
        case 7:
            printf("\n ----------CENTER---------- \n");
            Center(data);
            break;
        // AGE é o Case 8
        case 8:
            printf("\n ----------AGE---------- \n");
            CalculateCacheAge(data);
            break;

        // SORT é o Case 9
        case 9:
            printf("\n ----------SORT---------- \n");
            Sort(data);
            break;
        
        // STATEC é o Case 10
        case 10:
            printf("\n ----------STATEC---------- \n");
            STATEC(data);
            break;
        
        // M81 é o Case 11
        case 11:
            printf("\n ----------M81---------- \n");
            M81(data);
            break;


        // SAVE é o Case 12
        case 12:
            printf("\n ----------SAVE---------- \n");
            SaveFile(data);
            break;

        // Quit
        case 0:
            QUIT();
            break;

        // Error choice se for um numero inteiro errado
        default:
            printf("\n Invalid option! \n");
            break;
        }

    } while (Option != 0);

    return 0;
}