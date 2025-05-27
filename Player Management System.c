#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    int jerseyNumber;               
    char name[50];                      
    int runs;
    int wickets;
    int matches;
} Player;

void hardcodePlayers();
void addPlayer();
void removePlayer();
void searchPlayer();
void updatePlayer();
void displayAllPlayers();
void displayTopPlayers();

Player* players = NULL;
int playerCount = 0;
int capacity = 5;

int main() {
    int choice;

    players = (Player *)malloc(capacity * sizeof(Player));
   
    hardcodePlayers();

    while (1) {
        printf("\n--------------------_|||_ WelCome To Player Management System _|||_--------------------\n");
        printf("\n");
        printf("1. Add Player\n");
        printf("2. Remove Player\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Display All Players\n");
        printf("6. Display Top 3 Players\n");
        printf("7. Exit\n");
        
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPlayer(); 
            break;
            case 2: removePlayer(); 
            break;
            case 3: searchPlayer(); 
            break;
            case 4: updatePlayer(); 
            break;
            case 5: displayAllPlayers(); 
            break;
            case 6: displayTopPlayers(); 
            break;
            case 7: free(players); 
                printf("Exiting program...\n"); 
                return 0;
                
            default: 
                printf("Invalid Choice! Please Try Again.\n");
        }
    }
}

void hardcodePlayers() {
    Player defaultPlayers[] = {
        {7, "Virat Kohli", 12000, 4, 254},
        {18, "MS Dhoni", 10500, 200, 350},
        {45, "Rohit Sharma", 9800, 8, 220},
        {10, "Sachin Tendulkar", 18426, 154, 463},
        {33, "Jasprit Bumrah", 300, 200, 90}
    };

    for (int i = 0; i < 5; i++) {
        if (playerCount >= capacity) {
            capacity = capacity * 2;
            players = (Player *)realloc(players, capacity * sizeof(Player));
        }
        players[playerCount++] = defaultPlayers[i];
    }
}

void addPlayer() {
    if (playerCount >= capacity) {
        capacity = capacity * 2;
        players = (Player*)realloc(players, capacity * sizeof(Player));
    }

    printf("Enter Jersey Number: ");
    scanf("%d", &players[playerCount].jerseyNumber);
    getchar(); 

    printf("Enter Player Name: ");
    scanf(" %s", players[playerCount].name);

    printf("Enter Runs: ");
    scanf("%d", &players[playerCount].runs);

    printf("Enter Wickets: ");
    scanf("%d", &players[playerCount].wickets);

    printf("Enter Matches Played: ");
    scanf("%d", &players[playerCount].matches);

    playerCount++;
    
    printf("Player added successfully!\n");
}

void removePlayer() {

    int jerseyNumber, i, found = 0;
    
    printf("Enter Jersey Number to remove: ");
    scanf("%d", &jerseyNumber);

    for (i = 0; i < playerCount; i++) {
        if (players[i].jerseyNumber == jerseyNumber) {
            found = 1;
            for (int j = i; j < playerCount - 1; j++) {
                players[j] = players[j + 1];
            }
            
            playerCount--;
            printf("Player removed successfully!\n");
            return;
        }
    }
    if (!found) {
        printf("Player not found!\n");
    }
}

void searchPlayer() {
    int jerseyNumber, found = 0;
    
    printf("Enter Jersey Number to search: ");
    scanf("%d", &jerseyNumber);

    for (int i = 0; i < playerCount; i++) {
        if (players[i].jerseyNumber == jerseyNumber) {
            printf("Found: %s | Runs: %d | Wickets: %d | Matches: %d\n", players[i].name, players[i].runs, players[i].wickets, players[i].matches);
            found = 1;
            break;
        }
    }
    if (!found) printf("Player not found!\n");
}

void updatePlayer() {
    int jerseyNumber, found = 0;
    printf("Enter Jersey Number to update: ");
    scanf("%d", &jerseyNumber);

    for (int i = 0; i < playerCount; i++) {
        if (players[i].jerseyNumber == jerseyNumber) {
            printf("Enter New Runs: ");
            scanf("%d", &players[i].runs);
            
            printf("Enter New Wickets: ");
            scanf("%d", &players[i].wickets);
            
            printf("Enter New Matches Played: ");
            scanf("%d", &players[i].matches);

            printf("Player updated successfully!\n");
            
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Player not found!\n");
    }
}

void displayAllPlayers() {
    
    printf("\n------------------------------------------------------------------------\n");
    printf("| %-12s | %-20s | %-8s | %-8s | %-8s |\n", "Jersey No", "Name", "Runs", "Wickets", "Matches");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < playerCount; i++) {
        printf("| %-12d | %-20s | %-8d | %-8d | %-8d |\n",players[i].jerseyNumber, players[i].name, players[i].runs, players[i].wickets, players[i].matches);
    }
    printf("------------------------------------------------------------------------\n");
}

void displayTopPlayers() {

    Player *sortedPlayers = (Player *)malloc(playerCount * sizeof(Player));
    
    memcpy(sortedPlayers, players, playerCount * sizeof(Player));

    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = 0; j < playerCount - i - 1; j++) {
            if (sortedPlayers[j].runs < sortedPlayers[j + 1].runs) {
                Player temp = sortedPlayers[j];
                sortedPlayers[j] = sortedPlayers[j + 1];
                sortedPlayers[j + 1] = temp;
            }
        }
    }

    int topCount = playerCount < 3 ? playerCount : 3;

    printf("\n--------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s |\n", "Name", "Runs", "Matches");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < topCount; i++) {
        printf("| %-20s | %-10d | %-10d |\n",sortedPlayers[i].name, sortedPlayers[i].runs, sortedPlayers[i].matches);
    }
    printf("--------------------------------------------------------\n");

    free(sortedPlayers);
}