#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int loser, int winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        for (int g = 0; g < candidate_count; g++)
        {
            printf("%i \n", ranks[g]);
        }

        record_preferences(ranks);

        for (int h = 0; h < candidate_count; h++)
        {
            for (int e = 0; e < candidate_count; e++)
            {
                printf("%i", preferences[h][e]);
            }

            printf("\n");
        }

        printf("\n");
    }

    add_pairs();

    for (int h = 0; h < candidate_count; h++)
    {

        printf("%i", pairs[h].winner);
        printf("%i \n", pairs[h].loser);

    }

    printf("%i\n", pair_count);



    sort_pairs();

    for (int p = 0; p < candidate_count; p++)
    {

        printf("%i", pairs[p].winner);
        printf("%i \n", pairs[p].loser);

    }

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Compare the candidates names and add the rank into the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loops through the ranks array and compared each item to the other ones
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop through the preferences array and compare ith & jth and jth & ith votes
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;
            }

        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // use merge sort argorithm to do the job

    int maximum;
    pair swap;

    for (int i = 0; i < pair_count - 1; i++)
    {
        maximum = i;

        for (int j = i + 1 ; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[maximum].winner][pairs[maximum].loser])
            {
                maximum = j;
            }

        }

        swap = pairs[i];
        pairs[i] = pairs[maximum];
        pairs[maximum] = swap;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // go through each paid, check for any cycles and lock the pairs

    for (int i = 0; i < pair_count; i++)
    {
        if(check_cycle(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Check for a cycle recursively

//Look at a pair
//If the loser is not a winner in any existing locked pair, then lock the pair
//If the loser is a winner in an existing locked pair:
//Look at that pair
//If the loser is not a winner in any existing locked pair, then lock the pair
//If the loser is a winner in an existing locked pair:
//Look at that pair
//etc, etc etc . . .


bool check_cycle(int winner, int loser)
{
    // base case. if path exists, return true
    if (loser == winner)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true)
        {
            if (check_cycle(i, loser) == false)
            {
                return false;
            }
        }
    }

    return true;

}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool iswinner;

    for (int i = 0; i < candidate_count; i++)
    {

        iswinner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                iswinner = false;
            }

            if (iswinner)
            {
                printf("%s\n", candidates[i]);
            }

        }

    }

    return;
}

