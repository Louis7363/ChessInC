#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void afficher_echequier(char* chess[8][8]) {
    for (int i = 0; i < 8; i++) {
        printf("%d| ",8-i);
        for (int j = 0; j < 8; j++) {
            printf("%s  ",chess[i][j]);
        }
        printf("\n");
    }
    printf("   _  _  _  _  _  _  _  _\n");
    printf("   A  B  C  D  E  F  G  H");
}

int* convertisseur_case(char position[2]) {
    int * coord = malloc(2*sizeof(int));
    coord[0] = 8-(position[1] - '0');
    char lettre[8] = "ABCDEFGH";
    for (int i=0; i<8;i++) {
        if (position[0] == lettre[i]) {
            coord[1] = i;
            return coord;
        }

    }

}

bool tour(int chess[8][8], int * depart,int * arrive) {
    if (depart[0] == arrive[0]) {
        bool avant = depart[1]<arrive[1];
        int incr = 1;
        if (!avant)
            incr = -1;
        for (int i=depart[1]+incr;i!=arrive[1];i+=incr) {
            if (chess[depart[0]][i] != 0)
                return false;

        }

        return true;
    }
    else if (depart[1]==arrive[1]) {
        bool avant = depart[0]<arrive[0];
        int incr = 1;
        if (!avant)
            incr = -1;
        for (int i=depart[0]+incr;i!=arrive[0];i+=incr) {
            if (chess[i][depart[1]] != 0) {
                return false;
            }
        }
        return true;
    }
    else
        return false;

}
bool fou(int chess[8][8], int * depart,int * arrive) {
    int n = abs(arrive[0] - depart[0]);
    int n2 = abs(arrive[1]-depart[1]);
    int s1=0;
    int s2=0;
    if (arrive[0] - depart[0]<0)
        s1 = -1;
    else
        s1 = 1;
    if (arrive[1] - depart[1]<0)
        s2 = -1;
    else
        s2 = 1;

    if (n == n2 ) {
        for (int i = 1;i < n; i += 1) {
            if (chess[depart[0] + i*s1][depart[1] + i*s2] != 0)
                return false;

        }
        return true;
    }

    return false;
}

bool is_movement_possible (int chess[8][8], int * depart,int * arrive) {
    // ################ TOUR #################
    if (chess[arrive[0]][arrive[1]] >0) {
        return false;
    }

    if (chess[depart[0]][depart[1]] == 4) {

        return(tour( chess,  depart, arrive));
    }

        //################### FIN TOUR ##################
        //################### PION ######################
        if (chess[depart[0]][depart[1]] == 1) {

            if (depart[1] == arrive[1]) {
                int nbCases = depart[0]-arrive[0];
                if (nbCases==1 && chess[arrive[0]][arrive[1]] == 0) {
                    return true;
                }
                else if (nbCases==2 && depart[0]==6 && chess[arrive[0]][arrive[1]] == 0 && chess[arrive[0]+1][arrive[1]] == 0) {
                    return true;
                }
                else
                    return false;
            }
            else if (arrive[0] == depart[0]-1 && (arrive[1] == depart[1]-1 || arrive[1] == depart[1]+1 ) && chess[arrive[0]][arrive[1]]<0) {
                return true;
            }
            else
                return false;
        }

        //##################FIN PION############################
        //################### FOU ##############################
        if (chess[depart[0]][depart[1]] == 3) {

            return(fou( chess,  depart, arrive));

        }

        //################ FIN FOU ###################
        //################ DAME #####################
        if (chess[depart[0]][depart[1]] == 5) {
            return(fou( chess,  depart, arrive) || (tour( chess,  depart, arrive)));
        }
    //############### CAVALIER ##################
        if (chess[depart[0]][depart[1]] == 2 ) {
            if (((abs(depart[0] - arrive[0]) == 2B) && (abs(depart[1] - arrive[1]) == 1)) || ((abs(depart[0] - arrive[0]) == 1) && (abs(depart[1] - arrive[1]) == 2)) )
                return true;
            return false;
        }
    }



int main(void) {
    // pion : 1, cavalier : 2, fou : 3, tour : 4, dame: 5, roi : 6

    // ######## INITIALISATION ###########
    int chess[8][8] = {
        {-4,-2,-3,-5,-6,-3,-2,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {4,2,3,5,6,3,2,4}
    };
    const char* chessVisual[8][8] = {
        {"♖","♘","♗","♕","♔","♗","♘","♖"},
        {"♙","♙","♙","♙","♙","♙","♙","♙"},
        {".",".",".",".",".",".",".","."},
        {".",".",".",".",".",".",".","."},
        {".",".",".",".",".",".",".","."},
        {".",".",".",".",".",".",".","."},
        {"♟","♟","♟","♟","♟","♟","♟","♟"},
        {"♜","♞","♝","♛","♚","♝","♞","♜"},

    };
    afficher_echequier(chessVisual);
    while (true) {
    char piece_a_jouer[2];
    char arrive[2];

        printf("\n Quelle piece souhaitez vous jouer ?");
        scanf(" %c%c",&piece_a_jouer[0],&piece_a_jouer[1]);

        int * coordDep = convertisseur_case(piece_a_jouer);
        printf("\n En quelle position souhaitez vous mettre la pièce ?");
        scanf(" %c%c",&arrive[0],&arrive[1]);
        int * coordArr = convertisseur_case(arrive);
        bool possible = is_movement_possible(chess,coordDep,coordArr);
        //printf("%d,%d",coordDep[0],coordDep[1]);
        //printf("mouvement possible : %d",possible);
            if (possible) {
                chess[coordArr[0]][coordArr[1]]=chess[coordDep[0]][coordDep[1]];
                chessVisual[coordArr[0]][coordArr[1]]=chessVisual[coordDep[0]][coordDep[1]];
                chess[coordDep[0]][coordDep[1]] = 0;
                chessVisual[coordDep[0]][coordDep[1]] = ".";
            }
        system("clear");
        afficher_echequier(chessVisual);


        // ############# LIBERATION MEMOIRE####################
        free(coordDep);
        free(coordArr);
    }
    return 0;
}