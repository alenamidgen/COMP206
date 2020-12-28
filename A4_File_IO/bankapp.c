/* 
 Program to implement a simple banking application
********************************************************************
* Author        Dept.           Date            Notes
********************************************************************
* Alena Midgen  Software Eng    March 10, 2020   initial draft
* Alena Midgen  Software Eng    March 11, 2020   first round of edits
* Alena Midgen  Software Eng    March 13, 2020   completion
* Alena Midgen  Software Eng    March 28, 2020  tried to fix errors
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int addAcc(int argc, char *argv[]);
int deposit(int argc, char *argv[]);
int withdrawal(int argc, char *argv[]);
int verifyAccNum(char *num);

FILE *file;

int main(int argc, char *argv[] ){

        char *add = "-a";
        char *dep = "-d";
        char *wd = "-w";



        // if there are less than 3 arguments, or the first argument doesn't match the valid options
        if(argc < 2 || (strcmp(argv[1], add) != 0 && strcmp(argv[1], dep) != 0 && strcmp(argv[1], wd) != 0)){
                // prints error message to stderr
                fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
                exit(1);


        // then executes the appropriate functions according to the first argument
        } else if(strcmp(argv[1], add) == 0) {
                addAcc(argc, argv);
        } else if(strcmp(argv[1], dep) == 0) {
                deposit(argc, argv);
        } else if(strcmp(argv[1], wd) == 0) {
                withdrawal(argc, argv);
        }

        return 0;

}

// the function to add an account
int addAcc(int argc, char *argv[]){
	 //prints error and exits if there isn't the right number of arguments
        if(argc != 4){
                fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n");
                exit(1);


        // if the length of the second argument isn't 4, an error is printed and the program exits      
        }else if(strlen(argv[2]) != 4){
               fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n not 4 digit");
        }

        //tries to open the file
        if((file = fopen("bankdata.csv", "a"))){

                fclose(file);
                //if the account number is not used before
                if(verifyAccNum(argv[2])==-1){
                        file = fopen("bankdata.csv", "a");
                        fprintf(file, "AC,%s,%s\n", argv[2], argv[3]);
                        fclose(file);
                        return 0;

                //otherwise, prints error and exits     
                }else {
                        fprintf(stderr, "Error, the account number %s already exists\n", argv[2]);
                        fclose(file);
                        exit(50);
                }
        }else{
                //prints this is there is no file
                fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
                exit(100);
        }
        return 0;
}

//fundtion to make a deposit
int deposit(int argc, char *argv[]){

         //prints error and exits if there isn't the right number of arguments
        if(argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
                exit(1);

        // if the length of the second argument isn't 4, an error is printed and the program exits      
        }else if(strlen(argv[2]) != 4){
               fprintf(stderr, "Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
        }
        //tries to open the file
        file = fopen("bankdata.csv", "r");
        if(file != NULL){
                fclose(file);
                 //if the account number has been used before
                if(verifyAccNum(argv[2])!=-1){
			file = fopen("bankdata.csv", "a");
                        //writes the following to the file, closes it and exits
                        fprintf(file, "TX,%s,%s,%s\n", argv[2], argv[3], argv[4]);
                        fclose(file);

                        return 0;

                //otherwise, prints error and exits     
                }else {
                        fprintf(stderr, "Error, the account number %s does not exist\n", argv[2]);
                        exit(50);
                }
        //if file is not found, the following message is printed and the program exits
        }else{
                fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
                exit(100);
        }

        return 0;
}

//function for withdrawals
int withdrawal(int argc, char *argv[]){

         //prints error and exits if there isn't the right number of arguments
        if(argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
                exit(1);

         // if the length of the second argument isn't 4, an error is printed and the program exits     
        }else if(strlen(argv[2]) != 4){
               fprintf(stderr, "Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
        }

        //tries to open the file        
          file = fopen("bankdata.csv", "r");
          if(file != NULL){
                fclose(file);
        //if the account number has been used before
                if(verifyAccNum(argv[2])!=-1){
                	file = fopen("bankdata.csv", "r");
                        char *line;
                        size_t line_size = 0;
                        int lineNum = 0;

                        int sum = 0;
                        int sumIncluded = 0;
                        int column = 0;
                        char *token;
                        int transaction = 0;
                        int accPresent = 0;

                        //iterates through the lines of the file
                        while(getline(&line, &line_size, file)>=0){
				 //analyses if the first token indicates the line describes a transaction
                                token = strtok(line, ",");
                                if(strcmp(token, "TX") == 0){
                                        transaction = 1;

                                }

                                //checks to see if the account number matches that of the desired withdrawal
                                token = strtok(NULL, ",");
                                if(strcmp(token, argv[2])==0){
                                        sumIncluded = 1;

                                }
                                token = strtok(NULL, ",");
                                if(transaction == 1){
                                        //if it's a transaction, goes to the last piece of data
                                        token = strtok(NULL, ",");
                                        if(sumIncluded == 1){
                                                char *eptr;
                                                //if it's of the required account, adds the last number to the running sum
                                                sum = sum + strtod(token, &eptr);

                                        }
                                }
                                transaction = 0;
                                sumIncluded = 0;
                        }

                        //if there is enough money in the account:
                        if(sum > atoi(argv[4])){
                                fclose(file);
                                file = fopen("bankdata.csv", "a");
                         //writes the following line in the file and returns
                                fprintf(file, "TX,%s,%s,-%s\n", argv[2], argv[3], argv[4]);
                                fclose(file);
                                return 0;
                        //if there wasn't enough money, prints the error and exits
                        }else{
                                fprintf(stderr, "Error, account %s only has %d\n", argv[2], sum);
                                exit(60);
                        }


                //otherwise, prints error and exits
                }else {
                        fprintf(stderr, "Error, the account number %s does not exist\n", argv[2]);
                        exit(50);
                }
        //prints this error if there was no data file found
          }else{
                fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
                exit(100);

        }
	 return 0;
}

//returns -1 if the account number is not used, or the line number it was used in if it was used
int verifyAccNum(char *num){
        file = fopen("bankdata.csv", "r");
        char *line;
        size_t line_size = 0;
        int lineNum = 0;

        // goes through all the lines and makes tokens by seperating them where the commas are
        while(getline(&line, &line_size, file)>=0){

                char *token = strtok(line, ",");

                //checks to see if the account number is equal to the token
                while (token != NULL) {
                        if(strcmp(token, num) ==0){
                                fclose(file);
                                return lineNum;
                        }
                         token = strtok(NULL, ",");
                }

        lineNum = lineNum + 1;

        }
        fclose(file);
        return -1;

}
