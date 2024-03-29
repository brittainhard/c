/**
 * As-is, straight from K&R.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101


struct nlist {
    struct nlist *next;
    char *name;

    // Hash
    char *defn;
};


unsigned char hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

static struct nlist *hashtab[HASHSIZE];

unsigned char hash(char *s)
{
    unsigned hashval;

    for(hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for(np = hashtab[hash(s)]; np != NULL; np = np -> next){
        if(strcmp(s, np -> name) == 0){
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if((np = lookup(name)) == NULL){
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np -> name = strdup(name)) == NULL){
            return NULL;
        }
        hashval = hash(name);
        np -> next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np -> defn);
    }
    if((np -> defn = strdup(defn)) == NULL){
        return NULL;
    }
    return np;
}

int main(int argc, char *argv[])
{
    return 0;
}
