#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string getString(); //Получить строку
void printStatistic(); //Вывести статистику по строке

int main(void) {
    printStatistic(getString());    
}

string getString() {
    printf("vvedi stroku:");
    return get_string();
}

void printStatistic(string text) {
    char str['Z']; //Массив для количества повторений букв
    int max_val = 0; //Переменная для макс количество повторений
    
    //Обнуляем массив
    for (int i = 'A'; i <= 'Z'; i++) {
        str[i]=0;
    }
    
    //Заносим количество букв в массив
    for (int i = 0, n = strlen(text); i < n; i++) {
        str[toupper(text[i])]+=1;
        if (str[toupper(text[i])] > max_val) { //Запоминаем макс количество повторений
            max_val = str[toupper(text[i])];
        }
    }
    
    //Выводим  массив с буквами количество которых больше нуля, отсортированых по количеству повторений
    for (int j=max_val; j > 0; j--) { //Для каждого повторения
        for (int i = 'A'; i <= 'Z'; i++) { //Ищем нужный символ и выводим его.
            if (str[i]==j) {
                printf("%c - %i\n",i,str[i]);
            }
        }
    }
}