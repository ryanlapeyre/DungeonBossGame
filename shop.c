#include "game.h"

Shop* loadShop()
{

    FILE* f= fopen("Items.txt","r");
    Shield* shieldCache, *oldShield, *myShield;
    Sword* swordCache, *oldSword, *mySword;

    shieldCache= NULL;
    swordCache=NULL;


    Shop *myShop;

    myShop=malloc(sizeof(Shop));

    int i = 0;

    for(i=0;i<NUMSHIELDS;i++)
    {
	oldShield=malloc(sizeof(Shield));//initialize
	fscanf(f, "%s | %d | %d", (oldShield->name), &(oldShield->cost), &(oldShield->defense));
	if(shieldCache==NULL)
	{
	    shieldCache=oldShield;
	}
	oldShield->prevShield=shieldCache;//set it to NULL/value of oldshield
	shieldCache->nextShield=oldShield;
	shieldCache= oldShield;

    }

    for(i=0;i<NUMSWORDS;i++)
    {

	oldSword=malloc(sizeof(Sword));//initialize
	fscanf(f, "%s | %d | %d", (oldSword->name), &(oldSword->cost), &(oldSword->attack));
	if(swordCache==NULL)
	{
	    swordCache=oldSword;
	}
	oldSword->prevSword=swordCache;//set it to NULL/value of oldshield
	swordCache->nextSword=oldSword;
	swordCache= oldSword;

    }
    myShield=shieldCache;
    mySword=swordCache;

    for(i=0; i<NUMSHIELDS; i++)
    {
	myShield=myShield->prevShield;
    }
    myShield->prevShield=NULL;


    for(i=0; i<NUMSWORDS; i++)
    {
	mySword=mySword->prevSword;
    }
    mySword->prevSword=NULL;


    myShop->headSword=mySword;
    myShop->headShield=myShield;

    fclose(f);

    return myShop;
}

void destroyShop(Shop* shop)
{
    Shield* temp;
    Sword* temp2;

    while ((temp = shop->headShield->nextShield) != NULL) {
	shop->headShield = shop->headShield->nextShield;
	free(temp);
    }

    while ((temp2 = shop->headSword->nextSword) != NULL) {
	shop->headSword = shop->headSword->nextSword;
	free(temp2);
    }
    free(shop);
}

void sortShields(Shield** shields)
{
    Shield* start = *shields; // copy of head node , used just to find out number of elements in the list
    Shield* temp = NULL;   // starts at NULL, to be compared in a bit
    Shield* current = NULL;
    Shield* spare = NULL;
    int count = 0;
    int x = 0;

    while(start!= NULL)
    {
	start = start->nextShield; // for some reason, couldn't get a while loop based on != NULL to work
	count++;	// instead, this was implemented to keep track of current # of items
    }

    for(x = 0; x < count; x++)  // similar setup to start of a bubble sort
    {
	current = spare = *shields; // start of current and spare , makes them head pointers

	while(current->nextShield != NULL) 
	{
	    if(current->cost > current->nextShield->cost)
	    {
		temp = current->nextShield;  // bubble sort stuff. 
		current->nextShield = current->nextShield->nextShield;
		temp->nextShield = current;

		if(current == *shields )  // if current is still the head value
		{
		    *shields = spare = temp; // resets temp and spare, making the bubble sort work again due to the values compared, this is the special case in which  the very first value in the linked list is compared. similar to the first case scenario in the remove function  

		}
		else
		{
		    spare->nextShield = temp; // sets spare's pointer to temp, traversing through the list
		    current = temp; // resets current, since values have been compared and swapped

		}

	    }

	    spare = current; // bumps through the link list
	    current = current->nextShield;// the bump line
	}
    }
}

