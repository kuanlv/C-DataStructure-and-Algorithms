// Kuan Lyu 11/15/2019 //
// Trie and Hash //
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

// ************************* //
class Trie {

private:
    class Node{
    public:
        bool isWord;
        Node* next[26]{nullptr};
        Node():isWord(false) {
            for (auto& node: next) {
                node = nullptr;
            }
        }
    };

    static void deleteNode(Node* node) {
        for (auto& n : node->next) {
            if (n != nullptr)
                deleteNode(n);
        }
        delete node;
    }
    Node* root;
public:
    Trie() {root = new Node();}
    ~Trie() {
        Node* temp = root;
        for (auto& node: temp->next) {
            if (node != nullptr)
                deleteNode(node);
        }
        delete root;
    }

    void insert(string& word) {
        Node* temp = root;
        for (char c: word) {
            if (temp->next[c - 'a'] == nullptr)
                temp->next[c - 'a'] = new Node();
            temp = temp->next[c - 'a'];
        }
        temp->isWord = true;
    }

    bool search(string& word) {
        Node* temp = root;
        for (char c: word) {
            if (!temp->next[c - 'a'])
                return false;
            temp = temp->next[c - 'a'];
        }
        return (temp != nullptr and temp->isWord);
    }

    bool prefix(string& word) {
        Node* temp = root;
        for (char c: word) {
            if (!temp->next[c - 'a'])
                return false;
            temp = temp->next[c - 'a'];
        }
        return true;
    }

    friend bool hasNoChildren(Node* node) {
        for (auto& n: node->next) {
            if (n != nullptr)
                return false;
        }
        return true;
    }

    // remove string //
    friend bool deleteHelper(const string& key, Node* currentNode, int length, int level) {
        bool deletedSelf = false;
        if (currentNode == nullptr) {
            cout << "Key does not exist";
            return deletedSelf;
        }
        // base case: if we have reached at the node which points to the alphabet at the end of the key.
        if (level == length) {
            // if there are no nodes ahead of this node in this path
            // then we can delete this node
            if (hasNoChildren(currentNode)) {
                currentNode = nullptr;
                deletedSelf = true;
            }
                // if there are nodes ahead of this node in this path
                // then we cannot delete this node. We simply unmark this as leaf
            else {
                currentNode->isWord = false;
                deletedSelf = false;
            }
        }
        else {
            Node* childNode = currentNode->next[key[level] - 'a'];
            bool childDeleted = deleteHelper(key, childNode, length, level + 1);

            if (childDeleted) {
                // tricky
                // making children pointer also null: since child is deleted
                currentNode->next[key[level] - 'a'] = nullptr;

                // if this is leaf node that means this is part of another key
                // and hence we can not delete this node and it's parent path nodes
                if (currentNode->isWord) {
                    deletedSelf = false;
                }
                    // if childNode is deleted but if this node has more children then this node must be part of another key.
                    // we cannot delete this node
                else if (!hasNoChildren(currentNode)) {
                    deletedSelf = false;
                }
                    // else safely delete this node
                else {
                    currentNode = nullptr;
                    deletedSelf = true;
                }
            }
            else {
                deletedSelf = false;
            }
        }
        return deletedSelf;
    }

    void remove(const string& key) {
        if ((root == nullptr) || (key.length() == 0)){
            cout << "Null key or Empty trie error";
            return;
        }
        deleteHelper(key, root, key.length(), 0);
    }


    // print words indiscriminately //
    friend void printHelper(Node* node, char str[], int level) {
        if (node->isWord){
            str[level] = '\0';
            cout << str << " ";
        }
        for (int i = 0; i < 26; i++){
            if (node->next[i] != nullptr) {
                str[level] = char(i + 'a');
                printHelper(node->next[i], str, level + 1);
            }
        }
    }

    void print() {
        char str[40];
        printHelper(root, str, 0);
    }
    // print words indiscriminately //
    // print target words //
    friend void printCertainwordsHelper(Node* node, char str[], int level, string target) {
        if (node->isWord) {
            str[level] = '\0';
            cout << str << " ";
        }
        for (int i = 0; i < 26; i++) {
            if (node->next[i] != nullptr and char(i + 'a') == target[0]) {
                str[level] = char(i + 'a');
                printCertainwordsHelper(node->next[i], str, level + 1, target.substr(1));
            }
        }
    }

