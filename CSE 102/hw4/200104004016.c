#include <stdio.h>

void write_coefficients(int a, int b, int c);
void draw_graph();
void graph_to_txt();



int main(){

int operation;

// Coefficients for the equation.
int a;
int b;
int c;

do{ //This do-while loop continues until the user enters 4.

printf("Select an operation:\n");
printf("1 -> Enter the coefficients.\n2 -> Draw the graph.\n3 -> Print the graph into a .txt file.\n4 -> Exit.\n");

printf("\nChoice:");
scanf("%d",&operation);

switch(operation){

case 1:
    //In this case, the program gets coefficients from the user and save them in a .txt file called coefficients.txt.
    printf("Please enter the coefficients for the following equation: x = a*(y*y) + b*y + c\n");

    printf("a: ");
    scanf("%d",&a);

    printf("b: ");
    scanf("%d",&b);

    printf("c: ");
    scanf("%d",&c);

    write_coefficients(a,b,c);

    printf("\ncoefficients.txt has been created and the values have been written inside it.\n");

    break;
case 2:
    //In this case, the program prints the graph of the equation with the coefficients taken from user, on the terminal screen.
    draw_graph();
    //For more detailed info, check the comments in the draw_graph function block.
    break;
case 3:
    //In this case, the program prints graph of the equation in a .txt file called graph.txt.
    graph_to_txt();
    //For more detailed info, check the comments in the graph_to_txt function block.
    break;

default:

    break;
}

}while(operation != 4);

return 0;

}

void write_coefficients(int a, int b, int c){

    //This function simply writes the input data taken from the user, to a .txt file called coefficients.txt.
    FILE *fp;

    fp = fopen("coefficients.txt","w+");

    fprintf(fp,"%d ",a);
    fprintf(fp,"%d ",b);
    fprintf(fp,"%d ",c);

    fclose(fp);

}

void draw_graph(){

//This Function prints the graph of the equation with the coefficients taken from user, on the terminal screen.

//The border values for the graph (50x15).
int xAxisBorder = 50;
int yAxisBorder = 15;
//Necessary variables for the loops in the function, and for the coefficients.
int y=0;
int x=0;
int a,b,c;


//This section of the code read the coefficient values from the .txt file to use in the function.
FILE *fk;

fk = fopen("coefficients.txt","r");

fscanf(fk,"%d ",&a);
fscanf(fk,"%d ",&b);
fscanf(fk,"%d ",&c);

fclose(fk);

printf("Coefficients has been read from the coefficients.txt file.\n");
printf("Printing the graph of x = %d(y*y) + %d*y + %d\n\n",a,b,c);

for(y=yAxisBorder+1;y>-yAxisBorder-1;y--){

    for(x=-xAxisBorder;x<xAxisBorder+1;x++){

       if( ( x == a*y*y + b*y + c ) ){
       //The graph is printed here.             // This loops works in a hierarchical way to print the graph. The priority order is:
            printf("\033[0;34m");               // 1. Graph , 2. Elements of the coordinate plane , 3. Numbers on the coordinate plane, 4. Blank spaces.
            printf("#");
            printf("\033[0m");
        }else if(y == 0 && x == +50){
       //Elements of the coordinate plane such as -,|,<,> and ^ characters are printed in this part of the code.
            printf(">");
        }else if(y == 0 && x == -50){

            printf("<");
        }else if(x == 0 && y == 16){

            printf("^");
        }else if(y == 0){

            printf("-");

        }else if(x == 0){

            printf("|");

        //The numbers on the coordinate plane are printed in this part of the code.
                //
        }else if(x == -1 && y == -1){

            printf("\033[0;33m");
            printf("0");
            printf("\033[0m");

        }else if( x == -3 && y % 5 == 0){

            printf("\033[0;33m");
            printf("%d",y);
            printf("\033[0m");
            if(y > 0){
                if(y / 10 >= 1){

                    x+=1;
                }
            }else if(y < 0){
                if(y / 10 <= -1){

                    x+=2;
                }else x++;

            }else printf("%d",y);

        }else if( y == -1 && x % 10 == 0){

            printf("\033[0;33m");
            printf("%d",x);
            printf("\033[0m");
                if(x > 0){
                    if(x / 10 >= 1){

                        x+=1;
                    }
                }else if(x < 0){

                        if(x / 10 <= -1){
                            x+=2;
                        }else x++;
                }
                //Finally, if the space on the coordinate plane doesnt have any better character to be printed on, the function prints a blank space.
                }else printf(" ");

    }
    printf("\n"); //New line, new y value and a new round for x value loop.

}


}

void graph_to_txt(){

//This Function prints the graph of the equation with the coefficients taken from user, on a .txt file called graph.txt.

//The border values for the graph (50x15).
int xAxisBorder = 50;
int yAxisBorder = 15;

//Necessary variables for the loops in the function, and for the coefficients.
int y=0;
int x=0;
int a,b,c;

//This section of the code read the coefficient values from the .txt file to use in the function.
FILE *fk;

fk = fopen("coefficients.txt","r");

fscanf(fk,"%d ",&a);
fscanf(fk,"%d ",&b);
fscanf(fk,"%d ",&c);

fclose(fk);

FILE *ff; // This pointer is used to write data into a .txt file called graph.txt.

ff = fopen("graph.txt","w+");

for(y=yAxisBorder+1;y>-yAxisBorder-1;y--){

    for(x=-xAxisBorder;x<xAxisBorder+1;x++){

       if( ( x == a*y*y + b*y + c ) ){
       //The graph is printed here.             // This loops works in a hierarchical way to print the graph. The priority order is:
                                                // 1. Graph , 2. Elements of the coordinate plane , 3. Numbers on the coordinate plane, 4. Blank spaces.
            fprintf(ff,"#");
        }else if(y == 0 && x == +50){
       //Elements of the coordinate plane such as -,|,<,> and ^ characters are printed in this part of the code.
            fprintf(fk,">");
        }else if(y == 0 && x == -50){

            fprintf(ff,"<");
        }else if(x == 0 && y == 16){

            fprintf(ff,"^");
        }else if(y == 0){

            fprintf(ff,"-");

        }else if(x == 0){

            fprintf(ff,"|");

        //Finally, if the space on the coordinate plane doesnt have any better character to be printed on, the function prints a blank space.
        }else fprintf(ff," ");

    }
    fprintf(ff,"\n");

}

fclose(fk);

printf("\nGraph has been written to a .txt file called graph.txt successfully.\n");

}



