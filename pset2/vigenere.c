#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool checkArgs();   //Проверка количества аргументов
bool isAlphabet();  //Аргумент должен быть только из букв
void cryptChar();   //Зашифровать символ
string getText();   //Получить текст
string getCipher(); //Получить зашифрованный текст
void printCipheredText();   //Вывести текст

int main(int argc, string argv[]) {
    if (!checkArgs(argc)) {
        return 1;
    } 
    if (!isAlphabet(argv[1])) {
        return 1;
    }
    
    printCipheredText(getCipher(getText(),argv[1]));  //Делаем все хорошо
    
    return 0;
}

bool checkArgs(int argc) {
    if (argc == 2) {    //Если количество аргументов 2 тогда все хорошо
        return 1;
    }   
    printf("Usage: ./caeser k\n");  //Вывести подсказку
    return 0;
}

bool isAlphabet(string key) {
    for (int i = 0, n = strlen(key); i < n; i++) {
        if (!isalpha(key[i])) { //Проверяе строку ключа, если нашли цыфру значит неправильный ключ
            printf("Usage: ./caeser k\n"); //Вывести подсказку
            return 0;
        }
    }

    return 1;
}

string getText() {
    printf("plaintext:");
    return get_string();
}

string getCipher(string text, string key) {
    int j = 0; //Счетчик для ключа
    for (int i=0, n=strlen(text); i < n; i++) { //Перебор символов строки
        if (isalpha(text[i])) { //Если текущий символ строка
            cryptChar(&text[i],&key[j]);
            if (j + 1 < strlen(key)) { //Идем к следуюзуй букве ключа
                j++;
            }
            else {
                j=0;    //Елси перебрали все буквы ключа, то начинаем сначала
            }
        }
    }
    return text;
}

void cryptChar(char* inChar, char* key) {
    if (isupper(*inChar)) { //Шифрование большой буквы
        *inChar = ((*inChar - 'A' + (toupper(*key) - 'A')) % 26)+'A';    
    }
    else {//Шифрование маленькой буквы
        *inChar = ((*inChar - 'a' + (toupper(*key) - 'A')) % 26)+'a';    
    }
}

void printCipheredText(string text) {
    printf("ciphertext: %s\n",text);
}