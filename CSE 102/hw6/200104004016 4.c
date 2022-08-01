#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 15
#define COLUMN 30 

void fillMap(char board[][COLUMN]);
void printMap(char map[ROW][COLUMN],int player1_X, int player1_Y, int player2_X, int player2_Y);
int dice();
int startGame();
int player1_X( int x, int y, int dice);
int player1_Y( int x, int y, int dice);
int player2_X( int x, int y, int dice);
int player2_Y( int x, int y, int dice);
int p1won(int x, int y, int dice);
int p2won(int x, int y, int dice);

int main()
{
    // Required variables.
    char board[ROW][COLUMN];
    fillMap(board);
    
    // Coordinate values for p1 and p2
    int p1x=1;
    int p1y=1;
    int p2x=3;
    int p2y=3;
    int diceValue;
    
    // Temporary storage for p1 and p2 coordinates (more on this on line 49-50)
    int p1xreserved;
    int p1yreserved;
    int p2xreserved;
    int p2yreserved;
    
    // To check if p1 or p2 has won the game.
    int isP1;
    int isP2;
    
    // Turn of move.
    int rightOfMove;

    rightOfMove = startGame(); // As we start the game, we run the startGame function to decide which player will be starting first.

    printMap(board,p1x,p1y,p2x,p2y); // Prints starting map.

    while(1){
        fillMap(board); // clears the array from the players every round by filling it with it's first form.
        if(rightOfMove==1){
        printf("PLAYER 1... press ENTER to dice...\nDICE: ");
        diceValue = dice();
        getchar();
        printf("%d\n",diceValue);
        p1xreserved = p1x; // As the p1x change before p1y, program stores the locations from the previous tour on variables called p1reserved and p2reserved
        p1yreserved = p1y; // to prevent the p1y/p2y values to be affected from the change in p1x/p2x values.

        p1x = player1_X(p1xreserved,p1yreserved,diceValue);
        p1y = player1_Y(p1xreserved,p1yreserved,diceValue);
        isP1 = p1won(p1xreserved,p1yreserved,diceValue);
        //printMap(board,p1x,p1y,p2x,p2y);
        rightOfMove++; // Gives the right of move to player 2
        }

        if(rightOfMove==2){
        printf("PLAYER 2... press ENTER to dice...\nDICE: ");
        diceValue = dice();
        getchar();
        printf("%d\n",diceValue);
        p2xreserved = p2x; // As the p2x change before p2y, program stores the locations from the previous tour on variables called p1reserved and p2reserved
        p2yreserved = p2y; // to prevent the p1y/p2y values to be affected from the change in p1x/p2x values.

        p2x = player2_X(p2xreserved,p2yreserved,diceValue);
        p2y = player2_Y(p2xreserved,p2yreserved,diceValue);
        isP2 = p2won(p2xreserved,p2yreserved,diceValue);
        rightOfMove--; // Gives the right of move to player 1
        }

        printMap(board,p1x,p1y,p2x,p2y);

        //printf("p1x:%d\tp1y:%d\np2x:%d\tp2y:%d\n",p1x,p1y,p2x,p2y);
        if(isP1 == 1){
            printf("Player 1 has won.\n");
            exit(0);
        }else if(isP2 == 1){
            printf("Player 2 has won.\n");
            exit(0);
        }


    }



    printf("x of p1 is: %d\n",player1_X(p1x,p1y,dice()));
    printf("y of p1 is: %d\n",player1_Y(p1x,p1y,dice()));

    startGame();

    return 0;
}

int player1_X( int x, int y, int dice){
/*
This function gets the current coordinates and the dice value of player 1, and increase-decrease it's x and y coordinate
values according to the location of the player(for example, it increase the x value if the player is on the top road, or
decreases the x value if it's on bottom road, and it does the similar for the left and right roads.)

*/
int counter;
counter = dice;

while(counter > 0){

    if(y==1 && x<28){ // top road
        x++;
        counter--;
    }else if(x==28 && y<13){ // right road
        y++;
        counter--;
    }else if(y==13 && x>1){ // bottom road
        x--;
        counter--;
    }else if(x==1 && y>1){  // left road
        y--;
        counter--;
    }

}

// Checks if the player stops on a penalty point (since this function is for returning x, it doesnt interfere with the)
// situations where the y value needs to be changed as it hit a penalty point.
if((y==1&&x==14)){
    printf("Penalty for player 1\n");
    x = x-2;
}else if(y==13 && x==14){
    printf("Penalty for player 1.\n");
    x = x+2;
}

// After required changes, return the x value.
return x;

}

