#include <iostream>
#include <cstring>

using namespace std;

const int MAP_SIZE = 50000;

class hashMap {
private:
    int sizeOfMap;
    string hashTable[MAP_SIZE];

    unsigned int getHash(string str) {

        int seed = 131;
        unsigned int hash = 0;
        for(unsigned int i = 0; i < str.length(); i++) {
          hash = (hash * seed) + str[i];
        }
        return hash % MAP_SIZE;
    }

public:
    hashMap() {
        sizeOfMap = 0;
    }

    void add(string str) {
        hashTable[getHash(str)] = str;
        sizeOfMap++;
    }

    void remove(string str) {
        if (hashTable[getHash(str)]==str) {
            for (int i=getHash(str);i<MAP_SIZE-1;i++) {
                hashTable[i] = hashTable[i+1];
                sizeOfMap--;
            }
        }
    }

    void isInMap(string str) {
        if (hashTable[getHash(str)]==str) {
            cout << "Found " << str << "!" << endl;
        }
        else {
            cout << "Not found " << str << "!" << endl;
        }
    }

    int getSizeOfMap() {
        return sizeOfMap;
    }

    void showMap() {
        for (int i=0;i<MAP_SIZE;i++) {
            if (!hashTable[i].empty()) {
                cout << hashTable[i] << endl;
            }
        }
    }


};

int main()
{
    hashMap* hashMapClass = new hashMap;

    hashMapClass->add("hello");
    hashMapClass->add("tralala");
    hashMapClass->add("trololo");
    hashMapClass->add("goose");
    hashMapClass->add("1337_cr3w");
    hashMapClass->add("abcd");
    hashMapClass->add("kowo");
    hashMapClass->add("shpp");
    hashMapClass->add("world");

    hashMapClass->showMap();

    hashMapClass->remove("kowo");

    hashMapClass->showMap();

    hashMapClass->isInMap("trololo");
    hashMapClass->isInMap("lalalalal");
    hashMapClass->isInMap("adsfasfadsf");

    return 0;
}
