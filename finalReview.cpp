#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

class Trie {
private:
    class Node {
    public:
        bool isWord;
        Node* next[26]{nullptr};
        Node(): isWord(false) {
            for (auto& node: next)
                node = nullptr;
        }
    };
    Node* root;

public:

    Trie() {
        root = new Node();
    }
    void insert(string& word) {
        Node* temp = root;
        for (char i : word) {
            if (temp->next[i - 'a'] == nullptr)
                temp->next[i - 'a'] = new Node();
            temp = temp->next[i - 'a'];
        }
        temp->isWord = true;
    }

    bool contains(string& word) {
        Node* temp = root;
        for (char i : word) {
            if (temp->next[i - 'a'] == nullptr)
                return false;
            temp = temp->next[i - 'a'];
        }
        return temp->isWord;
    }

    bool prefix(string& pre) {
        Node* temp = root;
        for (char i : pre) {
            if (temp->next[i - 'a'] == nullptr)
                return false;
            temp = temp->next[i - 'a'];
        }
        return true;
    }

    friend void printHelper(char str[], int level, Node* temp) {
        if (temp->isWord) {
            str[level] = '\0';
            cout << str << " ";
        }
        for (int i = 0; i < 26; i++) {
            if (temp->next[i] == nullptr)
                continue;
            str[level] = char(i + 'a');
            temp = temp->next[i];
            printHelper(str, level + 1, temp);
        }
    }

    void print() {
        char str[40];
        Node* temp = root;
        printHelper(str, 0, temp);
    }

};

class BinaryTree {
private:
    class Node {
    public:
        int value;
        Node* left;
        Node* right;
        explicit Node(int value):value(value) {
            left = nullptr;
            right = nullptr;
        }

        void inorder() {
            if (left != nullptr)
                left->inorder();
            cout << value;
            if (right != nullptr)
                right->inorder();
        }

    };
    Node* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    void add(int v) {
        if (root == nullptr) {
            root = new Node(v);
            return;
        }

        Node* temp = root;
        while (true)
            if (v < temp->value) {
                if (temp->left == nullptr) {
                    temp->left = new Node(v);
                    return;
                }
                temp = temp->left;
            } else {
                if (temp->right == nullptr) {
                    temp->right = new Node(v);
                    return;
                }
                temp = temp->right;
            }

    }

//    friend void preorder(Node* node) {
//        if (node == nullptr)
//            return;
//
//        cout << node->value;
//        preorder(node->left);
//        preorder(node->right);
//    }
//
//    friend void inorder(Node* node) {
//        if (node == nullptr)
//            return;
//
//        inorder(node->left);
//        cout << node->value;
//        inorder(node->right);
//    }
//
//    friend void postorder(Node* node) {
//        if (node == nullptr)
//            return;
//
//        postorder(node->left);
//        postorder(node->right);
//        cout << node->value;
//    }

};

class CSR {
private:
    vector <int> startIndex;
    vector <int> adjanency;
    vector <double> weight;

public:
    explicit CSR(int numOfV) {
        startIndex.reserve(numOfV + 1);
    }

    void DFS(int from) {
        stack <int> stack;
        stack.push(from);
        vector <bool> visited;
        visited.reserve(startIndex.size() - 1);
        for (auto x: visited)
            x = false;
        visited[from] = true;
        while (not stack.empty()) {
            int cur = stack.top();
            cout << char(cur + 'a');
            stack.pop();
            for (int i = startIndex[cur]; i < startIndex[cur + 1]; i++) {
                if (visited[adjanency[i]])
                    continue;
                stack.push(adjanency[i]);
                visited[adjanency[i]] = true;
            }
        }
    }

    void BFS(int from) {
        queue <int> queue;
        queue.push(from);
        vector <bool> visited;
        visited.reserve(startIndex.size() - 1);
        for (auto x: visited)
            x = false;
        visited[from] = true;

        while (not queue.empty()) {
            int cur = queue.front();
            cout << char(cur + 'a') << " ";
            queue.pop();

            for (int i = startIndex[cur]; i < startIndex[cur + 1]; i++) {
                if (visited[adjanency[i]])
                    continue;
                queue.push(adjanency[i]);
                visited[adjanency[i]] = true;
            }
        }
    }

    void floydwarshall() {

    }

};
class Element {
public:
    int value;
    string key;
};

class HashMapLP {
private:
    int size;
    Element* table;


public:
    explicit HashMapLP(int size):size(size) {
        table = new Element[size];
    }
};

class Matrix {
private:
    int cols;
    int rows;
    double* data;

public:
    Matrix(int cols, int rows): cols(cols), rows(rows) {
        data = new double[rows * cols];
    }

    ~Matrix() {
        delete[] data;
    }

    double& operator() (int i, int j) {
        return data[cols * i + j];
    }

    friend Matrix operator* (const Matrix& a, const Matrix& b) {
        Matrix res(b.cols, a.rows);
        
        return res;
    }

};

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T value;
        Node* next;
        explicit Node(T value): value(value) {
            next = nullptr;
        }
    };
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        for (Node* temp = head; head != nullptr;) {
            Node* p = temp;
            temp = temp->next;
            delete p;
        }
    }

    void addStart(T value) {
        Node* node = new Node(value);
        if (head == nullptr)
            return head = node;
        node->next = head;
        head = node;
    }

    bool contains(const T& value) {
        if (head == nullptr)
            return false;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->value == value)
                return true;
            temp = temp->next;
        }
        return false;
    }
};

class HashMap {
private:
    int size;
    LinkedList<string>* table;

public:
    explicit HashMap(int size): size(size) {
        table = new LinkedList<string> [size];
    }

};

void print(const vector<int>& nums) {
    for (auto x: nums)
        cout << x << ' ';
}

// Regular permutation
void helper1(vector<vector<int> > &res, vector<int> nums, int n){

    if(n == 0){
        res.push_back(nums);
//      print(nums);
        return;
    }

    for(int i = 0 ; i <= n; i++){
        swap(nums[i], nums[n]);
        helper1(res, nums, n - 1);
        swap(nums[i], nums[n]);
    }
}

vector<vector<int> > permute1(int n) {

    vector<vector<int> > res;
    vector<int> nums;
    for (int i = 0; i <= n; i++)
        nums.push_back(i);
    int s = nums.size();

    helper1(res, nums, s - 1);

    return res;
}


// Heap's algorithm
void helper2(vector<vector<int> > &res, vector<int> nums, int n){

    if(n == 0){
        res.push_back(nums);
        return;
    }

    for(int i = 0 ; i <= n; i++){
        helper2(res, nums, n - 1);
        if (n % 2 == 1)
            swap(nums[0], nums[n]);
        else
            swap(nums[i], nums[n]);
    }
}

vector<vector<int> > permute2(int n) {

    vector<vector<int> > res;
    vector<int> nums;
    for (int i = 0; i <= n; i++)
        nums.push_back(i);
    int s = nums.size();

    helper2(res, nums, s - 1);

    return res;
}



int main() {
    vector<int> nums;
    for (int i = 0; i <= 3; i++)
        nums.push_back(i);
    vector<vector<int>> r = permute1(3);
    for (auto & i : r) {
        for (int j : i)
            cout << j << " ";
        cout << endl;
    }
//    int x[] = {1, 2, 3, 4};
//    while (next_permutation(x, x + 4)) {
//        for (auto i: x)
//            cout << i << " ";
//        cout << endl;
//    }

}