int player1_Y( int x, int y, int dice){
/*
This function gets the current coordinates and the dice value of player 1, and increase-decrease it's x and y coordinate
values according to the location of the player(for example, it increase the x value if the player is on the top road, or
decreases the x value if it's on bottom road, and it does the similar for the left and right roads.)

*/
// The counter variable means the dice value.
int counter;
int i,j;
counter = dice;

while(counter > 0){

    if(y==1 && x<28){ // top road
        x++;
        counter--;
    }else if(x==28 && y<13){ // right road
        y++;
        counter--;
    }else if(y==13 && x>1){ // bottom road
        x--;
        counter--;
    }else if(x==1 && y>1){ // left road
        y--;
        counter--;
    }

}

// Checks if the player stops on a penalty point (since this function is for returning y, it doesnt interfere with the)
// situations where the x value needs to be changed as it hit a penalty point.
if(y==7&&x==28){
    printf("Penalty for player 1.\n");
    y = y-2;
}

// After required changes, return the y value.
return y;

}

int player2_X(int x, int y, int dice){
/*
This function gets the current coordinates and the dice value of player 2, and increase-decrease it's x and y coordinate
values according to the location of the player(for example, it increase the x value if the player is on the top road, or
decreases the x value if it's on bottom road, and it does the similar for the left and right roads.)

*/
int counter;
counter = dice;

while(counter > 0){
//counter=0 // y=3 // x=26
    if(y==3 && x<26){ // top road
        x++;
        counter--;
    }else if(x==26 && y<11){ // right road
        y++;
        counter--;
    }else if(y==11 && x>3){ // bottom road
        x--;
        counter--;
    }else if(x==3 && y>3){ // left road
        y--;
        counter--;
    }
}

// Checks if the player stops on a penalty point (since this function is for returning x, it doesnt interfere with the)
// situations where the y value needs to be changed as it hit a penalty point.
if((y==3&&x==10) || (y==3 && x==18)){
    printf("Penalty for player 2.\n");
    x = x-2;
}else if((y==11&&x==10) || (y==11&&x==18)){
    printf("Penalty for player 2.\n");
    x = x+2;
}

// After required changes, return the x value.
return x;

}


int player2_Y(int x, int y, int dice){
/*
This function gets the current coordinates and the dice value of player 2, and increase-decrease it's x and y coordinate
values according to the location of the player(for example, it increase the x value if the player is on the top road, or
decreases the x value if it's on bottom road, and it does the similar for the left and right roads.)

*/
int penaltyCounter = 2; //this is only used for the penalty point on (5,26).
int counter;
counter = dice;

while(counter > 0){

    if(y==3 && x<26){ // top road
        x++;
        counter--;
    }else if(x==26 && y<11){ // right road
        y++;
        counter--;
    }else if(y==11 && x>3){ // bottom road
        x--;
        counter--;
    }else if(x==3 && y>3){ // left road
        y--;
        counter--;
    }
}
// Checks if the player stops on a penalty point (since this function is for returning y, it doesnt interfere with the)
// situations where the x value needs to be changed as it hit a penalty point.
if(y==10&&x==26){
    printf("Penalty for player 2.\n");
    y = y-2;
}else if(y==5 && x==26){
    // Since this penalty point is close to a corner, it is kinda problematic. So i needed to create a mini version of the coordinate calculating algorithm
    // with a counter(equivalent of the dice value) value 2.
    printf("Penalty for player 2.\n");
    if(y==3 && x<26){
        x--;
        penaltyCounter--;
    }else if(x==26 && y<11){
        y--;
        penaltyCounter--;
    }

}
// After required changes, return the y value.
return y;

}

//This function works paralelly with the ones who calculate the locations of player1. But since they return the coordinates, I decided to have the x-y coordinates flow the same way
//in this function to only get 1 or 0 to determine whether the game is finished or not.
int p1won(int x, int y, int dice){


// The counter variable means the dice value.
int counter;
int i,j;
counter = dice;

while(counter > 0){

    if(y==1 && x<28){
        x++;
        counter--;
    }else if(x==28 && y<13){
        y++;
        counter--;
    }else if(y==13 && x>1){
        x--;
        counter--;
    }else if(x==1 && y>1){
        y--;
        counter--;
    }
// returns 1 as the coordinates of player 1 pass by the end point.
    if(y==2 && x==1){
        printf("PLAYER 1 HAS WON THE GAME.\n");
        return 1;
    }
}

if(y==7&&x==28){
    y = y-2;
}

return 0;

}

//This function works paralelly with the ones who calculate the locations of player2. But since they return the coordinates, I decided to have the x-y coordinates flow the same way
//in this function to only get 1 or 0 to determine whether the game is finished or not.
int p2won(int x, int y, int dice){

int counter;
counter = dice;

while(counter > 0){
//counter=0 // y=3 // x=26
    if(y==3 && x<26){
        x++;
        counter--;
    }else if(x==26 && y<11){
        y++;
        counter--;
    }else if(y==11 && x>3){
        x--;
        counter--;
    }else if(x==3 && y>3){
        y--;
        counter--;
    }
// returns 1 as the coordinates of player 2 pass by the end point.
    if(y==4 && x==3){
        printf("PLAYER 2 HAS WON THE GAME.\n");
        return 1;
    }

}

if((y==3&&x==10) || (y==3 && x==18)){
    x = x-2;
}else if((y==11&&x==10) || (y==11&&x==18)){
    x = x+2;
}


return 0;


}

