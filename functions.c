#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#include"structs.h"
#include "functions.h"

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
int login(char *username, char *pass, accounts *accountsHead)
{
    //In this Function we check if Username and password is correct
    if (check(username, pass, accountsHead, 3) == TRUE)
    {
        printf("Welcome to your account =)  \n ");
        return 1;
    }
    else
    {
        printf("User not found you should signup first! \n");
        return 0;
    }
}
void delete(int postnum, accounts *user)
{
    // we delete the post and free the node 
    posts *node = user->postshead;
    posts *prev;
    while (node->nextpost)
    {
        prev = node;
        node = node->nextpost;
        if (node->postnum == postnum)
        {
            prev->nextpost = node->nextpost;
            free(node);
            return;
        }
    }

    printf("couldnt delete the post \n ");
}
void info(char *username, accounts *accountsHead, int flag)
{
    accounts *curUser;
    if (curUser = finduser(username, accountsHead))
    {
        posts *node = curUser->postshead->nextpost;
        if (flag == 0)
        {
            printf("Your username is %s \n Your password is %s \n here is your posts \n", curUser->user, curUser->pass);
        }
        else if (flag == 1)
        {
            printf("Your username is %s \t here is your posts \t  ", curUser->user);
        }
        while (node)
        {
            printf("%s \t likes : %d\t postId : %d\n", node->text, node->likenum, node->postnum);
            node = node->nextpost;
        }

       
    }
    else
    {
        printf("User not found \n");
    }
}
void like(char *username, int postnum, accounts *accountsHead)
{
    accounts *user = finduser(username, accountsHead);
    posts *node = user->postshead;
    while (node)
    {
        if (node->postnum == postnum)
        {
            node->likenum = node->likenum + 1;
            return;
        }

        node = node->nextpost;
    }

    printf("You liked the post \n ");
}
void post(char *text, char *curuser, accounts *accountsHead)
{
    accounts *cur = finduser(curuser, accountsHead);
    (cur->postnum)++;
    AddPost(curuser, cur->postshead, text, cur->postnum, 0);
    printf("Your post has been uploaded =)  \n ");
}
int check(char *username, char *pass, accounts *accountsHead, int checkwhich) //Checks if the given username / pass matches 
{
    accounts *node = accountsHead;
    switch (checkwhich)
    {
    case CHECK_USERNAME:
    {
        for (int i = 0; node; i++)
        {
            if (strcmp(username, node->user) == 0)
            {
                return TRUE;
            }
            node = node->nextaccount;
        }
        break;
    }
    case CHECK_PASS:
    {
        for (int i = 0; node; i++)
        {
            if (strcmp(pass, node->pass) == 0)
            {
                return 1;
            }
            node = node->nextaccount;
        }
        break;
    }
    default:
    {
        for (int i = 0; node != NULL; i++)
        {
            if (((strcmp(username, node->user)) == 0) && ((strcmp(pass, node->pass)) == 0))
            {
                return 1;
            }
            node = node->nextaccount;
        }
        break;
    }
    }
    return FALSE;
}