void sortSwords(Sword** swords)
{
    Sword* start = *swords; // copy of head node , used just to find out number of elements in the list
    int count = 0;  
    while(start!= NULL)
    {
	start = start->nextSword; // for some reason, couldn't get a while loop based on != NULL to work
	count++;	// instead, this was implemented to keep track of current # of items
    }
    Sword* end;
    Sword* current = *swords;
    Sword* prev = 0;
    Sword* tempNode = 0;
    int changeFlag = 0;
    int i = 0;
    for (i = 0; i < count ; i++)
    {
	while (current->nextSword != 0)
	{
	    tempNode = current->nextSword;

	    if (current->cost > tempNode->cost)
	    {
		changeFlag = 1;
		current->nextSword = tempNode->nextSword;
		tempNode->nextSword = current;
		if (prev != 0)
		    prev->nextSword = tempNode;
		prev = tempNode;
		if (*swords == current)
		    *swords = tempNode;
		if (current->nextSword == 0)
		   end = current;
	    }
	    else
	    {
		prev = current;
		current = current->nextSword;
	    }
	}
	if (changeFlag == 0)
	    break;
	else
	{
	    prev = 0;
	    current = *swords;
	    changeFlag = 0;
	}
    }
}
void printShields(Shield* shields)
{

    Shield* s=shields;
    int i=1;

    while(s!=NULL)
    {
	printf("\n %d - ", i);
	printf("%s \n\tCost: %d \tDefense: %d", s->name, s->cost, s->defense);
	s=s->nextShield;
	i++;
    }


}

void printSwords(Sword* swords)
{

    Sword* s=swords;
    int i=1;

    while(s!=NULL)
    {
	printf("\n %d - ", i);
	printf("%s \n\tCost: %d \tAttack: %d", s->name, s->cost, s->attack);
	s=s->nextSword;
	i++;

    }
}
Sword* removeSwordFromList(Sword** swords, int choice)
{
    Sword* s=*swords;
    Sword* s1=*swords;
    int i=0;
    Sword* sold;

    if(choice==1)//Account for the first item being chosen
    {
	sold=s; //Selling the first item
	*swords = (*swords)->nextSword;
	(*swords)->prevSword =NULL;
	return sold;
    }


    for(i=1; i<choice-1; i++)
    {
	s1=s1->nextSword;
    }

    if(i == choice -1)
    {
	sold = s1->nextSword;
	s1->nextSword = NULL;
	return sold;
    }


    sold=s1->nextSword;
    s=s1->nextSword;
    Sword* s2=s1->nextSword=s->nextSword;
    s2->prevSword = s1;
    return sold;
}



Shield* removeShieldFromList(Shield** shields, int choice)
{
    Shield* s=*shields;
    Shield* s1=*shields;
    int i=0;
    Shield* sold;

    if(choice==1)//Account for the first item being chosen
    {
	sold=s; //Selling the first item
	*shields = (*shields)->nextShield;
	(*shields)->prevShield =NULL;
	return sold;
    }


    for(i=1; i<choice-1; i++)
    {
	s1=s1->nextShield;
    }

    if(i == choice -1)
    {
	sold = s1->nextShield;
	s1->nextShield = NULL;
	return sold;
    }


    sold=s1->nextShield;
    s=s1->nextShield;
    Shield* s2=s1->nextShield=s->nextShield;
    s2->prevShield = s1;
    return sold;

}

/***************************START OF FUNCTIONS GIVEN TO YOU**********************************/

void freeHeroesAndItems(Hero* heroes)
{
    int i;
    for(i = 0; i < NUMCHOSENHEROES; i++)
    {
	if(heroes[i].heroSword != NULL)
	{
	    free(heroes[i].heroSword);
	}
	if(heroes[i].heroShield != NULL)
	{
	    free(heroes[i].heroShield);
	}
    }
    free(heroes);
}

