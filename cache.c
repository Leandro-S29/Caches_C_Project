// Libraries usadas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "cache.h"

// Função de Load
int LoadFile(Data data[2000], char ficheiro[50])
{

    // Verifica se o contador esta a 0 e se estiver ele dá Load
    if (data[0].contador == 0)
    {

        // Abre o file e se não o achar dá erro
        FILE *file = fopen(ficheiro, "r");

        if (file == NULL)
        {
            fprintf(stderr, "File not found \n");
            return 1;
        }

        // Variaveis
        char line[1500];                  // Usada para a linha do cabeçario o valor introduzido
        int records = 0;                  // Variaveis de records sem values iguais
        char encounteredCodes[2000][100]; // Matriz para armazenar os códigos de cache encontrados
        int TRecords = 0;                 // Variaveis de records com values iguais

        // Ler e ignorar a linha de cabeçalho
        fgets(line, sizeof(line), file);

        // Ler e processar cada linha do ficheiro ignorando a primeira linha até ao final do ficheiro
        while (fgets(line, sizeof(line), file) != NULL)
        {
            setlocale(LC_NUMERIC, "C");
            int result = sscanf(line, "%99[^;];%199[^;];%99[^;];%199[^;];%lf;%lf;%49[^;];%49[^;];%lf;%lf;%49[^;];%49[^;];%d;%d;%d;%lf",
                                data[records].code,
                                data[records].name,
                                data[records].state,
                                data[records].owner,
                                &data[records].latitude,
                                &data[records].longitude,
                                data[records].kind,
                                data[records].size,
                                &data[records].difficulty,
                                &data[records].terrain,
                                data[records].status,
                                data[records].hidden_date,
                                &data[records].founds,
                                &data[records].not_founds,
                                &data[records].favourites,
                                &data[records].altitude);

            // Deteta erros de formatação e indica o local de erros
            if (result != 16)
            {
                fprintf(stderr, " \n Error in Line %d\n", records + 2); //+2 porque dá skip no header
                printf(" Erro in record %d\n", result);
                fclose(file);
                return 1;
            }

            TRecords++;

            // Procura por Data que tenha codigos iguais e removios
            int isRepeated = 0;
            for (int i = 0; i < records; i++)
            {
                if (strcmp(data[records].code, encounteredCodes[i]) == 0)
                {
                    isRepeated = 1;
                    break;
                }
            }

            // Apenas adiciona caches unicas
            if (!isRepeated)
            {
                // Armazenar o código encontrado para verificar se há repetição
                strcpy(encounteredCodes[records], data[records].code);
                records++;
            }
        }
        // Fecha o ficheiro
        fclose(file);

        // Coloca o records dentro do contador
        printf("\n%d not unique caches loaded>\n", TRecords);
        printf("%d unique caches loaded\n", records);

        // Coloca a quantidade de records dentro do contador para uso em outras funções
        data[0].contador = records;
    }

    // Se o contador estiver com mais de 0 ele não dá Load e manda mensagem de erro
    else if (data[0].contador != 0)
    {
        printf("There is content inside the Load! Clear it!");
    }

    return 0;
}

// Função de List
void List(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\nDoesn't exist a file loaded!\n");
    }
    else if (data[0].contador != 0)
    {
        // Print the data
        printf("Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficuldade | Terrain | Status | Hidden Date | Founds | Not Founds | Favorites | Altitude\n \n");
        for (int i = 0; i < data->contador; i++)
        {
            printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n", data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude, data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status, data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
            printf("\n");
        }
    }
}

// Função de ClearMemory
void ClearMemory(Data data[2000])
{
    for (int i = 0; i < 2000; i++)
    {
        // Limpa todos os campos da estrutura
        strcpy(data[i].code, "");
        strcpy(data[i].name, "");
        strcpy(data[i].state, "");
        strcpy(data[i].owner, "");
        data[i].latitude = 0.0;
        data[i].longitude = 0.0;
        strcpy(data[i].kind, "");
        strcpy(data[i].size, "");
        data[i].difficulty = 0.0;
        data[i].terrain = 0.0;
        strcpy(data[i].status, "");
        strcpy(data[i].hidden_date, "");
        data[i].founds = 0;
        data[i].not_founds = 0;
        data[i].favourites = 0;
        data[i].altitude = 0.0;
    }
    // Reinicia o contador para 0
    data[0].contador = 0;
}

