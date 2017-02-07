#include <cs50.h>
#include <stdio.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>

bool card_check(long long number);

int main(void) {
    printf("Number: ");
    
    long long card_number = get_long_long();
    
    if (card_number < 1000000000000000 && card_number > 99999999999999 && card_check(card_number)) { //AMEX
        printf("AMEX\n");
    }
    else if (card_number < 10000000000000000 && card_check(card_number)){ //Visa или MasterCard
        if (card_number / 1000000000000000 == 4) { //Visa
            printf("VISA\n");
        } 
        else {
            printf ("MASTERCARD\n");   
        }
    }
    else {
        printf("INVALID\n");
    }
}

bool card_check(long long number) {
    long long tmp_number = number;
    int num_count = 0;
    int sum = 0;
    
    do {
        num_count++;
        if (num_count % 2 == 0) {
            int tmp_sum = (tmp_number % 10)*2;
            if (tmp_sum > 9) {
                sum += (tmp_sum % 10)+((tmp_sum / 10) % 10);
            }
            else {
                sum += tmp_sum;   
            }
        }
        else {
            sum += (tmp_number % 10);
        }

        tmp_number = tmp_number /10;
    } while (tmp_number > 0);
    
    if (sum % 10 == 0) {
        return true;
    }
    return false;
}