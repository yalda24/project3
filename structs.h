
#ifndef STRUCTS
#define STRUCTS

typedef struct posts
{
    char *user;
    int postnum;
    int likenum;
    char *text;
    struct posts *nextpost;
} posts;
typedef struct accounts
{
    char *user;
    char *pass;
    int postnum;
    struct accounts *nextaccount;
    posts *postshead;

} accounts;

#endif