void QUIT()
{
    printf("\n See you soon! \n");
}

// FoundP Funções
void FoundP(Data data[2000])
{
    // Se não encontrar dados, pede para dar Load
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
    }
    // Se encontrar dados, faz os calculos e mostra.
    else if (data[0].contador != 0)
    {
        for (int x = 0; x < (data[0].contador); x++)
        {
            int CF, CNF, Search;
            double CachePercentage;

            CF = data[x].founds;
            CNF = data[x].not_founds;
            Search = CF + CNF;

            CachePercentage = ((double)CF / Search) * 100;

            printf("Found Percentage: %.1lf%% \n", CachePercentage);
            printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n", data[x].code, data[x].name, data[x].state, data[x].owner, data[x].latitude, data[x].longitude, data[x].kind, data[x].size, data[x].difficulty, data[x].terrain, data[x].status, data[x].hidden_date, data[x].founds, data[x].not_founds, data[x].favourites, data[x].altitude);
            printf("\n");
        }
    }
}

// Função SEARCH
void Search(Data data[2000])
{
    // Verefica se existe cache
    // Se não tiver Cahes não permite dar Search
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
    }

    // Se tiver Cache ele excuta o search
    else if (data[0].contador != 0)
    {

        // Variaveis
        char CodeToSearch[100];
        int CacheFound = 0; // Flag de vereficação

        printf("Enter the Code you are looking for:");
        scanf("%s", CodeToSearch);

        for (int i = 0; i < data[0].contador; i++)
        {
            if (strcmp(data[i].code, CodeToSearch) == 0)
            {
                // Cache found, print details
                CacheFound = 1;
                printf("\n Cache found:\n");
                printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n", data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude, data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status, data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
                printf("\n");
                break; // Sai do loop depois de achar o codigo
            }
        }

        // Se não achar manda print
        if (!CacheFound)
        {
            printf("\nCache with code %s not found.\n", CodeToSearch);
        }
    }
}

//--------------------------  INICIO da Função EditCache ---------------------------//

// Função de validação de Status
int isValidStatus(const char *status)
{
    return (strcmp(status, "AVAILABLE") == 0 || strcmp(status, "DISABLED") == 0);
}

