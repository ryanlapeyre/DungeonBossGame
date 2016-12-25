#include "game.h"

//Knock yourself out boys and girls. 

Boss* loadBoss()
{
    Boss* boss;
    boss = malloc(sizeof(Boss));
    FILE* fp; 
    int numqueue = 0;
    int x = 0;
    // Define our values, and immediately malloc for the boss.
    
    fp = fopen("Boss.txt" , "r");

    if(fp == NULL )
    {
	puts("CAN YOU SEE WHY KIDS LOVE CINNAMON TOAST CRUNCH?!");
	exit(0);
	// A cautionary error check.
    }

    fscanf( fp , "%s | %d | %d | %d | %d" , boss->name , &boss->health , &boss->baseDefense , &boss->baseAttack ,   &boss->baseSpeed   ); 

    //Of course, file scan the needed values and put the inside of the boss.
   
   
    boss->maxHealth = boss->health;
    DecisionTreeNode* AI = NULL;
    boss->root = AI;

    //We make the maxHealth have the same value as health, can be done many ways. 
    //This gives us a value so the bossHeal works in fight.c
    // We create a DecisionTreeNode, and make it NULL. Now, the boss has 
    // a DTN inside of it, simple precaution as it holds no values.



    while(!feof(fp))
    {

	//While the file pointer does not point to the end of file. Do these things. 
	//Make another DNT and malloc, and NULL unneeded values, and scan from the file. 

	DecisionTreeNode* newNode;
	newNode = malloc(sizeof(DecisionTreeNode));
	newNode ->left  = NULL;
	newNode -> right = NULL;
	newNode->FirstAction = NULL;
	fscanf(fp , "%d | %d | %d" , &newNode->healthFloor , &newNode->healthCeiling , &numqueue);

	

	for(x = 0; x < numqueue; x++)
	{
	    
	    //The numqueue value we scan in earlier tells us how many possible actions the boss can take.
	    //Based on this we need to build a linked list with these actions.
	    //The "for" loop builds and mallocs a linked list member and scans in its respective action. 
		
	    ActionNode* dummy;
	    dummy = malloc(sizeof(ActionNode));
	    dummy->next = NULL;
	    fscanf(fp , "%u" , &dummy->decision);
	    //This is an unsigned integer scan because it's an enum.
	    newNode ->FirstAction = addActionToList(newNode->FirstAction , dummy);
	    // So using the node the we have built, we give its first action the linked list member and build the linked
	    // list. Loops and properly enqueues the function.
	    // When these loops are done, we have a fully functional BST based on the health values
	    // with a linked list inside.
	}

	AI = addNodeToTree(AI , newNode);
	// Adds the nodes to the head AI tree.


    }

    boss->root = AI;
    fclose(fp);
    return boss;

    //Give the root BST in the boss the AI tree built.
    //Close our file and return the boss.

}

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
    if(front == NULL)
    {
	return newAction; 
	// This will ring true for the first run of the program, makes the linked list have a "head" or
	// first value.
	//Also our base case. 
    }
    else
    {
	front->next = addActionToList(front->next , newAction);
	return front;
	//Recursive call to add a new action to the linked list. 
	//Works by accessing the newest member of the linked list. Traverses through the linked list until reaching
	//a NULL "front." If the "front" value is NULL, then returns "newAction"
	//as the action to be added, and then returns the value for the function. 
    }

}

DecisionTreeNode* addNodeToTree(DecisionTreeNode* root, DecisionTreeNode* newNode)
{
    if(root == NULL)
    {
	return newNode;
	//Our base case. Returns the "newNode" as the node to be added to the BST when reached. 
    }

    else if(newNode->healthFloor > root->healthCeiling)
    {
	root->right = addNodeToTree(root->right , newNode);	
	// If the floor is greater than the root's ceiling, adds a node to the right root of the tree.

    }
    else if (newNode->healthCeiling < root -> healthFloor)
    {
	root->left = addNodeToTree(root->left , newNode);	
	//Same as above, but vice versa. 
    }


    return root; 
}
ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{
    ActionNode* value = root->FirstAction;
    int hp = boss->health;
    // We have these values in case none of our "if" statements are hit. 
    
    if (hp < root-> healthCeiling && hp > root->healthFloor)
    {
	return root->FirstAction;
	// Returns the FirstAction of the root once a new HP range has been hit. 
    }

    else
    {
	if(hp > root->healthCeiling)
	{
	    return fetchNewList(boss , root->right);
	    //Traverses the right of the tree is HP is greater then the root's ceiling.
	}
	else if(hp < root->healthFloor)
	{
	    return fetchNewList (boss , root->left);
	    //Vice versa.
	}
    }
    
    return value;
    //In case of a tie. 

}

void freeBossTree(DecisionTreeNode* root)
{
    if(root == NULL)
    {
	return; 
	//Don't free anything when the root is NULL. 
    }

    freeBossTree(root->left);
    freeBossTree(root->right);
    freeActionListInNode(root->FirstAction);
    free(root);

    //Steps through the left and right side of the BST, and free the values held inside.
    //Does not free when hitting a NULL value, instead return to the previous call. 
    //Finally, frees the root when done with recursive calls. 

}

void freeActionListInNode(ActionNode* head)
{
    ActionNode* temp = head;
    while ( head != NULL) 
    {
	temp = head;
	head = head->next;
	free(temp);
    }
    free(head);

    //A simple free function for a linked list. Sets up a temporary variable, and steps through it while freeing
    //its value. Then, frees the head of the linked list at the end when finished. 
}



