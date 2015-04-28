#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// function to cipher text with moving keys
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Retry with 1 numerical argument for key: \n");
        return 1;
    }
    else
    {
        int keylen = strlen(argv[1]);
        int keys[keylen];
        for (int i = 0; i < keylen; i++)
        {            
            char k = argv[1][i];
            if (!isalpha(k))
            {
                printf("Retry key with all letters: \n");
                return 1;
            
            }
            else
            {
                if (isupper(k))
                {
                    keys[i] = k - 'A';
                }
                else
                {
                    keys[i] = k - 'a';
                }  
            } 
        }
        string text = GetString();
        int keyindex = 0;
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            char letter = text[i];
            if (!isalpha(letter))
            {
                printf("%c", letter);
            }
            else
            {
                if (isupper(letter))
                {
                    printf("%c", 'A' + (letter + keys[keyindex] - 'A') % 26);
                }
                else
                {
                    printf("%c", 'a' + (letter + keys[keyindex] - 'a') % 26);
                }  
                keyindex = (keyindex + 1) % keylen;
            }
        }
        printf("\n");
    }
    return 0;
}