// Função de validação de Data
int isValidDateFormat(const char *date)
{
    int year, month, day; // Variaveis
    // Ira ler a data, separar por ano, mês e dia
    if (sscanf(date, "%d/%d/%d", &year, &month, &day) == 3)
    {
        if (year >= 1000 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
        {
            return 1; // Retorna o Valor 1 que indica que é valido
        }
    }
    return 0; // Retorna o Valor 0 que indica um formato invalido
}

// // Função de validação de Altitude
int isValidNumericInput(const char *input)
{
    int i = 0;

    while (input[i] != '\0')
    {
        //Verifica se o caractere não é um dígito, ponto decimal ou sinal negativo
        if (!isdigit(input[i]) && input[i] != '.' && input[i] != '-')
        {
            return 0; // Numero Invalido
        }
        i++;
    }
    return 1; // Numero Valido
}

//  Função EditCache
void EditCache(Data data[2000])
{
    // Verificar se existe alguma cache carregada
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

    // Variáveis
    char CodeToEdit[100];
    int CacheFound = 0; // Flag para verificação
    int choice;

    printf("Enter the code of the cache to edit:  ");
    scanf("%s", CodeToEdit);

    for (int i = 0; i < data[0].contador; i++)
    {
        if (strcmp(data[i].code, CodeToEdit) == 0)
        {
            // Cache encontrada, imprimir detalhes
            CacheFound = 1;
            printf("\nCache found:\n");
            printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n", data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude, data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status, data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
            printf("\n");

            do
            {
                printf("\n\nSelect the information to edit:\n");
                printf("1. Owner\n2. Status\n3. Hidden Date\n4. Altitude\n0. Exit\n");

                printf("Enter your choice: ");
                if (scanf("%d", &choice) != 1)
                {
                    // Limpa a memória do buffer de entrada no caso de uma variavel não inteira.
                    while (getchar() != '\n')
                        ;

                    printf("\n Invalid option! Enter a number.\n");
                    continue; // Reset no Loop
                }

                // Verificar a escolha do user e edita o campo correspondente
                switch (choice)
                {
                case 1:
                    printf("\n\n Current owner: %s", data[i].owner);
                    printf("\nEnter new owner: ");
                    scanf(" %99[^\n]", data[i].owner);
                    break;
                case 2:
                    printf("\n\n Current status: %s", data[i].status);
                    printf("\nEnter new status (AVAILABLE/DISABLED): ");
                    char newStatus[100];
                    scanf("%99s", newStatus);

                    if (!isValidStatus(newStatus))
                    {
                        printf("\nInvalid status! Please enter either 'AVAILABLE' or 'DISABLED'.\n");
                        continue; // Reset the loop
                    }

                    strcpy(data[i].status, newStatus);

                    break;
                case 3:
                    printf("\n\n Current Hidden_Date: %s", data[i].hidden_date);
                    printf("\nEnter new hidden date (YYYY/MM/DD): ");
                    char newHiddenDate[100]; // Variavel para Validação
                    scanf("%99s", newHiddenDate);

                    // Se o return for 0, ira dar erro
                    if (!isValidDateFormat(newHiddenDate))
                    {
                        printf("\nInvalid date format! Please use YYYY/MM/DD.\n");
                        continue; // Reseta o Loop
                    }

                    strcpy(data[i].hidden_date, newHiddenDate); // Troca a hidden_date para a newHiddenDate
                    break;

                case 4:
                    printf("\n\n Current altitude: %.0lf", data[i].altitude);
                    printf("\nEnter new altitude: ");
                    char newAltitude[100];
                    scanf("%99s", newAltitude);

                    if (!isValidNumericInput(newAltitude))
                    {
                        printf("\nInvalid input for altitude! Please enter a valid number.\n");
                        continue; // Reset the loop
                    }

                    data[i].altitude = atof(newAltitude);
                    break;
                case 0:
                    // Sai do Loop
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                }
            } while (choice != 0);

            printf("\n%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n", data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude, data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status, data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
            printf("\nCache information updated successfully.\n");

            break; // Sair do ciclo depois de editar a cache
        }
    }

    // Se a cache não for encontrada
    if (!CacheFound)
    {
        printf("\nCache with code %s not found.\n", CodeToEdit);
    }
}
//--------------------------  FIM da Função EditCache ---------------------------//

// Função CENTER
void Center(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

    // Variáveis
    double sumLatitudes = 0.0;
    double sumLongitudes = 0.0;
    int countCaches = 0;

    // Calcular a média das latitudes e longitudes
    for (int i = 0; i < data[0].contador; i++)
    {
        // Ignorar caches com altitudes desconhecidas
        if (data[i].altitude != -9999999)
        {
            sumLatitudes += data[i].latitude;
            sumLongitudes += data[i].longitude;
            countCaches++;
        }
    }

    // Calcular a média
    double avgLatitude = sumLatitudes / countCaches;
    double avgLongitude = sumLongitudes / countCaches;

    // Calcular o desvio padrão
    double sdLatitude = 0.0;
    double sdLongitude = 0.0;

    for (int i = 0; i < data[0].contador; i++)
    {
        // Ignorar caches com altitudes desconhecidas
        if (data[i].altitude != -9999999)
        {
            sdLatitude += pow(data[i].latitude - avgLatitude, 2);
            sdLongitude += pow(data[i].longitude - avgLongitude, 2);
        }
    }

    sdLatitude = sqrt(sdLatitude / countCaches);
    sdLongitude = sqrt(sdLongitude / countCaches);

    // Mostrar as estatísticas
    printf("\nStatistics for Caches with Known Altitudes:\n");
    printf("Average Latitude: %.7f\n", avgLatitude);
    printf("Latitude Standard Deviation: %.7f\n", sdLatitude);
    printf("Average Longitude: %.7f\n", avgLongitude);
    printf("Longitude Standard Deviation: %.7f\n", sdLongitude);
}

// Função para calcular a idade das caches
void CalculateCacheAge(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

    // Variáveis para armazenar as datas
    struct tm DataAntiga = {0};
    struct tm DataNova = {0};

    // Índices das caches mais antigas e mais recentes
    int AntigaDataLocalização = 0;
    int NovaDataLocalização = 0;

    // Inicializar as datas para comparação
    sscanf(data[0].hidden_date, "%4d/%2d/%2d", &DataAntiga.tm_year, &DataAntiga.tm_mon, &DataAntiga.tm_mday);
    sscanf(data[0].hidden_date, "%4d/%2d/%2d", &DataNova.tm_year, &DataNova.tm_mon, &DataNova.tm_mday);

    DataAntiga.tm_year -= 1900; // Ano é contado a partir de 1900 em struct tm
    DataAntiga.tm_mon--;        // Meses começam do zero

    DataNova.tm_year -= 1900; // Ano é contado a partir de 1900 em struct tm
    DataNova.tm_mon--;        // Meses começam do zero

    // Iterar sobre todas as caches para encontrar as datas mais antigas e mais recentes
    for (int i = 1; i < data[0].contador; i++)
    {
        struct tm DataAtual = {0};
        sscanf(data[i].hidden_date, "%4d/%2d/%2d", &DataAtual.tm_year, &DataAtual.tm_mon, &DataAtual.tm_mday);
        DataAtual.tm_year -= 1900; // Ano é contado a partir de 1900 em struct tm
        DataAtual.tm_mon--;        // Meses começam do zero

        // Comparar com a data mais antiga
        if (difftime(mktime(&DataAtual), mktime(&DataAntiga)) < 0)
        {
            DataAntiga = DataAtual;
            AntigaDataLocalização = i;
        }

        // Comparar com a data mais recente
        if (difftime(mktime(&DataAtual), mktime(&DataNova)) > 0)
        {
            DataNova = DataAtual;
            NovaDataLocalização = i;
        }
    }

    // Calcular a diferença em meses entre as datas
    int monthsDiff = (DataNova.tm_year - DataAntiga.tm_year) * 12 + DataNova.tm_mon - DataAntiga.tm_mon;

    // Imprimir os resultados
    printf("\nOldest Cache:\n");
    printf("Date: %04d/%02d/%02d\n", DataAntiga.tm_year + 1900, DataAntiga.tm_mon + 1, DataAntiga.tm_mday);
    printf("Cache Information:\n");
    printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n",
           data[AntigaDataLocalização].code, data[AntigaDataLocalização].name, data[AntigaDataLocalização].state, data[AntigaDataLocalização].owner,
           data[AntigaDataLocalização].latitude, data[AntigaDataLocalização].longitude, data[AntigaDataLocalização].kind, data[AntigaDataLocalização].size,
           data[AntigaDataLocalização].difficulty, data[AntigaDataLocalização].terrain, data[AntigaDataLocalização].status, data[AntigaDataLocalização].hidden_date,
           data[AntigaDataLocalização].founds, data[AntigaDataLocalização].not_founds, data[AntigaDataLocalização].favourites, data[AntigaDataLocalização].altitude);

    printf("\nNewest Cache:\n");
    printf("Date: %04d/%02d/%02d\n", DataNova.tm_year + 1900, DataNova.tm_mon + 1, DataNova.tm_mday);
    printf("Cache Information:\n");
    printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n",
           data[NovaDataLocalização].code, data[NovaDataLocalização].name, data[NovaDataLocalização].state, data[NovaDataLocalização].owner,
           data[NovaDataLocalização].latitude, data[NovaDataLocalização].longitude, data[NovaDataLocalização].kind, data[NovaDataLocalização].size,
           data[NovaDataLocalização].difficulty, data[NovaDataLocalização].terrain, data[NovaDataLocalização].status, data[NovaDataLocalização].hidden_date,
           data[NovaDataLocalização].founds, data[NovaDataLocalização].not_founds, data[NovaDataLocalização].favourites, data[NovaDataLocalização].altitude);

    printf("\nDifference in months: %d months\n", monthsDiff);
}

