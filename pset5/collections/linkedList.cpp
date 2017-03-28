#include <iostream>

using namespace std;

class Node {
private:
    int data;
    Node* next;

public:
    Node() {
        this->data = 0;
        this->next = NULL;
    }

    ~Node() {

    }

    int getData() {
        return data;
    }

    void setData(int data) {
        this->data = data;
    }

    Node* getNext() {
        return this->next;
    }

    void setNext(Node* node) {
        this->next = node;
    }


};

class linkedList {
private:
    Node* root;
    Node* last;
    int sizeOfList;

public:
    linkedList() {
        root = new Node;
        sizeOfList = 0;
        last = root;
    }

    ~linkedList() {
        for(int i=0;i<sizeOfList;i++) {
            remove(1);
        }
    }

    void add(int data) {
        Node* current;
        current = getLast(root);
        Node* node = new Node;
        node->setData(data);
        current->setNext(node);
        sizeOfList++;
    }

    Node* getLast(Node* node) {
        Node* current;
        current=node;
        if (current->getNext() == NULL) {
            return current;
        }
        return getLast(current->getNext());
    }

    int getValByIndex(int index) {
        Node* current = root;
        if (index>=0 && index<=sizeOfList) {
            for (int i=0;i<index;i++) {
                current = current->getNext();
            }
            return current->getData();
        }
        else {
            throw("Index out of bounds");
        }
        return 0;
    }

    Node* getNodeByIndex(int index) {
        Node* current = root;
        if (index>=0 && index<=sizeOfList) {
            for (int i=0;i<index;i++) {
                current = current->getNext();
            }
            return current;
        }
        else {
            throw("Index out of bounds");
        }
        return NULL;
    }

    void remove(int index) {
        if (index>0) {
            Node* forRemove = this->getNodeByIndex(index);
            Node* prevNode = this->getNodeByIndex(index - 1);
            prevNode->setNext(forRemove->getNext());

            delete forRemove;

            sizeOfList--;
        }
    }

    int getSizeOfList() {
        return sizeOfList;
    }

    void showList() {
        Node* current = root->getNext();
        for (int i=0;i<sizeOfList;i++) {
            cout << current->getData() << ' ';
            current = current->getNext();
        }
    }
};

int main()
{
    linkedList* list = new linkedList;
    for (int i=0;i<20;i++) {
        list->add(i);
    }
    cout << list->getValByIndex(10) << endl;
    list->remove(10);
    list->showList();

    delete list;
    return 0;
}
