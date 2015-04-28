/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // linear research
    if (n < 0)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (values[i] == value)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // a O(n^2) sorting algorithm: bubble sort
    int temp; 
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n - 1; j++)
        {
            if (values[j] > values[j+1])
            {
                temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
     
    return;
}