//------------------INICIO de funções SORT-------------------------------------//

void SortByAltitude(Data data[2000])
{
    // ContadorAlt Guarda os dados do contador, para que durante a troca de dados não existir perdas.
    int contadorAlt = data[0].contador;

    // Ordenação por bolha para ordenar as caches por altitude ( decrescente)
    for (int i = 0; i < contadorAlt - 1; i++)
    {
        // Atualizar o contadorAlt dentro do ciclo
        for (int j = 0; j < contadorAlt - i - 1; j++)
        {
            if (data[j].altitude < data[j + 1].altitude)
            {
                // Trocar de posição se a altitude for menor
                Data temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // Mostrar a lista ordenada por altitude
    printf("\nSorted Caches by Altitude (Descending):\n");
    printf("Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficuldade | Terrain | Status | Hidden Date | Founds | Not Founds | Favorites | Altitude\n\n");
    for (int i = 0; i < contadorAlt; i++)
    {
        printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n",
               data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude,
               data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status,
               data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
        printf("\n");
    }

    // Necessario pois a Troca de dados faz o contador se perder e invalida a o contador para 0
    data[0].contador = contadorAlt;
}

void SortByState(Data data[2000])
{

    // contadorState Guarda os dados do contador, para que durante a troca de dados não existir perdas.
    int contadorState = data[0].contador;

    // Bubble Sort para ordenar as caches por state (A-Z), e em caso de empate, por founds (decrescente)
    for (int i = 0; i < contadorState - 1; i++)
    {
        // Atualizar contadorState dentro do ciclo
        for (int j = 0; j < contadorState - i - 1; j++)
        {
            // Comparar strings de state através de strcmp
            int stateComparison = strcmp(data[j].state, data[j + 1].state);

            // Troca de posições se o state for maior ou se o founds for menor em caso de empate
            if (stateComparison > 0 || (stateComparison == 0 && data[j].founds < data[j + 1].founds))
            {
                Data temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // Mostrar a lista ordenada por state
    printf("\nSorted Caches by State (Ascending) and Found Counts (Descending):\n");
    printf("Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficulty | Terrain | Status | Hidden Date | Founds | Not Founds | Favorites | Altitude\n\n");
    for (int i = 0; i < contadorState; i++)
    {
        printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n",
               data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude,
               data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status,
               data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
        printf("\n");
    }

    // Necessario pois a Troca de dados faz o contador se perder e invalida a o contador para 0
    data[0].contador = contadorState;
}

void SortByDate(Data data[2000])
{

    // contadorDate Guarda os dados do contador, para que durante a troca de dados não existir perdas.
    int contadorDate = data[0].contador;

    // Bubble Sort para ordenar as caches por hidden_date ( decrescente)
    for (int i = 0; i < contadorDate - 1; i++)
    {
        // Atualizar contadorDate dentro do ciclo
        for (int j = 0; j < contadorDate - i - 1; j++)
        {
            // Comparar strings hidden_date através de strcmp
            if (strcmp(data[j].hidden_date, data[j + 1].hidden_date) < 0)
            {
                // Trocar posições se a data for mais recente
                Data temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // Mostrar a lista ordenada por hidden_date
    printf("\nSorted Caches by Hidden Date (Descending):\n");
    printf("Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficulty | Terrain | Status | Hidden Date | Founds | Not Founds | Favorites | Altitude\n\n");
    for (int i = 0; i < contadorDate; i++)
    {
        printf("%s | %s | %s | %s | %.7f | %.7f | %s | %s | %.1lf | %.1lf | %s | %s | %d | %d | %d | %.0lf \n",
               data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude,
               data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status,
               data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
        printf("\n");
    }

    // Necessario pois a Troca de dados faz o contador se perder e invalida a o contador para 0
    data[0].contador = contadorDate;
}

void MenuSort()
{
    printf("\nChoose a sorting method:\n");
    printf("1 - Sort by Altitude (Descending)\n");
    printf("2 - Sort by State (A-Z)\n");
    printf("3 - Sort by Hidden Date (Descending)\n");
    printf("0 - Go Back\n");
}

void Sort(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

    int choice;

    // Adiciona especiais Caracteres
    setlocale(LC_ALL, "Portuguese.utf8");

    // Do While que continua até receber Variavel diferente de 0
    do
    {

        MenuSort();
        printf("Enter your choice: ");

        // Enquanto não for um valor inteiro
        while (scanf("%d", &choice) != 1)
        {
            MenuSort();

            printf("\n \n Invalid input! Please enter a valid Option: ");
            // Limpa o Input
            while (getchar() != '\n')
                ;
        }

        // Menu é selecionado por Switch&Case
        switch (choice)
        {

        // SortByAltitude é o Case 1
        case 1:
            SortByAltitude(data);
            break;

        // SortByState é o Case 2
        case 2:
            SortByState(data);
            break;

        // SortByDate é o Case 3
        case 3:
            SortByDate(data);
            break;

        // Quit
        case 0:
            printf("\n See you soon! \n");
            break;

        // Error choice se for um numero inteiro errado
        default:
            printf("\n Invalid option! \n");
            break;
        }

    } while (choice != 0);
}

//------------------FIM de funções SORT-------------------------------------//

// Função STATEC
void STATEC(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

    // Variáveis para contar caches por distrito e status
    int nAtivos[500] = {0};
    int nDesativados[500] = {0};

    // Faz até ao numero de caches
    for (int i = 0; i < data[0].contador; i++)
    {
        // Verificar se o estado é válido
        if (strcmp(data[i].state, "") == 0)
        {
            printf("\nError: Cache at position %d has an empty state.\n", i);
            continue;
        }

        // Determina a posição correspondente ao distrito
        int PositionDistrict = -1;
        for (int t = 0; t < 500; t++)
        {
            if (strcmp(data[i].state, data[t].state) == 0)
            {
                PositionDistrict = t;
                break;
            }
        }

        if (PositionDistrict == -1)
        {
            printf("\nError: Cache at position %d has an invalid state.\n", i);
            continue;
        }

        // Aumenta a quantidade com base no status da cache se feita com sucesso
        if (strcmp(data[i].status, "AVAILABLE") == 0)
        {
            nAtivos[PositionDistrict]++;
        }
        else if (strcmp(data[i].status, "DISABLED") == 0)
        {
            nDesativados[PositionDistrict]++;
        }
        else
        {
            printf("\nError: Cache at position %d has an invalid status.\n", i);
        }
    }

    // Mostra a quantidade de Ativos e Desativos por Destrito
    printf("\n STATEC Report:\n");
    printf("District | Available Caches | Disabled Caches\n");
    for (int c = 0; c < 500; c++)
    {
        if (nAtivos[c] > 0 || nDesativados[c] > 0)
        {
            printf("%s | %d | %d\n", data[c].state, nAtivos[c], nDesativados[c]);
        }
    }
}

//  Função M81
void M81(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\n Doesn't exist a file loaded!\n");
        return;
    }

   // Matriz 81 para armazenar a contagem de caches para cada combinação de terreno/dificuldade
    int matriz81[9][9] = {0};

    // Percorre cada cache e atualizar a matriz
    for (int i = 0; i < data[0].contador; i++)
    {
        // Ajusta o terreno e a dificuldade para ficarem no intervalo 0-8
        int terrainIndex = (data[i].terrain - 1) * 2;
        int difficultyIndex = (data[i].difficulty - 1) * 2;

        // Aumenta a contagem para a combinação correspondente de terreno/dificuldade
        matriz81[difficultyIndex][terrainIndex]++;
    }

    // Print da matriz
    printf("\nMatriz 81:\n");
    printf("      ");

    // Dá print nos header
    for (double i = 1; i <= 5; i += 0.5)
    {
        printf("%-5.1lf", i);
    }
    printf("\n");

    // Print nas linhas da matriz 
    for (int i = 0; i < 9; i++)
    {
        // Print da linha do header (Valor do Terreno)
        printf("%-5.1lf", i * 0.5 + 1.0);

        // Print nos valores da matriz
        for (int j = 0; j < 9; j++)
        {
            printf("%-5d", matriz81[i][j]);
        }
        printf("\n");
    }
}

// Função de Save
int SaveFile(Data data[2000])
{
    if (data[0].contador == 0)
    {
        printf("\nNo data to save!\n");
        return 1;
    }

    char filename[50];
    printf("\nEnter the name of the file (without extension): ");
    scanf("%s", filename);

    // Adiciona o ".csv" para o nome do ficheiro
    strcat(filename, ".csv");

    // Abre o ficheiro para escrever
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file for writing\n");
        return 1;
    }

    // Print no Header do ficheiro
    fprintf(file, "Code;Name;State;Owner;Latitude;Longitude;Kind;Size;Difficulty;Terrain;Status;Hidden Date;Founds;Not Founds;Favorites;Altitude\n");

    // Print em cada Record para o ficheiro
    for (int i = 0; i < data[0].contador; i++)
    {
        fprintf(file, "%s;%s;%s;%s;%.7f;%.7f;%s;%s;%.1lf;%.1lf;%s;%s;%d;%d;%d;%.0lf\n",
                data[i].code, data[i].name, data[i].state, data[i].owner, data[i].latitude, data[i].longitude,
                data[i].kind, data[i].size, data[i].difficulty, data[i].terrain, data[i].status,
                data[i].hidden_date, data[i].founds, data[i].not_founds, data[i].favourites, data[i].altitude);
    }

    // Fecha o ficheiro
    fclose(file);

    printf("\nData saved to %s\n", filename);

    return 0;
}
