// Implements a dictionary's functionality


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table 2^16
const unsigned int N = 65536;

// Hash table
node *table[N];
int wordcount=0;


//declare empty head
node *head = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int length =strlen(word);
    char copy[length+1]; // take a byte extra for NTC
    copy[length] = '\0'; // necessary to add the ntc after allocating space to it

// not converting gave errors to :) handles min length (1-char) words

 for (int i = 0; i < length; i++) // we take the word and LC and save that into copy
    {
        copy[i] = tolower(word[i]);
    }


       int hashcode=hash(copy); // get a hashcode for that copy
       node *tmp=table[hashcode]; // take a pointer tmp to point at what that array of hashcode is pointing
       if(tmp==NULL) // if tmp points to null return
       {
           return false;
       }

       while(tmp!=NULL) // do it until the ll ends
       {
           if(strcasecmp(tmp->word,copy)==0) // check case insesnitive for word in node to our word(copy)
           {
               return true; // if found
           }

                tmp=tmp->next; // else move to next node, traverse the ll
        }

       return false; // if not found copy until end
}

//https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/ this was for a prior one that I altered later to ^


unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    int c = *word;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
   FILE *file=fopen(dictionary,"r"); // open dict and read it, pointer to it is file
   if(file==NULL) // if the pointer points to null return
   {
       return false;
   }
   {
       // assign a buffer of size 1 for NTC
      char buffer[LENGTH+1];
       while(fscanf(file,"%s",buffer)!=EOF) // until eof
       {

       node *n=malloc(sizeof(node)); // allot memory for n
          if(n==NULL) // check if memory is alloted
          {

            fclose(file);
           return false;
          }

         else // if yes
          {

              strcpy(n->word,buffer); // copy word from buffer to word field of node n

           n->next=NULL; // at first the n node points to null

           unsigned int index =hash(buffer); // hash the word in buffer to get index of array

           // our current node points to what array is pointing at and then the array points to our node
           // even if our array points to null then this node points to null, it is better than initializing the array to null and then taking if/else

               n->next=table[index]; // this is done to avoid orphaning rest of the ll
               table[index]=n; // it gets inserted in beginning of ll

           wordcount++; // increment the word count until eof

             }
       }
       fclose(file);
       return true;
   }


}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount; // we had a counter for this in load after word was read,copied and added to ll
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i=0;i<N;i++) // loop thru all the arrays
   {
    // tmp1 is like a cursor that points to each node while tmp2 is the pointer that frees the prior node
    node *tmp1=table[i]; // initially tmp1 points to 1st node
    while(tmp1!=NULL) // until end of ll
        {
           node *tmp2 = tmp1; // tmp2 points to what tmp1 points
            tmp1 = tmp1 -> next; // tmp1 points to next node
            free(tmp2); // tmp2 frees the prior node
        }
   }

    return true;
}