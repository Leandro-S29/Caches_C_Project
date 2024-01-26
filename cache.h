#ifndef CACHE_H
#define CACHE_H

// Definição da struct
typedef struct Data
{
    char code[100];
    char name[200];
    char state[100];
    char owner[200];
    double latitude;
    double longitude;
    char kind[50];
    char size[50];
    double difficulty;
    double terrain;
    char status[50];
    char hidden_date[50];
    int founds;
    int not_founds;
    int favourites;
    double altitude;
    int contador;
} Data;

// Inicialização das funções
int LoadFile(Data data[2000], char ficheiro[50]);
void List(Data data[2000]);
void ClearMemory(Data data[2000]);
void QUIT();
void FoundP(Data data[2000]);
void Search(Data data[2000]);
void EditCache(Data data[2000]);
void Center(Data data[2000]);
void CalculateCacheAge(Data data[2000]);
void Sort(Data data[2000]);
void STATEC(Data data[2000]);
void M81(Data data[2000]);
int SaveFile(Data data[2000]);

#endif