#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

bool key_validation(string key);
string coding(string plaintext, string key);

int main(int argc, string argv[])
{

    // check for the validity of input
    if (argc < 2)
    {
        printf("No key entered\n");
        return 1;
    }

    bool validation = key_validation(argv[1]);

    // check for the validity of input
    if (validation == false)
    {
        printf("Wrong Key\n");
        return 1;
    }

    string plaintext = get_string("plaintext ");

    string ciphertext = coding(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);

}

bool key_validation(string key)
{

    // string length

    int length = strlen(key);


    // check the length of the string is 26 characters
    if (length != 26)
    {
        return false;
    }

    // check the characters are alphabetic
    for (int i = 0; i < length; i++)
    {
        if (isalpha(key[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    // convert all characters to uppercase
    for (int j = 0; j < length; j++)
    {
        key[j] = toupper(key[j]);
    }

    // check the characters are not repeating
    for (int k = 0; k < length - 1; k++)
    {
        for (int l = k + 1; l < length; l++)
        {
            if (key[k] == key[l])
            {
                return false;
            }
        }
    }

    return true;
}

//encypher the plaintext function
string coding(string plaintext, string key)
{
    // identify the length of a string
    int length = strlen(plaintext);
    string ciphertext = plaintext;

    for (int i = 0; i < length; i++)
    {
        //get the position and assign the key letter to ciphertext
        if (isupper(plaintext[i]))
        {
            int position = plaintext[i] - 65;
            ciphertext[i] = key[position];
        }
        else if (islower(plaintext[i]))
        {
            int position = plaintext[i] - 97;
            ciphertext[i] = tolower(key[position]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }

    }

    return ciphertext;
}