void goShopping(Hero* heroes, Shop* shop)
{

    printf("\n\nNow, you will select a sword and shield for your heroes.\n");

    int firstPass = 1; 

    int bank = STARTINGBANKVALUE;

    while(1)
    {
	printf("Which would you like to look at?\n");
	printf("1: Swords\n2: Shields\n3: Continue to fight\n");
	printf("> ");
	int choice; 
	scanf("%d", &choice);
	while(choice < 1 || choice > 3)
	{
	    printf("Invalid choice. Select again: \n");
	    printf("> ");
	    scanf("%d", &choice);
	}

	if(choice == 3)
	{
	    if(firstPass == 1)
	    {
		printf("Are you sure you don't want to buy anything?\n");
		printf("1: yes\n2: no\n");
		printf("> ");
		scanf("%d", &choice);
		while(choice < 1 || choice > 2)
		{
		    printf("Invalid choice. Select again: \n");
		    printf("> ");
		    scanf("%d", &choice);
		}
	    }
	    else
	    {
		choice = 1;
	    }

	    if(choice == 1)
	    {
		destroyShop(shop);
		return;
	    }
	}
	else if(choice == 2)
	{
	    printf("Do you want it sorted (1) or unsorted? (2)\n");
	    printf(">");
	    int sortChoice;
	    scanf("%d", &sortChoice);
	    while(sortChoice != 1 && sortChoice != 2)
	    {
		printf("Invalid choice, choose again: ");
		printf(">");
		scanf("%d", &sortChoice);
	    }

	    if(sortChoice == 1)
	    {
		sortShields(&(shop->headShield));
	    }


	    while(1)
	    {
		printShields(shop->headShield);

		while(1)
		{
		    printf("\nBudget: %d\n", bank);
		    printf("Select a shield (-1 to go back): \n");
		    printf("> ");
		    scanf("%d", &choice);

		    while((choice < 1 || choice > NUMSHIELDS) && choice != -1)
		    {
			printf("Invalid choice. Select again: \n");
			printf("> ");
			scanf("%d", &choice);
		    }

		    if(choice != -1)
		    {
			if(findShieldPrice(shop->headShield, choice) > bank)
			{
			    printf("You don't have enough money for that!\n");
			}
			else break;
		    }
		    else break;
		}

		if(choice == -1)
		{
		    break;
		}
		else
		{
		    int heroChoice; 

		    while(1)
		    {
			printHeroes(heroes, NUMCHOSENHEROES);
			printf("Which hero do you want to have the item? (-1 to go back): \n");
			printf("> ");
			scanf("%d", &heroChoice);

			while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
			{
			    printf("Invalid choice. Select again: \n");
			    printf("> ");
			    scanf("%d", &heroChoice);
			}

			if(heroChoice == -1)
			{
			    break;
			}

			if(heroes[heroChoice - 1].heroShield != NULL)
			{
			    printf("That hero already has a shield. Choose again.\n");
			}
			else
			{
			    break;
			}

		    }


		    if(heroChoice == -1)
		    {
			break;
		    }
		    else
		    {
			Shield* item = removeShieldFromList(&(shop->headShield), choice);
			heroes[heroChoice - 1].heroShield = item;
			bank -= item->cost;
			firstPass = 0;
		    }
		}
	    }
	}
	else if(choice == 1)
	{
	    printf("Do you want it sorted (1) or unsorted? (2)\n");
	    printf(">");
	    int sortChoice;
	    scanf("%d", &sortChoice);
	    while(sortChoice != 1 && sortChoice != 2)
	    {
		printf("Invalid choice, choose again: ");
		printf(">");
		scanf("%d", &sortChoice);
	    }

	    if(sortChoice == 1)
	    {
		sortSwords(&(shop->headSword));
	    }

	    while(1)
	    {
		printSwords(shop->headSword);

		while(1)
		{
		    printf("\nBudget: %d\n", bank);
		    printf("Select a sword (-1 to go back): \n");
		    printf("> ");
		    scanf("%d", &choice);

		    while((choice < 1 || choice > NUMSWORDS) && choice != -1)
		    {
			printf("Invalid choice. Select again: \n");
			printf("> ");
			scanf("%d", &choice);
		    }

		    if(choice != -1)
		    {
			if(findSwordPrice(shop->headSword, choice) > bank)
			{
			    printf("You don't have enough money for that!\n");
			}
			else break;
		    }
		    else break;
		}

		if(choice == -1)
		{
		    break;
		}
		else
		{
		    int heroChoice; 

		    while(1)
		    {
			printHeroes(heroes, NUMCHOSENHEROES);
			printf("Which hero do you want to have the item? (-1 to go back): \n");
			printf("> ");
			scanf("%d", &heroChoice);

			while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
			{
			    printf("Invalid choice. Select again: \n");
			    printf("> ");
			    scanf("%d", &heroChoice);
			}

			if(heroChoice == -1)
			{
			    break;
			}

			if(heroes[heroChoice - 1].heroSword != NULL)
			{
			    printf("That hero already has a sword. Choose again.\n");
			}
			else
			{
			    break;
			}
		    }
		    if(heroChoice == -1)
		    {
			break;
		    }
		    else
		    {
			Sword* item = removeSwordFromList(&(shop->headSword), choice);
			heroes[heroChoice - 1].heroSword = item;
			bank -= item->cost;
			firstPass = 0;
		    }
		}
	    }
	}
    }
}

int findSwordPrice(Sword* swords, int choice)
{
    int i = 1;
    while(i < choice)
    {
	swords = swords->nextSword;
	i++;
    }
    return swords->cost;
}

int findShieldPrice(Shield* shields, int choice)
{
    int i = 1;
    while(i < choice)
    {
	shields = shields->nextShield;
	i++;
    }
    return shields->cost;
}
