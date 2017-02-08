#include <cs50.h>
#include <stdio.h>

//Константы
const int WHATER_CONSUMPTION_PER_MINUTE = 12;

//Функции
int getMinutes(); //Запрос ввода минут
int getBottlesNumber(); //Получение количества бутылок в зависимости от времени и расхода.
void showBottles(); //Вывоб еличества бутылок

int main(void) {
    showBottles(getBottlesNumber(getMinutes())); //Делаем все хорошо, и утопично! Без переменных.
    return 0;
}

int getMinutes() {
    printf("Minutes: ");
    return get_int();
}

int getBottlesNumber(int minutes) {
    return WHATER_CONSUMPTION_PER_MINUTE * minutes;
}

void showBottles(int count) {
    printf("Bottles: %i\n",count);
}