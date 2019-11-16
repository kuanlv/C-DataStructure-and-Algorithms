// Kuan Lyu GrowArray 10/19/2019 //
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;

class point{
public: double x; double y;
        point(){
            x = 0;
            y = 0;
        }
        point(double x, double y):x(x), y(y){}
    friend ostream& operator << (ostream& s, const point& p){
        s << p.x << ", " << p.y;
        return s;
    }
};

template <typename T>
class GrowArray{
private:
    int capacity;
    int used;
    T* data;
    void Grow(){
        T* old = data;
        data = new T[2 * capacity];
        for(int i = 0; i < used; i++)
            data[i] = old[i];
        capacity *= 2;
        delete[] old;
    }

public:
    GrowArray():capacity(1), used(0), data(new T[capacity]){}
    GrowArray(const GrowArray& original):capacity(original.capacity), used(original.used){
        data = new T[original.capacity];
        for(int i = 0; i < original.used; i++)
            data[i] = original.data[i];
    }
    GrowArray& operator=(const GrowArray& original){
        if(this == &original)
            return *this;
        delete[] data;
        capacity = original.capacity;
        used = original.used;
        data = new T[capacity];
        for(int i = 0; i < used; i++)
            data[i] = original.data[i];
        return *this;
    }
    ~GrowArray(){
        delete[] data;
    }
    friend ostream& operator<<(ostream& s, const GrowArray& a){
        for(int i = 0; i < a.used; i++){
            s << a.data[i] << "; ";
        }
        s << endl;
        return s;
    }
    explicit GrowArray (int initalSize): capacity(initalSize), used(0){
        data = new T[initalSize];
    }

    void addEnd(T value){
        if(used+1 == capacity){
            Grow();
        }
        used++;
        data[used-1] = value;
    }

    void addStart(T value){
        if(used + 1 == capacity)
            Grow();
        for(int i = used-1; i >= 0; i--)
            data[i+1] = data[i];
        used++;
        data[0] = value;
    }

    void insert(int index, T value){
        if(used + 1 == capacity)
            Grow();
        for(int i = used-1; i >= index; i--)
            data[i+1] = data[i];
        used++;
        data[index] = value;
    }

    void removeEnd(){
        used--;
    }

    void removeStart(){
        for(int i = 0; i < used - 1; i++)
            data[i] = data[i + 1];
        used--;
    }

    void remove(int index){
        if(index == 0)
            removeStart();
        else if(index == used - 1)
            removeEnd();
        else{
            for(int i = index; i < used - 1; i++)
                data[i] = data[i + 1];
            used--;
        }
    }

    int size() const{
        return used;
    }
    void getInfo(){
        cout << used << ", " << capacity;
    }
};


void readPointsFromFile(double& maxX, double& maxY, double& minX, double& minY){
    double x, y;
    ifstream infile;
    infile.open("convexhullpoints.dat");
    if(infile.is_open()){
        while(!infile.eof()){
            infile >> x >> y;
            if(x > maxX)
                maxX = x;
            if(x < minX)
                minX = x;
            if(y > maxY)
                maxY = y;
            if(y < minY)
                minY = y;
        }
        infile.close();
    }else{
        cout << "can't open file!";
    }
}

vector< vector<GrowArray<point>> > dispachPointsFromFile(){
    double maxX = -numeric_limits<int>:: max();
    double maxY = -numeric_limits<int>:: max();
    double minX = numeric_limits<int>:: max();
    double minY = numeric_limits<int>:: max();
    readPointsFromFile(maxX, maxY, minX, minY);

    vector< vector<GrowArray<point>> > Grid;
    vector<GrowArray<point>> rows;
    GrowArray<point> primitive;
    for(int i = 0; i < 8; i++)
        rows.push_back(primitive);
    for(int i = 0; i < 8; i++)
        Grid.push_back(rows);

    ifstream infile;
    double x, y;
    infile.open("convexhullpoints.dat");
    if(infile.is_open()){
        while(!infile.eof()){
            infile >> x >> y;
            double row = (y - minY) * 7 / (maxY- minY);
            double col = (x - minX) * 7 / (maxX- minX);
            Grid[int(row)][int(col)].addEnd(point(x, y));
        }
        infile.close();
    }else{cout << "Can't open file!"; }
    return Grid;
}

void PrintPremium(vector< vector<GrowArray<point>> >& Grid){
    if(Grid.empty()) {
        cout << "Nothing to print" << endl;
        return;
    }
    int row_length = Grid[0].size();
    int col_length = Grid.size();
    cout <<  "The first row is: " << endl;
    for(int i = 0; i < row_length; i++)
        cout << Grid[0][i];
    cout << endl << "The last column: ";
    for(int i = 0; i < col_length; i++)
        cout << Grid[i][col_length - 1];
    cout << endl << "The last row: ";
    for(int i = row_length - 1; i >= 0; i--)
        cout << Grid[row_length - 1][i];
    cout << endl << "The first column: ";
    for(int i = col_length - 1; i >= 0; i--)
        cout << Grid[i][0];
}


int main() {
    double maxX = -numeric_limits<int>:: max();
    double maxY = -numeric_limits<int>:: max();
    double minX = numeric_limits<int>:: max();
    double minY = numeric_limits<int>:: max();
    readPointsFromFile(maxX, maxY, minX, minY);
    cout<<"maximum of x is "<< maxX << ";"<< endl;
    cout<<"maximum of y is "<< maxY << ";"<< endl;
    cout<<"minimum of x is "<< minX << ";" << endl;
    cout<<"minimum of y is "<< minY << ";" << endl;
    vector< vector<GrowArray<point>> > Grid = dispachPointsFromFile();
    PrintPremium(Grid);
}