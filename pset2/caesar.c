#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// function to cipher text
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Retry with 1 numerical argument for key: \n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        string text = GetString();
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (!isalpha(text[i]))
            {
                printf("%c", text[i]);
            }
            else
            {
                if (isupper(text[i]))
                {
                    printf("%c", 'A' + (text[i] + k - 'A') % 26);
                }
                else
                {
                    printf("%c", 'a' + (text[i] + k - 'a') % 26);
                }   
            }
        }
        printf("\n");
    }
    return 0;
}
