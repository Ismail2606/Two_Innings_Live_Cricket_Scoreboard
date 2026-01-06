/*
 * Project: Two-Innings Live Cricket Scoreboard
 * Author: Ismail Pasha (2025)
 */

#include "scoreboard.h"

void playInnings(Innings *batting, Innings *bowling, int totalOvers, int target) {
    int striker = 0, nonStriker = 1, nextBatsman = 2;
    char bowlerName[30];
    int bowlerIndex = -1;
    batting->totalRuns = batting->wickets = batting->oversDone = batting->ballsInOver = 0;

    printf("\n%s batting — %s bowling\n", batting->teamName, bowling->teamName);
    if (target > 0) {
        printf("Target to chase: %d Runs\n\n", target);
    } else {
        printf("First innings: Set the target\n\n");
    }


    while (batting->oversDone < totalOvers && batting->wickets < 10) {
        // ask bowler at start of over
        if (batting->ballsInOver == 0) {
            printf("\nOver %d begins. Enter bowler name: ", batting->oversDone + 1);
            scanf(" %[^\n]", bowlerName); 
            bowlerIndex = findBowler(bowling, bowlerName);
            
            if (bowlerIndex == -1) {
                printf("Invalid bowler name! Try again.\n");
                continue;
            }
        }


        displayLive(batting, striker, nonStriker, &bowling->bowlers[bowlerIndex]);

        int runs;
        scanf("%d", &runs);
        getchar();

        if (runs == -1) {
            printf("%s is OUT!\n", batting->batsmen[striker].name);
            batting->batsmen[striker].out = 1;
            batting->wickets++;
            bowling->bowlers[bowlerIndex].wickets++;
            bowling->bowlers[bowlerIndex].balls++;
            if (nextBatsman < MAX_PLAYERS)
                striker = nextBatsman++;
            else
                break;
        } else {
            batting->batsmen[striker].runs += runs;
            batting->batsmen[striker].balls++;
            if (runs == 4) 
            batting->batsmen[striker].fours++;
            if (runs == 6) 
            batting->batsmen[striker].sixes++;
            
            batting->totalRuns += runs;
            bowling->bowlers[bowlerIndex].runs_conceded += runs;
            bowling->bowlers[bowlerIndex].balls++;

            if (runs % 2 == 1) {
                int tmp = striker;
                striker = nonStriker;
                nonStriker = tmp;
            }
        }

        batting->ballsInOver++;
        if (batting->ballsInOver == 6) {
            batting->oversDone++;
            batting->ballsInOver = 0;
            bowling->bowlers[bowlerIndex].overs++;
            bowling->bowlers[bowlerIndex].balls = 0;

            int tmp = striker;
            striker = nonStriker;
            nonStriker = tmp;
        }

        // if chasing
        if (target > 0 && batting->totalRuns > target) 
        break;
    }
}

void displayLive(Innings *inn, int striker, int nonStriker, Bowler *bowler) {
    clearScreen();
    printf("=====================================\n");
    printf("   LIVE SCOREBOARD: %s Innings\n", inn->teamName);
    printf("=====================================\n");
    printf("Score: %d/%d in %d.%d overs\n", inn->totalRuns, inn->wickets, inn->oversDone, inn->ballsInOver);
    printf("-------------------------------------\n");
    printf("Batsman\t\tR(B)\t4s\t6s\n");
    printf("-------------------------------------\n");
    printf("%-12s\t%d(%d)\t%d\t%d%s\n",
           inn->batsmen[striker].name,
           inn->batsmen[striker].runs, inn->batsmen[striker].balls,
           inn->batsmen[striker].fours, inn->batsmen[striker].sixes,
           inn->batsmen[striker].out ? " (OUT)" : "");
    printf("%-12s\t%d(%d)\t%d\t%d%s\n",
           inn->batsmen[nonStriker].name,
           inn->batsmen[nonStriker].runs, inn->batsmen[nonStriker].balls,
           inn->batsmen[nonStriker].fours, inn->batsmen[nonStriker].sixes,
           inn->batsmen[nonStriker].out ? " (OUT)" : "");
    printf("-------------------------------------\n");
    printf("Current Bowler: %s | O: %d.%d  R: %d  W: %d\n",
           bowler->name, bowler->overs, bowler->balls, bowler->runs_conceded, bowler->wickets);
    printf("-------------------------------------\n");
    printf("Enter runs (0–6) or -1 for WICKET:\n");
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int findBowler(Innings *opp, char *bowlerName) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (strcmp(opp->batsmen[i].name, bowlerName) == 0) {
            for (int j = 0; j < MAX_PLAYERS; j++) {
                if (strcmp(opp->bowlers[j].name, bowlerName) == 0)
                    return j; // already existing bowler
            }
            // new bowler
            for (int j = 0; j < MAX_PLAYERS; j++) {
                if (strlen(opp->bowlers[j].name) == 0) {
                    strcpy(opp->bowlers[j].name, bowlerName);
                    opp->bowlers[j].overs = opp->bowlers[j].balls = opp->bowlers[j].runs_conceded = opp->bowlers[j].wickets = 0;
                    return j;
                }
            }
        }
    }
    return -1; // not found
}


void saveToFile(Innings *A, Innings *B, int totalOvers) {
    FILE *fp = fopen("scoreboard.txt", "w");
    if (!fp) {
        printf("Error writing to file.\n");
        return;
    }

    Innings *teams[2] = {A, B};
    for (int t = 0; t < 2; t++) {
        fprintf(fp, "===============================\n");
        fprintf(fp, "%s Innings: %d/%d in %d.%d overs\n",
                teams[t]->teamName, teams[t]->totalRuns, teams[t]->wickets,
                teams[t]->oversDone, teams[t]->ballsInOver);
        fprintf(fp, "===============================\n");
        fprintf(fp, "Batsman\t\t\tR(B)\t4s\t6s\tStatus\n");
        fprintf(fp, "---------------------------------------\n");
        for (int i = 0; i < MAX_PLAYERS; i++) {
            fprintf(fp, "%-12s\t%d(%d)\t%d\t%d\t%s\n",
                    teams[t]->batsmen[i].name,
                    teams[t]->batsmen[i].runs,
                    teams[t]->batsmen[i].balls,
                    teams[t]->batsmen[i].fours,
                    teams[t]->batsmen[i].sixes,
                    teams[t]->batsmen[i].out ? "OUT" : "NOT OUT");
        }
        fprintf(fp, "\nBowler\t\t\tO\tR\tW\n");
        fprintf(fp, "---------------------------------------\n");
        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (strlen(teams[1 - t]->bowlers[i].name) > 0)
                fprintf(fp, "%-12s\t%d\t%d\t%d\n",
                        teams[1 - t]->bowlers[i].name,
                        teams[1 - t]->bowlers[i].overs,
                        teams[1 - t]->bowlers[i].runs_conceded,
                        teams[1 - t]->bowlers[i].wickets);
        }
        fprintf(fp, "\n");
    }

    // Result
    if (A->totalRuns > B->totalRuns)
        fprintf(fp, "Result: %s won by %d runs.\n", A->teamName, A->totalRuns - B->totalRuns);
    else if (B->totalRuns > A->totalRuns)
        fprintf(fp, "Result: %s won by %d wickets.\n", B->teamName, 10 - B->wickets);
    else
        fprintf(fp, "Result: Match tied.\n");

    fclose(fp);
    printf("\n---Match result saved to scoreboard.txt---\n\n");
}

