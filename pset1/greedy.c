#include <stdio.h>
#include <cs50.h>

// function to print mario blocks
int main(void)
{
    printf("Input cash amount: \n");
    float cash = GetFloat(); 
    while (cash < 0)
    {
        printf("Negative input, please retry:\n");
        cash = GetFloat();
    }
    int cashInCent = (int)(cash * 100 + 0.5);
    int numQ = (int) (cashInCent / 25);
    cashInCent -= 25 * numQ;
    int numD = (int) (cashInCent / 10);
    cashInCent -= 10 * numD;
    int numN = (int) (cashInCent / 5);
    cashInCent -= 5 * numN;
    int numP = cashInCent;
    int numTotal = numQ + numD + numN + numP;
    printf("%i\n", numTotal);
}
