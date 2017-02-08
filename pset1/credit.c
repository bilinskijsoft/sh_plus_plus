#include <cs50.h>
#include <stdio.h>

long long checkCardNumber(); //Проверка валидности номера карты
long long getCardNumber(); //Запрос на ввод номера карты
int getCardType(); //Получить тип карты. Возвращает 1 - AMEX, 2 - Visa, 3 - MasterCard, 0 - Неправильно.
void showCardType(); //Вывести тип карты

int main(void) {
    showCardType(getCardType(checkCardNumber(getCardNumber()))); //Делаем все хорошо.
    return 0;
}

void showCardType(int type) {
    switch (type) {
        case 0:
            printf("INVALID\n");
            break;
        case 1:
            printf("AMEX\n");
            break;
        case 2:
            printf("VISA\n");
            break;
        case 3:
            printf("MASTERCARD\n");
    }    
}

int getCardType(long long number) {
    switch (number / 100000000000000) { //Проверяем первые цыфры номера
        case 3: //AMEX
            return 1; 
            break;
        case 40: //Visa
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46: 
        case 47:
        case 48:
        case 49:
            return 2;
            break;
        case 51: //MasterCard
        case 52:
        case 53:
        case 54:
        case 55:
            return 3;
            break;
        default:
            return 0;
            break;
    }   
}

long long getCardNumber() {
    printf("Number: ");
    return get_long_long();
}

long long checkCardNumber(long long number) {
    long long tmp_number = number;  //Создаем временную переменную для номера карты
    int num_count = 0;
    int sum = 0; //Сумма для проверки.
    
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
        return number;
    }
    
    return 0;
}