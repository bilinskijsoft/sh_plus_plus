#include <cs50.h>
#include <stdio.h>
//Константы
const int MIN_HEIGHT = 0;
const int MAX_HEIGHT = 23;

int getHeight(); //Запрос ввода высоты
void showRow(); //Вывести строку пирамидки в зависимости от номера и высоты
void showPyramid(); //Вывести пирамидку.

int main(void) {
    showPyramid(getHeight()); //Делаем все хорошо, но увы с переменными.
    return 0;
}

int getHeight() {
    int height = 0;
    do {
        printf("Height: ");
        height = get_int();
    } while (height < MIN_HEIGHT || height > MAX_HEIGHT); //Проверка вваода по условию
    return height;
} 

void showRow(int number, int height) {
    int sharps = 0;
    int spaces = 0;
    
    //Вычисление необходимого кол-ва пробелов и решоток для строки.
    spaces = height - number - 1; 
    sharps = height - spaces;
    
    //Вывод пробелов перед решотками
    for (int x=0; x < spaces; x++) {
        printf(" ");
    }
        
    //Вывод решоток первой половины пирамидки
    for (int x=0; x < sharps; x++) {
        printf("#");
    }
    
    //Два прорбела между половинками
    printf("  "); 
    
    //Вывод решоток второй половины пирамидки
    for (int x=0; x < sharps; x++) {
        printf("#");
    }
    
    //Перенос на следущую строку
    printf("\n");
}

void showPyramid(int height) {
    for (int i = 0; i<height; i++) {
        showRow(i,height);
    }
} 