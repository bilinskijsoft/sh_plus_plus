#include<iostream>

using namespace std;

const int DEFAULT_ARRAY_SIZE = 50;
const int DEFAULT_ARRAY_SIZE_MULTIPLIER = 2;

class arrayList {
private:
    int *array;
    int size;
    int lastElementIndex;

    void resizeArray() {
        int *tmpArray = new int[size * DEFAULT_ARRAY_SIZE_MULTIPLIER];
        for (int i = 0; i < size; i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = size * DEFAULT_ARRAY_SIZE_MULTIPLIER;
    }

    void resizeArray(int arraySizeMultiplier) {
        int *tmpArray = new int[size * arraySizeMultiplier];
        for (int i = 0; i < size; i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = size * arraySizeMultiplier;
    }

    void fitArraySize() {
        int *tmpArray = new int[lastElementIndex];
        for (int i=0;i<lastElementIndex;i++) {
            tmpArray[i] = array[i];
        }

        array = tmpArray;
        size = lastElementIndex;
    }

public:

    arrayList() {
        array = new int[DEFAULT_ARRAY_SIZE];
        size = DEFAULT_ARRAY_SIZE;
        lastElementIndex = 0;
    }

    arrayList(int sizeOfArray) {
        array = new int[sizeOfArray];
        size = sizeOfArray;
        lastElementIndex = 0;
    }

    ~arrayList() {
        delete array;
    }

    void add(int value) {
        if (lastElementIndex == size) {
            resizeArray();
        }
        array[lastElementIndex] = value;
        lastElementIndex++;
    }

    void set(int index, int value) {
        if (index >= 0 && index <= size) {
            array[index] = value;
        }
        else {
            throw("Index out of bounds!");
        }
    }

    int get(int index) {
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
            cout << array[i] << ' ';
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
};

int main() {
    arrayList array;

    for (int i=0;i<20;i++) {
        array.add(i);
    }
    array.fitSize();
    array.showAllList();
    cout << array.get(12) << endl;
    array.set(12,345);
    array.show(12);
    array.remove(12);
    array.showAllList();

    return 0;
}
