#include <cs50.h>
#include <stdio.h>

int main(void) {
    printf("Water: "); //Запрос ввода
    int minutes = get_int();
    printf("Bottles: %i\n",minutes*12); //Вывод результата
}