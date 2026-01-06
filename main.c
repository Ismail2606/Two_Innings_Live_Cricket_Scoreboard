/*
Project: Two innings live cricket scoreboard
Author: Ismail Pasha
 */ 
#include "scoreboard.h"

int main() {
    Innings teamA, teamB;
    int totalOvers;

    printf("Enter total overs: ");
    scanf("%d", &totalOvers);
    getchar();

    printf("Enter Team A name: ");
    scanf(" %[^\n]", teamA.teamName);

    printf("Enter Team B name: ");
    scanf(" %[^\n]", teamB.teamName);

    // Enter both teams’ players at once
    printf("\nEnter players for %s:\n", teamA.teamName);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        scanf(" %[^\n]", teamA.batsmen[i].name);  

        teamA.batsmen[i].runs = teamA.batsmen[i].balls = teamA.batsmen[i].fours =
        teamA.batsmen[i].sixes = teamA.batsmen[i].out = 0;
    }


    printf("\nEnter players for %s:\n", teamB.teamName);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        scanf(" %[^\n]", teamB.batsmen[i].name);  

        teamB.batsmen[i].runs = teamB.batsmen[i].balls = teamB.batsmen[i].fours =
        teamB.batsmen[i].sixes = teamB.batsmen[i].out = 0;
    }

    // Initialize team stats
    for (int i = 0; i < MAX_PLAYERS; i++) {
        teamA.bowlers[i].name[0] = '\0';
        teamA.bowlers[i].overs = 0;
        teamA.bowlers[i].balls = 0;
        teamA.bowlers[i].runs_conceded = 0;
        teamA.bowlers[i].wickets = 0;

        teamB.bowlers[i].name[0] = '\0';
        teamB.bowlers[i].overs = 0;
        teamB.bowlers[i].balls = 0;
        teamB.bowlers[i].runs_conceded = 0;
        teamB.bowlers[i].wickets = 0;
    }


    // Innings 1
    printf("\n--- %s Innings ---\n", teamA.teamName);
    playInnings(&teamA, &teamB, totalOvers, 0);

    // Innings 2
    printf("\n--- %s Innings ---\n", teamB.teamName);
    playInnings(&teamB, &teamA, totalOvers, teamA.totalRuns);

    saveToFile(&teamA, &teamB, totalOvers);
    return 0;
}