    void printCertainwords(string target) {
        char str[40];
        printCertainwordsHelper(root, str, 0, move(target));
    }
    // print target words //
    // print words with certain prefix //
    void printPrefix(string& pre) {
        if (!prefix(pre))
            return;
        char str[40];
        int index = 0;
        Node* temp = root;
        while (pre[index] != '\0') {
            for (int i = 0; i < 26; i++) {
                if (temp->next[i] == nullptr or char(i + 'a') != pre[0])
                    continue;
                str[index] = char(i + 'a');
                temp = temp->next[i];
            }
            index++;
        }
        printHelper(temp, str, index - 1);
    }
};
// end of trie class //
// ************************* //
// ************************* //

// class Linked List //

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T value;
        Node* next;
        explicit Node (T v){
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

    bool isEmpty() {
        return head == nullptr;
    }

    void deleteLinkedList() {
        for (Node* temp = head; temp != nullptr;){
            Node* p = temp;
            temp = temp -> next;
            delete p;
        }
    }

    void addStart (const T value) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = node;
            return;
        }
        node -> next = head;
        head = node;
    }


    void display() const {
        if (head == nullptr) {
            cout << "empty" << endl;
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

    int getSize ()const {
        if (head == nullptr) return 0;
        int res = 0;
        Node* temp = head;
        while (temp != nullptr){
            res++;
            temp = temp -> next;
        }
        return res;
    }


    void findAndRemoveFirst(const T& value) {
        if (head->value == value and head->next == nullptr) {
            head = nullptr;
            return;
        }
        if (head->value == value) {
            Node* temp = head->next;
            delete head;
            head = temp;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr and temp->next->value != value) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            cout << "value not in list" << endl;
            return;
        }
        temp->next = temp->next->next;
    }

    bool contains(const T& value) {
        if (head == nullptr)
            return false;
        Node* temp = head;
        while (temp) {
            if (temp->value == value)
                return true;
            temp = temp->next;
        }
        return false;
    }
};
// end of class Linked List //
// ************************* //
// ************************* //
// ************************* //

void testAdd(Trie& trie, const char name[]) {
    ifstream inFile;
    inFile.open(name);
    string s;
    if (inFile.is_open()) {
        while (!inFile.eof()) {
            inFile >> s;
            trie.insert(s);
        }
        inFile.close();
    }else
        cout << "can't open file!";
}

void testContain(Trie& trie) {
    ifstream inFile;
    inFile.open("testContains.txt");
    string s;
    if (inFile.is_open()) {
        while(!inFile.eof()) {
            inFile >> s;
            trie.insert(s);
            trie.printCertainwords(s);
        }
        cout << endl;
        inFile.close();
    }else {
        cout << "can't open file!";
        return;
    }
}

void testPrefix(Trie& trie) {
    ifstream inFile;
    inFile.open("testTriePrefix.txt");
    string pre;
    if (inFile.is_open()) {
        while (!inFile.eof()) {
            inFile >> pre;
            trie.printPrefix(pre);
        }
        cout << endl;
        inFile.close();
    }else {
        cout << "can't open file!";
        return;
    }
}

void testRemove(Trie& trie) {
    ifstream inFile;
    inFile.open("testRemove.txt");
    if (not inFile.is_open()) {
        cout << "file not found!";
        return;
    }
    string s;
    while (not inFile.eof()) {
        inFile >> s;
        if (not trie.search(s))
            continue;
        trie.remove(s);
    }
    inFile.close();
}

int findNoneWords(Trie& trie, const char name[]) {
    ifstream inFile;
    inFile.open(name);
    if (!inFile.is_open()) {
        cout << "can't open file!";
        return -1;
    }
    string s;
    int res2 = 0;
    while (!inFile.eof()) {
        inFile >> s;
        if (s[0] < 'a' || s[0] > 'z')
            res2++;
        else if (!trie.search(s))
            res2++;
    }
    inFile.close();
    return res2;
}

// ************************* //
// ************************* //
// ************************* //

class HashMapLinearChaining {
private:
    uint32_t size;
    LinkedList<string>* table;
public:

    explicit HashMapLinearChaining(uint32_t size):size(size) {
        table = new LinkedList<string>[size];
    }

    ~HashMapLinearChaining() {
        for (uint32_t i = 0; i < size; i++) {
            if (table[i].isEmpty())
                continue;
            table[i].deleteLinkedList();
        }
    }

    HashMapLinearChaining(const HashMapLinearChaining& orig) = default;
    HashMapLinearChaining& operator =(const HashMapLinearChaining& orig) = delete;

    uint32_t HashString(const string& s) {
        int sum = 0;
        for (char k : s)
            sum = sum + int(k);
        return  sum % size;
    }

