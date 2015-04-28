#include <stdio.h>
#include <cs50.h>

// function to print mario blocks
int main(void)
{
    printf("Input height: \n");
    int height = GetInt();
    while(height < 0 || height > 23)
    {
       printf("Retry: \n");
       height = GetInt();
    }
    for (int i = 2; i <= height + 1; i++)
    {
        for (int j = 1; j <= height + 1; j++)
        {
            if (j <= height + 1 - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
     printf("\n");   
     }   
}
