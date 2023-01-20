#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#include "structs.h"

#define TRUE 1
#define FALSE 0
#define CHECK_USERNAME 1
#define CHECK_PASS 2

char *signup(char *username, char *pass, accounts *accountsHead)
{
    // In this Function we first check if username is unique then we add a node to "AddAcount" Function

    if (check(username, pass, accountsHead, CHECK_USERNAME) == TRUE)
    {
        printf("This username is already used plz enter another username \n");
        return NULL;
    }
    else
    {
        printf("you signed up successfully =) \n ");
        posts *postsHead = (posts *)malloc(sizeof(posts));
        AddAcount(username, pass, 0, accountsHead, postsHead);

        return username;
    }
}
