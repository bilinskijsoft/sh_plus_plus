#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

const int DEFAULT_ARRAY_SIZE = 50;
const int DEFAULT_ARRAY_SIZE_MULTIPLIER = 2;
const char* DICTIONARY_PATH = "large.txt";

class timer {
private:
    unsigned int startTime, endTime;
public:
    void start() {
        startTime = clock();
    }

    void finish() {
        endTime = clock();
        cout << "Done. Time: " << endTime - startTime << "ms." << endl;
    }
};

class arrayList {
private:
    string *array;
    int size;
    int lastElementIndex;

    void resizeArray() {
        string *tmpArray = new string[size * DEFAULT_ARRAY_SIZE_MULTIPLIER];
        for (int i = 0; i < size; i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = size * DEFAULT_ARRAY_SIZE_MULTIPLIER;
    }

    void resizeArray(int arraySizeMultiplier) {
        string *tmpArray = new string[size * arraySizeMultiplier];
        for (int i = 0; i < size; i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = size * arraySizeMultiplier;
    }

    void fitArraySize() {
        string *tmpArray = new string[lastElementIndex];
        for (int i=0;i<lastElementIndex;i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = lastElementIndex;
    }

public:

    arrayList() {
        array = new string[DEFAULT_ARRAY_SIZE];
        size = DEFAULT_ARRAY_SIZE;
        lastElementIndex = 0;
    }

    arrayList(int sizeOfArray) {
        array = new string[sizeOfArray];
        size = sizeOfArray;
        lastElementIndex = 0;
    }

    ~arrayList() {
        delete array;
    }

    void add(string value) {
        if (lastElementIndex == size) {
            resizeArray();
        }
        array[lastElementIndex] = value;
        lastElementIndex++;
    }

    void set(int index, string value) {
        if (index >= 0 && index <= size) {
            array[index] = value;
        }
        else {
            throw("Index out of bounds!");
        }
    }

    string get(int index) {
        if (index >= 0 && index <= size) {
            return array[index];
        }
        else {
            throw("Index out of bounds!");
        }
    }

    void remove(int index) {
        if (index >= 0 && index <= size) {
            for (int i = index; i < size; i++) {
                array[i] = array[i+1];
            }
            lastElementIndex--;

        }
        else {
            throw("Index out of bounds!");
        }
    }

    void show(int index) {
        if (index >= 0 && index <= size) {
            cout << array[index] <<endl;
        }
        else {
            throw("Index out of bounds!");
        }
    }

    void showAllList() {
        for (int i=0; i<lastElementIndex; i++) {
            cout << array[i] << endl;
        }
        cout << endl;
    }

    int getSize() {
        return size;
    }

    int getLastElemntIndex() {
        return lastElementIndex;
    }

    void fitSize() {
        fitArraySize();
    }

    bool search(string data) {
        for (int i=0;i<size;i++) {
            if (array[i]==data) {
                return true;
            }
        }
        return false;
    }
};


class fileLoader {
private:
    ifstream file;
public:
    fileLoader() {
        file.open(DICTIONARY_PATH);
        checkFile();
    }

    void checkFile() {
        if (!file.is_open()) {
            cout << "Cold not open file!" << endl;
            throw 1;
        }
    }

    arrayList* loadFile() {
        timer* timeCounter = new timer;
        string word;
        arrayList* dictionary = new arrayList;

        cout << "Loading dictionary..." <<endl;
        timeCounter->start();

        while(!file.eof()) {
            file >> word;
            dictionary->add(word);
        }

        file.close();

        timeCounter->finish();
        return dictionary;
    }
};

class speller {
private:
    arrayList* dictionary;
    fileLoader* fLoader;
    arrayList* misspels;
    ifstream file;

    int wordsCount;
public:
    speller() {
        fLoader = new fileLoader;
        misspels = new arrayList();
        dictionary = fLoader->loadFile();

        wordsCount = 0;
    }

    void check(string word) {
        cout << dictionary->search(word) << endl;
    }

    arrayList* loadFileForCheck(char* path) {
        string word;
        arrayList* words = new arrayList;
        timer* timeCounter = new timer;

        cout << "Loading text..." <<endl;
        timeCounter->start();
        file.open(path);

        if (!file.is_open()) {
            cout << "Cold not open file!" << endl;
            throw 1;
        }

        while(!file.eof()) {
            file >> word;
            words->add(word);
            wordsCount++;
        }

        file.close();

        words->fitSize();

        timeCounter->finish();
        return words;
    }

    void checkForMisspelings(arrayList* words) {
        timer* timeCounter = new timer;
        cout << "Checking text for misspels, please wait..." << endl;
        timeCounter->start();
        for (int i=0, sizeOfWords=words->getLastElemntIndex(); i<sizeOfWords; i++) {
            if (!dictionary->search(optiWord(words->get(i)))) {
                misspels->add(optiWord(words->get(i)));
            }
        }
        timeCounter->finish();
        wordsCount = words->getSize();
        cout << endl << "MISSPELLED WORDS" << endl << endl;
        misspels->fitSize();
        misspels->showAllList();
    }

    string optiWord(string word) {
        for (unsigned int i = 0; i < word.length(); i++){
			if (isalpha(word[i]) || word[i]=='-' || word[i]==39) {
				word[i] = tolower(word[i]);
			}
			else {
                word.erase(i,1);
                i--;
			}
		}
		return word;
    }

    void printStatistic() {
        dictionary->fitSize();
        cout << "WORDS MISSPELLED:     " << misspels->getSize() << endl;
        cout << "WORDS IN DICTIONARY:  " << dictionary->getSize() << endl;
        cout << "WORDS IN TEXT:        " << wordsCount << endl;
    }

    char* promptForFilename() {
        char* fileName = new char;
        cout << "Input filename:";
        cin.getline(fileName,255);
        return fileName;
    }
};


int main()
{
    speller* spellerObj = new speller;
    spellerObj->checkForMisspelings(spellerObj->loadFileForCheck(spellerObj->promptForFilename()));

    spellerObj->printStatistic();

    return 0;
}
