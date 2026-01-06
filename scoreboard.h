#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 11

typedef struct {
    char name[30];
    int runs, balls, fours, sixes;
    int out; // 0 = not out, 1 = out
} Batsman;

typedef struct {
    char name[30];
    int overs, balls;
    int runs_conceded, wickets;
} Bowler;

typedef struct {
    char teamName[30];
    Batsman batsmen[MAX_PLAYERS];
    Bowler bowlers[MAX_PLAYERS];
    int totalRuns, wickets, oversDone, ballsInOver;
} Innings;


/* Prototypes */
void playInnings(Innings *batting, Innings *bowling, int totalOvers, int target);
void displayLive(Innings *inn, int striker, int nonStriker, Bowler *bowler);
int findBowler(Innings *opp, char *bowlerName);
void saveToFile(Innings *A, Innings *B, int totalOvers);
void clearScreen();
#endif // SCOREBOARD_H