    void add(const string& s) {
        uint32_t index = HashString(s);
        table[index].addStart(s);
    }

    void remove(const string& s) {
        uint32_t index = HashString(s);
        table[index].findAndRemoveFirst(s);
    }

    bool contains(const string& s) {
        uint32_t index = HashString(s);
        return table[index].contains(s);
    }

    void computeHistogram() {
        int history[10]{0};
        for (uint32_t i = 0; i < size; i++) {
            if (table[i].isEmpty())
                history[0]++;
            else if (table[i].getSize() == 1)
                history[1]++;
            else if (table[i].getSize() == 2)
                history[2]++;
            else if (table[i].getSize() == 3)
                history[3]++;
            else if (table[i].getSize() == 4)
                history[4]++;
            else if (table[i].getSize() == 5)
                history[5]++;
            else if (table[i].getSize() == 6)
                history[6]++;
            else if (table[i].getSize() == 7)
                history[7]++;
            else if (table[i].getSize() == 8)
                history[8]++;
            else
                history[9]++;
        }
        cout << "Histogram is: ";
        for (int j : history)
            cout << j << " ";
        cout << endl;
        for (uint32_t k = 0; k < size; k++) {
            if (not table[k].isEmpty())
                table[k].display();
        }
    }

    void print() {
        for (uint32_t k = 0; k < size; k++) {
            if (not table[k].isEmpty())
                table[k].display();
        }
    }

};
// ************************* //
// ************************* //
// ************************* //

void testHashMap(HashMapLinearChaining& hash, const char name1[], const char name2[], const char name3[]) {
    ifstream inFile;
    // add test file //
    inFile.open(name1);
    if (!inFile.is_open()) {
        cout << "file not found";
        return;
    }
    string s;
    while (not inFile.eof()) {
        inFile >> s;
        hash.add(s);
    }
    inFile.close();
    cout << "Now hashmap has the following: " << endl;
    hash.computeHistogram();
    // contains test file //
    inFile.open(name2);
    if (not inFile.is_open()) {
        cout << "file2 not found";
        return;
    }
    cout << "Trie contains the word in the file: " << endl;
    while (not inFile.eof()) {
        inFile >> s;
        hash.add(s);
        if (hash.contains(s))
            cout << s << " ";
    }
    cout << endl;
    inFile.close();
    // remove test file //
    cout << "After removing the words in remove file: " << endl;
    inFile.open(name3);
    if (not inFile.is_open()) {
        cout << "file3 not found";
        return;
    }
    while (not inFile.eof()) {
        inFile >> s;
        if (hash.contains(s))
            hash.remove(s);
    }
    inFile.close();
    hash.print();
}

void readbook(HashMapLinearChaining& dictionary, const char name[]) {
    ifstream inFile;
    inFile.open(name);
    string s;
    if (!inFile.is_open()) {
        cout << "can't open it";
        return;
    }
    while (not inFile.eof()) {
        inFile >> s;
        dictionary.add(s);
    }
    inFile.close();
}

uint32_t checkNonWords(HashMapLinearChaining& dictionary, const char name[]) {
    ifstream inFile;
    inFile.open(name);
    if (not inFile.is_open()) {
        cout << "cant open it";
        return -1;
    }
    uint32_t res = 0;
    string s;
    while (not inFile.eof()) {
        inFile >> s;
        if (not dictionary.contains(s))
            res++;
    }
    inFile.close();
    return res;
}

int main() {
    Trie dict;
    Trie test;
    cout << "Trie section: " << endl << endl;
    testAdd(test, "testTrieAdd.txt");
    cout << "Trie contains words in contains.txt: ";
    testContain(test);
    cout << "Trie contains words starting with prefix in prefix.txt: ";
    testPrefix(test);
    cout << "All the words in the trie: ";
    test.print();
    cout << endl << "After removing all the words in remove.txt: ";
    testRemove(test);
    test.print();
    cout << endl;
    testAdd(dict, "dict.txt");
    cout << "Non words calculated using trie: " << findNoneWords(dict, "prideandprejudice.txt") << endl;
    cout << endl;
    cout << "Hash Map section: " << endl << endl;
    HashMapLinearChaining hash(20);
    testHashMap(hash, "testTrieAdd.txt", "testContains.txt", "testRemove.txt");
    HashMapLinearChaining dictionary(500000);
    readbook(dictionary, "dict.txt");
    cout << "Non words calculated using hashmap: " << checkNonWords(dictionary, "prideandprejudice.txt");

}