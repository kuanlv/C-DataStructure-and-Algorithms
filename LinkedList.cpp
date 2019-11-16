// Kuan Lyu LinkedList //
// 11/11/2019 //

#include <iostream>
#include <fstream>
using namespace std;

class LinkedList {
private:
    class Node {
    public:
        int value;
        Node* next;
        explicit Node (int v){
            value = v;
            next = nullptr;
        }
    };
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }
    ~LinkedList() {
        for (Node* temp = head; temp != nullptr;){
            Node* p = temp;
            temp = temp -> next;
            delete p;
        }
    }

    void addStart (int value) {
        if (head == nullptr) {
            head -> value = value;
            return;
        }
        Node* node = new Node(value);
        node -> next = head;
        head = node;
    }


    void addEnd(int value) {
        Node* node = new Node(value);
        if (head == nullptr){
            head = node;
            return;
        }
        Node* temp = head;
        while (temp -> next != nullptr){
            temp = temp -> next;
        }
        temp -> next = node;
    }

    void display() {
        if (head == nullptr) {
            cout << "empty" <<endl;
            return;
        }
        Node* temp = head;
        while (temp -> next != nullptr) {
            cout << temp -> value << " -> ";
            temp = temp -> next;
        }
        cout << temp -> value << endl;
    }

    LinkedList(const LinkedList& orig) {
        if (orig.head == nullptr) {
            head = nullptr;
            return;
        }
        head = new Node(orig.head -> value);
        Node* temp = head;
        for (Node* p = orig.head -> next; p != nullptr; p = p->next, temp = temp -> next) {
            temp -> next = new Node(p -> value);
        }
    }

    int getSize () {
        if (head == nullptr) return 0;
        int res = 0;
        Node* temp = head;
        while (temp != nullptr){
            res++;
            temp = temp -> next;
        }
        return res;
    }

    void Insert (int data, int position) {
        if (position == 0){
            addStart(data);
            return;
        }
        int size = getSize();
        if (position > size + 1) {
            cout << "out of bounds" << endl;
            return;
        }
        if (position == size + 1){
            addEnd(data);
            return;
        }
        Node* dummy = new Node(-1);
        dummy -> next = head;
        while (dummy -> next != nullptr and position != 0) {
            dummy = dummy -> next;
            position--;
        }
        if (position == 0){
            Node* node = new Node(data);
            node -> next = dummy -> next;
            dummy -> next = node;
        }
    }

    Node* gettail() {
        if (head == nullptr) {
            cout << "empty" << endl;
            return nullptr;
        }
        Node* temp = head;
        while (temp -> next != nullptr)
            temp = temp -> next;
        return temp;
    }

    void removeAndSave(LinkedList& empty) {
        if (head == nullptr){
            cout << "error" << endl;
            return;
        }
        Node* dummy = new Node(-1);
        dummy -> next = head;
        Node* temp = dummy;
        while (temp -> next != nullptr) {
            if (temp -> next -> value % 2 == 0){
                empty.addEnd(temp -> next -> value);
                temp -> next = temp -> next -> next;
            }else
                temp = temp -> next;
        }
        head = dummy -> next;
    }

    void InsertBack (LinkedList& b) {
        if (head == nullptr){
            head = b.head;
            return;
        }
        int index = 0;
        Node* tail = gettail();
        Node* tempA = head;
        Node* tempB = b.head;
        while (tempB != nullptr and tempA != tail) {
            if (index % 2 == 0) {
                Insert(tempB -> value, index);
                tempB = tempB -> next;
            }
            index++;
        }
        if (tempA == tail and tempB != nullptr) {
            while (tempB != nullptr){
                addEnd(tempB -> value);
                tempB = tempB -> next;
            }
        }

    }

};


int main() {
    LinkedList a;
    LinkedList b;
    ifstream infile;
    int x;
    infile.open("hw5.dat");
    if (infile.is_open()) {
        while (!infile.eof()) {
            infile >> x;
            a.addEnd(x);
        }
    }else {
        cout << "not open" << endl;
        return 0;
    }
    a.removeAndSave(b);
    a.InsertBack(b);
    a.display();
}