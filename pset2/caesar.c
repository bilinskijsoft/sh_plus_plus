#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool checkArgs();   //Проверка количества аргументов
bool isNegative();  //ПРоверка аргумента на негативность
string getText();   //Получить текст
void encryptChar(); //Зашифровать символ
string getCipher(); //Получить зашифрованный текст
void printCipheredText();   //Вывести текст

int main(int argc, string argv[]) {
    if (!checkArgs(&argc)) {
        return 1;
    } 
    if (!isNegative(atoi(argv[1]))) {
        return 1;
    }
    
    printCipheredText(getCipher(getText(),atoi(argv[1])));  //Делаем все хорошо
    
    return 0;
}

bool checkArgs(int* argc) {
    if (*argc == 2) {    //Если количество аргументов 2 тогда все хорошо
        return 1;
    }   
    printf("Usage: ./caeser k\n");  //Вывести подсказку
    return 0;
}

bool isNegative(int num) {
    if (num > 0) {  //Если аргумент больше нуля тогда все хорошо
        return 1;
    }
    printf("Usage: ./caeser k\n"); //Вывести подсказку
    return 0;
}

string getText() {
    printf("plaintext:");
    return get_string();
}

string getCipher(string text, int num) {
    while(num > 27) {   //Нормализуме число в интервал 1..26
        num = num - 26;
    }
    
    for (int i = 0, n = strlen(text); i<n; i++) { //Перебираем символы
        if (isalpha(text[i])) { //Если текущий сивол буква
            encryptChar(&text[i], &num);   
        }
    }   
    return text;
}

void encryptChar(char* inChar, int* key) {
    if (isupper(*inChar)) { //Шифруем и оставляем букву большой
        *inChar = ((*inChar - 'A' + *key) % 26)+'A';    
    }
    else {  //Шифруем и оставляем букву маленькой
        *inChar = ((*inChar - 'a' + *key) % 26)+'a';   
    }
}

void printCipheredText(string text) {
    printf("ciphertext: %s\n",text);
}