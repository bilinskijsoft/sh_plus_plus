#include <cs50.h>
#include <stdio.h>

bool card_check(long long number);

int main(void) {
    //Запрос номера карты
    printf("Number: ");
    long long card_number = get_long_long();
    
    if (card_number < 1000000000000000 && card_number > 99999999999999 && card_check(card_number)) { //AMEX
        printf("AMEX\n");
    }
    else if (card_number < 10000000000000000 && card_check(card_number)){ //Visa или MasterCard
        if (card_number / 1000000000000000 == 4) { //Visa
            printf("VISA\n");
        } 
        //MasterCard
        else if(card_number / 100000000000000 == 51 || card_number / 100000000000000 == 52 || card_number / 100000000000000 == 53 || card_number / 100000000000000 == 54 || card_number / 100000000000000 == 55){
            printf ("MASTERCARD\n");   
        }
        else {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }
    return 0;
}

bool card_check(long long number) {
    long long tmp_number = number;
    int num_count = 0;
    int sum = 0;
    
    do { //Перебираем все цыфры номера карты
        num_count++;
        if (num_count % 2 == 0) { //Четное число по порядку - умножаем на 2, если > 9 вычисляем сумму цыфр, добавляем в сумму
            int tmp_sum = (tmp_number % 10)*2;
            if (tmp_sum > 9) {
                sum += (tmp_sum % 10)+((tmp_sum / 10) % 10);
            }
            else {
                sum += tmp_sum;   
            }
        }
        else { //Нечетное число по порядку - просто добавляем в сумму
            sum += (tmp_number % 10);
        }

        tmp_number = tmp_number / 10;
    } while (tmp_number > 0);
    
    if (sum % 10 == 0) {//Если поседняя цыфра суммы 0 тогда номер карты правильный
        return true;
    }
    
    return false;
}