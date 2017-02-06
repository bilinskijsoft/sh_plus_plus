#include <cs50.h>
#include <stdio.h>

int main(void) {
    const int max_height = 23;
    int height = 0;
    int sharps = 0;
    int spaces = 0;
    
    //Проверяем на правильность ввода.
    do {
        printf("Height: ");
        height = get_int();
    } while (height < 0 || height > max_height);
    
    //Вывод строк пирамидки
    for (int i=0; i<height; i++) {
        //Вычисление необходимого кол-ва пробелов и решоток для текущей строки.
        spaces = height - i - 1; 
        sharps = height - spaces;
        
        //Вывод пробелов перед решотками
        for (int x=0; x < spaces; x++) {
            printf(" ");
        }
        
        //Вывод решоток первой пирамидки
        for (int x=0; x < sharps; x++) {
            printf("#");
        }
        
        //Два прорбела между пирамидками
        printf("  "); 
        
        //Вывод решоток второй пирамидки
        for (int x=0; x < sharps; x++) {
            printf("#");
        }
        
        //Перенос на следущую строку
        printf("\n");
        
    }
    return 0;
}