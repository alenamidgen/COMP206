/*
*Program to implement caesar's cipher 
*************************************************************** 
* Author        Dept .          Date            Notes *
***************************************************************
* Alena Midgen Software Eng . Feb 20 2020 Initial version .
* Alena Midgen Software Eng . Feb 20 2020 Debugged version.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char *argv []){

        // returns if there isn't a second argument
        if (argc != 2){
                printf("Error: usage is caesarcipher <offset>\n");
                return 1;
        }

        //declares variables for the counter and strings
        int i;
        char message[100];
        char crypted[100];
        char ch;
        //loops while there is still and input in the stream
        while((ch = getchar()) != EOF){
                ungetc(ch, stdin); //puts the char back

                fgets(message, 100, stdin);
                // for each character in the stream message
                for(i = 0; i < 100; i++){

                        // if it is in the lower case alphabet, the corresponding character in the output is shifted in a way that it will return to the beginning of the alphabet
                        if (message[i] >= 'a' && message[i] <= 'z'){
                                if(message[i] + atoi(argv[1]) > 'z'){
                                        crypted[i] = message[i] + atoi(argv[1]) - 26;
                                } else if (message[i] + atoi(argv[1]) < 'a'){
                                        crypted[i] = message[i] + atoi(argv[1]) + 26;
                                } else{
                                        crypted[i] = message[i] + atoi(argv[1]);
                                }

                        //otherwise the crypted message is the same
                        }else{
                                crypted[i] = message[i];
                        }
                }
                //crypted message is printed
                printf("%s", crypted);
        }
        //0 is returned
        return 0;
}
