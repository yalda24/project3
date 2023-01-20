#include"structs.h"

int check(char *username, char *pass, accounts *accountsHead, int checkwhich); // gets a number (checkwhich) and checks if the given username or password matches any username/pass or not
char *signup(char *username, char *pass, accounts *accountsHead);//creates a node and give it to AddAcount
int login(char *username, char *pass, accounts *accountsHead); // checks username and pass and make the node the cur node 
void post(char *text, char *curuser, accounts *accountsHead);//finds the account by username and posts the given text
void info(char *username, accounts *accountsHead, int flag);
void delete(int postnum, accounts *user);
void like(char *username, int postnum, accounts *accountsHead);

