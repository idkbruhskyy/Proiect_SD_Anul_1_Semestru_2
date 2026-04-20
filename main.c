#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                    ///TASK 1////

typedef struct Player{
    char firstName[50];
    char secondName[50]; // Player struct
    int points;
    struct Player* next;
}Player;

typedef struct Team{
    char name[100];
    int playerCount;
    int scoreSum;
    struct Player* players; // Team struct
    struct Team* next;
}Team;

Team* eliminate(Team* head){
    int minSum = 99999;
    int minCount = 1;
    Team* minTeam = NULL;
    Team* current = head;
    Team* prev = NULL;
    Team* minPrev = NULL;

    while (current != NULL){
        // Compara a/b < c/d as a*d < c*b
        if (current->scoreSum * minCount < minSum * current->playerCount){
            minTeam = current;
            minSum = current->scoreSum;
            minCount = current->playerCount;
            minPrev = prev;
        }
        prev = current;
        current = current->next;
    }
    if (minTeam == head)
        head = head->next;
    else
        minPrev->next = minTeam->next;
    free(minTeam);
    return head;
}

Team* LlRead(FILE* dFile){ // Linked List Read function
    Team* head = NULL;
    Team* tail = NULL;
    int n;
    fscanf(dFile, "%d", &n);

    for (int i=0;i<n;i++){
        Team* newTeam = (Team*)malloc(sizeof(Team));
        newTeam->next = NULL;
        fscanf(dFile, "%d", &newTeam->playerCount);
        fscanf(dFile, " %[^\n]", newTeam->name);

        // Scoate spatiul de la final pentru anumite echipe
        int len = strlen(newTeam->name);
        while(len > 0 && newTeam->name[len-1] == ' '){
            newTeam->name[len-1] = '\0';
            len--;
        }

        Player* playerHead = NULL;
        Player* playerTail = NULL;

        for (int j=0;j<newTeam->playerCount;j++){
            Player* newPlayer = (Player*)malloc(sizeof(Player));
            newPlayer->next = NULL;
            fscanf(dFile, "%s", newPlayer->firstName);
            fscanf(dFile, "%s", newPlayer->secondName);
            fscanf(dFile, "%d", &newPlayer->points);

            if (playerHead == NULL){
                playerHead = newPlayer;
                playerTail = newPlayer;
            }
            else{
                playerTail->next = newPlayer;
                playerTail = newPlayer;
            }
        }
        newTeam->players = playerHead;

        if (head == NULL){
            head = newTeam;
            tail = newTeam;
        }
        else{
            tail->next = newTeam;
            tail = newTeam;
        }
    }
    return head;
}

int isPowerOf2(int n){
    return (n==1 || n==2 || n==4 || n==8 || n==16 || n==32 || n==64 || n==128 || n==256 || n==512);
}

int main(int argc, char* argv[]){
    FILE* cFile = fopen(argv[1], "r");
    FILE* dFile = fopen(argv[2], "r");   // Deschidere fisiere pentru citire scriere
    FILE* outputFile = fopen(argv[3], "w");
    int count = 0;

    if (!cFile || !dFile || !outputFile){
        printf("Eroare la citirea fisierelor !"); // Check if file = NULL
        return 1;
    }

    Team* teamHead = LlRead(dFile); // LlRead din fisiere
    Team* current = teamHead;

    // Calculare suma scor pt fiecare echipa
    while(current != NULL){
        int sum = 0;
        Player* currentPlayer = current->players;
        while(currentPlayer != NULL){
            sum += currentPlayer->points;
            currentPlayer = currentPlayer->next;
        }
        current->scoreSum = sum;
        count++;
        current = current->next;
    }

    // Inversare lista inainte de afisare
    Team* prev = NULL;
    current = teamHead;
    Team* next = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    teamHead = prev;

    // Eliminare a echipelor cu scor mic pana la un numar total de echipa = cu o putere a lui 2
    while(!isPowerOf2(count)){
        teamHead = eliminate(teamHead);
        count--;
    }

    // Scrie restul de echipe in outputFile
    current = teamHead;
    while(current != NULL){
        fprintf(outputFile, "%s\n", current->name);
        current = current->next;
    }

    // Inchidere fisiere
    fclose(cFile);
    fclose(dFile);
    fclose(outputFile);
    return 0;
}