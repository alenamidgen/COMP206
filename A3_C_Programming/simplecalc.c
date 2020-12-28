/*Program to implement a simple calculator 
 * *************************************************************** 
 * * Author     Dept .          Date            Notes 
 ***************************************************************
* Alena Midgen Software Eng . Feb 19 2020 Initial version .
* Alena Midgen Software Eng . Feb 20 2020 Debugged version .
*/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){


        // if there isn't the right number of arguments, the error message is displayed and the program returns error code 1
       if (argc != 4){
                printf("Error: usage is simplecalc <x> <op> <y> \n");
                return 1;
        }

       // the operator is stored in a char variable
        char op = *argv[2];

        //switch statement to see which operator it is
        switch(op)
        {
                // each case prints the answer using atoi to convert the argument numbers into integers 
                case '+':
                        printf("%d \n",atoi(argv[1])+atoi(argv[3]));
                        break;
                case '-':
                         printf( "%d \n",atoi(argv[1]) - atoi(argv[3]));
                         break;

                 case '*':
                         printf("%d \n",atoi(argv[1]) * atoi(argv[3]));
                         break;

                 case '/':
                        printf("%d \n",atoi(argv[1]) / atoi(argv[3]));
                         break;

                //if the operator isn't one of the above, a message prints and the error code 2 is returned      
                default:
                         printf("%c is not a valid operator\n", op);
                         return 2;
        }
        //otherwise 0 is returned
        return 0;
}
