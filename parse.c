#include "game.h"

//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again. 

void ParseShieldInfo(Shield* s, FILE* fp)
{
    if(fp == NULL)
    {
	puts("UH OH SPAGHETTIOS!");
	// A cautionary error check in case the file pointer is NULL. Supposedly our code is going to be "broken "
	// so it's a failsafe.
	return; 
    }	

    char name[50];
    char cost[50];
    char defense[50];
    char description[100];
    char buffer[MAXFILELINELENGTH];

    //Define character arrays from which we will store various aspects of the Items.txt file. 
    //MAXFILELINELENGTH is defined is header for us, has a value of 150. 


    fgets(buffer , MAXFILELINELENGTH , fp);
    sscanf(buffer , "%[^|]|%[^|]|%[^|]|%[^\n]\n", name , cost , defense , description);
    strcpy(s->name , name);
    s->cost =  atoi(cost);
    s->defense = atoi(defense);
    strcpy(s->description , description);	    

    //We scan into a buffer from fgets and store inside of it. Line 27 is the muscle of this function.
    //First we string scan into the buffer. The percentage sign means store, like %d , %s, etc. The brackets
    //define to scan all objects, except the bars -> |, due to the "^" caret symbol which means to make an exception. So that	  //scans all objects into the field except for |s. Then, ignore the next bar, and star over again. 
    //Repeat until you're at the end of the line, and ignore the newline character. Store these values into their respective
    //fields, convert the needed strings into integer values, and viola!

}


void ParseSwordInfo(Sword* s, FILE* fp)
{

    if(fp == NULL)
    {
	puts("THEY'RE AFTER ME LUCKY CHARMS");
	return; 
    }	

    char name[50];
    char cost[50];
    char attack[50];
    char description[100];


    char buffer[MAXFILELINELENGTH];

    fgets(buffer , MAXFILELINELENGTH , fp);
    sscanf(buffer , "%[^|]|%[^|]|%[^|]|%[^\n]\n", name , cost , attack , description);
    strcpy(s->name , name);
    s->cost =  atoi(cost);
    s->attack = atoi(attack);
    strcpy(s->description , description);	    

}
