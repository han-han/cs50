#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// function to print initial letters
int main(void)
{
    //printf("Input name strings: \n");
    string names = GetString();
    bool flag = true;
    int n = strlen(names);
    if (n >= 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (flag && names[i] != ' '){
                printf("%c", toupper(names[i]));
                flag = false;
            }
            else if (!flag && names[i] == ' ')
            {
                flag = true;
            }    
        }
    }
    printf("\n");
}
