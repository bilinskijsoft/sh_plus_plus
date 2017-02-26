/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int left = 0;
    int right = n;

    while (!(left >= right))
    {
        int mid = left + (right - left)  / 2;
        if (values[mid] == value) {
            return true;
        }

        if (values[mid] > value) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Sorting with insertions algorythm

    
    for (int i = 1; i<=n-1;i++) { 
        int tmp = values[i];
        int j = i;
        while (j > 0 && values[j-1] > tmp) { 
            values[j] = values[j-1];
            j--;
        }
        values[j] = tmp;
    }
    return;
}
