#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string getName(); //Запрос на ввод имени
void printInitials(); //Получить инициалы

int main(void) {
    printInitials(getName());   //Делаем все хорошо! 
}

string getName() {
    return get_string();
}

void printInitials(string name) {   
    for (int i=0, n = strlen(name); i<n;i++) {  //Перебираем каждый елемент строки
        if (isalpha(name[i])) {     //Если текущий елемент буква
            printf("%c",toupper(name[i]));   //Выводим символ, переведя его в верхний регистр
            
            while(name[i+1]!=' ' && i < n) {    //Пропускаем все остальное, пока не найдем пробел
                i++;
            }
        }
    }
    printf("\n");
}