// Just fills the 2D array with the base elements(borders, finish lines, penalty points, roads..) except the players.
void fillMap(char board[][COLUMN]){

    int i,j,k;

    for(i=0;i<ROW;i++){

        for(j=0;j<COLUMN;j++){
            if(i==0 || i==14){
                board[i][j] = '.';
            }else if(i==1 || i== 13){
                if(j==0 || j==29){
                    board[i][j] = ':';
                }else if(j==14){
                    board[i][j] = 'X';
                }else board[i][j] = ' ';
            }else if(i==2 ||  i==12){
                if(j==0 || j==29){
                    board[i][j] = ':';
                }else if(j != 1 && j!=28){
                    board[i][j] = '.';
                }else board[i][j] = ' ';
            }else if(i==3 || i==11){
                if(j==0 || j==29){
                    board[i][j] = ':';
                }else if(j==2 || j==27){
                    board[i][j] = ':';
                }else if(j==10 || j==18){
                    board[i][j] = 'X';
                }else board[i][j] = ' ';
            }else if(i==4 || i==10){
                if(j==0 || j==29){
                    board[i][j] = ':';
                }else if(i==10 && j==26){
                    board[i][j] = 'X';
                }else if(j==2 || j==27){
                    board[i][j] = ':';
                }else if(j<=25 && j>=4){
                    board[i][j] = '.';
                }else board[i][j] = ' ';
            }else if(i>=5 && i<=9){
                if(j==0 || j==29){
                    board[i][j] = ':';
                }else if((i==5 && j==26) || (i==7 && j==28)){
                    board[i][j] = 'X';
                }else if(j==2 || j==4 || j==25 || j==27){
                    board[i][j] = ':';
                }else board[i][j] = ' ';

            }

        }
    }

    board[2][1] = '_';
    board[4][3] = '_';
}

int startGame(){
/*

This function lets the players roll the dice and decide
who will be starting first.

Returns 1 for player 1 and 2 for player 2.

If the dice values are equal, makes them roll the dice again and again
until they get different values.

*/
int p1,p2;
char enter;

printf("To start the game, players should dice and decide who is going to start first according to it...\n\n");

do{

printf("PLAYER 1... press ENTER to dice...\nDICE: ");
getchar();
p1 = dice();
printf("%d\n",p1);

printf("PLAYER 2... press ENTER to dice...\nDICE: ");
getchar();
p2 = dice();
printf("%d\n",p2);

if(p1==p2){
    printf("Same dice value. Please try again.\n");
}

}while(p1 == p2);

// This block compares the dice values and return the value of player who will be starting first.
if(p1>p2){
    printf("*** PLAYER 1 will start the game...***\n");
    return 1;
}else if(p2>p1){
    printf("*** PLAYER 2 will start the game...***\n");
    return 2;
}else printf("error in startGame() function.");

}


//Prints the 2D array which store the map. Also colorize certain elements like the penalty points, finish line, players..
void printMap(char map[15][30], int player1_X, int player1_Y, int player2_X, int player2_Y){
/*
Takes the location of the players and puts them in the array.
Then prints the array using a 2 dimensional nested loop.
Also colorizes some items.
*/
int y,x;

map[player1_Y][player1_X] = '1';
map[player2_Y][player2_X] = '2';


for(y=0;y<ROW;y++){
        for(x=0;x<COLUMN;x++){
            if((y==1&&x==14)||(y==7&&x==28)||(y==13&&x==14)||(y==3&&x==10)||(y==3&&x==18)||(y==5&&x==26)||(y==10&&x==26)||(y==11&&x==10)||(y==11&&x==18)){
                printf("\033[0;31m");
                printf("%c",map[y][x]);
                printf("\033[0m");
            }else if(y==player1_Y&&x==player1_X){
                printf("\033[0;33m");
                printf("%c",map[y][x]);
                printf("\033[0m");
            }else if(y==player2_Y&&x==player2_X){
                printf("\033[0;34m");
                printf("%c",map[y][x]);
                printf("\033[0m");
            }else if((y==2&&x==1)||(y==4&&x==3)){
            	printf("\033[0;32m");
                printf("%c",map[y][x]);
                printf("\033[0m");
            }else printf("%c",map[y][x]);
        }
        printf("\n");
    }

}

// Just a simple function which returns a random integer between 1 and 6 (1 and 6 included.).
int dice(){

srand(time(NULL));
int randNum = (rand() % 6) + 1;
return randNum;

}


