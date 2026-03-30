#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct Player{
        char firstName[50];
        char secondName[50]; //Player struct
        int points;
        struct Player* next;
    }Player;



    typedef struct Team{
        char name[100];
        int playerCount;
        float score;
        struct Player* players;  //Team struct
        struct Team* next;
    }Team;
    


    Team* LlRead(FILE* dFile){   //Linked Lists Read function
        Team* head = NULL;
        Team* tail = NULL;
   
        int n;
        fscanf(dFile, "%d", &n);
        
        for (int i=0;i<n;i++){
            Team* newTeam = (Team*)malloc(sizeof(Team));
            newTeam->next = NULL;
            fscanf(dFile, "%d", &newTeam->playerCount);
            fscanf(dFile, " %[^\n]", newTeam->name);     
        
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

    
int main(int argc, char* argv[]){
    FILE* cFile = fopen(argv[1], "r");
    FILE* dFile = fopen(argv[2], "r");   //Deschidere fisiere c,d citire output scriere
    FILE* outputFile = fopen(argv[3], "w");

    if (!cFile || !dFile || !outputFile){
        printf("Eroare la citirea fisierelor !"); //Check if file = NULL
        return 1;
    }

    Team* teamHead = LlRead(dFile);  //citire fisier

    fclose(cFile);
    fclose(dFile);   ///Inchidere fisiere
    fclose(outputFile);

    return 0;
}