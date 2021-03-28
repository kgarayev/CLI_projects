#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// declare the functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int find_grade(double letters, double words, double sentences);

int main(void)
{
    // get text input
    string text = get_string("Text: ");

    // assign relevant values
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = find_grade(letters, words, sentences);


    // print the grade
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }


}

// count letters
int count_letters(string text)
{
    int counter = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            counter++;
        }

    }

    return counter;
}

// count words
int count_words(string text)
{
    int counter = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            counter++;
        }
    }

    return counter;

}

// count sentences
int count_sentences(string text)
{
    int counter = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }

    return counter;
}

// calculate grade
int find_grade(double letters, double words, double sentences)
{
    double L = 100 * letters / words;
    double S = 100 * sentences / words;
    double score = ((0.0588 * L) - (0.296 * S) - 15.8);
    int index = round(score);
    return index;
}