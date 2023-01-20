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
accounts *AddAcount(char *user, char *pass, int postnum, accounts *accountshead, posts *postsHead)
{
    // Builds a linked-list -> each new account becomes the second node in the list (The node connected to the Head)
   
    postsHead->user = " ";
    postsHead->likenum = 0;
    postsHead->postnum = 0;
    postsHead->text = " ";
    postsHead->nextpost = NULL;

    accounts *node = (accounts *)malloc(sizeof(accounts));
    if (node == '\0')
    {
        printf("Error ! couldn't allocate memmory!\n");
    }
    else
    {
        node->user = user;
        node->pass = pass;
        node->postnum = postnum;
        node->postshead = postsHead;
        node->nextaccount = accountshead->nextaccount;
        accountshead->nextaccount = node;
    }
    return node;
}
posts *AddPost(char *user, posts *postshead, char *text, int postnum, int likenum)
{
     // Builds a linked-list -> each new post(node) becomes the second node in the list (The node connected to the Head)
    posts *node = (posts *)malloc(sizeof(posts));
    if (node == '\0')
    {
        printf("Error ! couldn't allocate memmory!\n");
    }
    else
    {
        node->user = user;
        node->postnum = postnum;
        node->likenum = likenum;
        node->text = text;
        node->nextpost = postshead->nextpost;
        postshead->nextpost = node;
    }
    return node;
}

accounts *finduser(char *username, accounts *userhead);

int check(char *username, char *pass, accounts *accountsHead, int checkwhich); // gets a number (checkwhich) and checks if the given username or password matches any username/pass or not
char *signup(char *username, char *pass, accounts *accountsHead);//creates a node and give it to AddAcount
int login(char *username, char *pass, accounts *accountsHead); // checks username and pass and make the node the cur node 
void post(char *text, char *curuser, accounts *accountsHead);//finds the account by username and posts the given text
void info(char *username, accounts *accountsHead, int flag);
void delete(int postnum, accounts *user);
void like(char *username, int postnum, accounts *accountsHead);

int main()
{

    int log = 0;
    // commands :
    char su[] = "signup", li[] = "login", lk[] = "like", pst[] = "post", inf[] = "info", lo[] = "logout", del[] = "delete", fu[] = "find_user";
   
    accounts *accountsHead = (accounts *)malloc(sizeof(accounts)); // creates a dummy node for accounts linked-list
    accountsHead->user = " ";
    accountsHead->pass = " ";
    accountsHead->postnum = 0;
    accountsHead->nextaccount = NULL;

    char *cur;
    while (TRUE)
    {

        char *input = (char *)malloc(sizeof(char)); // we get a string by Dynamic-m-a with malloc and realloc
        char inputch;
        int counter;
        int flag = 0;
        printf(" Dear User Enter your command \n");

        inputch = getchar();
        for (counter = 0; inputch != '\n'; counter++) 
        {
            if (input == '\0')
            {
                printf("Error ! couldn't allocate memmory!\n");
            }
            else
            {
                input = (char *)realloc(input, ((counter + 2) * sizeof(char)));
                *(input + counter) = inputch;
                inputch = getchar();
            }
        }
        *(input + counter) = '\0'; // The end of string should be Null 
        counter = 0;

        char *sepinput[3];

        sepinput[0] = strtok(input, " ");
        if ((strcmp(pst, sepinput[0])) == 0) // if the command is post then the next part is continued until ENTER is pressed
        {
            sepinput[1] = strtok(NULL, "\n");
        }
        else 
        {
            sepinput[1] = strtok(NULL, " ");
            sepinput[2] = strtok(NULL, " ");
        }

        if (log == 1)
        {

            if (strcmp(su, sepinput[0]) == 0)
            {
                printf(" to signup  a New account you should logout from this account \n");
            }
            else if (strcmp(li, sepinput[0]) == 0)
            {
                printf(" to login  another account you should logout from this account \n");
            }
            else if (strcmp(lk, sepinput[0]) == 0)
            {
                like(sepinput[1], atoi(sepinput[2]), accountsHead);
            }
            else if (strcmp(pst, sepinput[0]) == 0)
            {
                post(sepinput[1], cur, accountsHead);
            }
            else if (strcmp(inf, sepinput[0]) == 0)
            {
                info(cur, accountsHead, 0);
            }
            else if (strcmp(lo, sepinput[0]) == 0)
            {
                printf("GoodBye =)  \n");
                log = 0;
            }
            else if (strcmp(fu, sepinput[0]) == 0)
            {
                info(sepinput[1], accountsHead, 1);
            }
            else if (strcmp(del, sepinput[0]) == 0)
            {
                delete (atoi(sepinput[1]), finduser(cur, accountsHead));
            }
            else
            {
                printf(" Command not found plz try again \n");
            }
        }
        if (log == 0) // if you haven't logged in into your account : 
        {
            if (strcmp(su, sepinput[0]) == 0)
            {
                signup(sepinput[1], sepinput[2], accountsHead);
            }
            else if (strcmp(li, sepinput[0]) == 0)
            {
                if (login(sepinput[1], sepinput[2], accountsHead) == 1)
                {
                    cur = sepinput[1];
                    log = 1;
                }
            }
            else if (strcmp(lk, sepinput[0]) == 0)
            {
                printf("Plz Login first\n");
            }
            else if (strcmp(pst, sepinput[0]) == 0)
            {
                printf("Plz Login first\n");
            }
            else if (strcmp(inf, sepinput[0]) == 0)
            {
                printf("Plz Login first\n");
            }
            else if (strcmp(lo, sepinput[0]) == 0)
            {
                printf("Plz Login first \n");
            }
            else if (strcmp(del, sepinput[0]) == 0)
            {
                printf("Plz Login first \n");
            }
            else if (strcmp(fu, sepinput[0]) == 0)
            {
                printf("Plz Login first \n");
            }
            else
            {
                printf(" Command not found plz try again \n");
            }
        }
    }
}
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
accounts *finduser(char *username, accounts *userhead) // if the given username was found , it will return the related node 
{
    accounts *node = userhead;
    while (node != NULL)
    {
        if (strcmp(node->user, username) == 0)
        {
            return node;
        }

        node = node->nextaccount;
    }
    return NULL;
}
