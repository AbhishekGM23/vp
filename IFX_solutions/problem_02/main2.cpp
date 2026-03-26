#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class MyCout {
public:
    T a;
    T b;

    MyCout(T val,T val1) : a(val), b(val1) {}

    // Define the friend inside the class. 
    // This automatically creates a non-template friend for every instance of MyCout.
    friend ostream& operator-(ostream& os, const MyCout<T>& obj) {
        os << obj.a << obj.b; 
        return os;
    }

    friend ostream& operator+(ostream& os, const MyCout<T>& obj) {
        os << obj.a << obj.b; 
        return os;
    }
};

int main() {
    MyCout<int> obj(10,11);
    MyCout<string> obj2("Hello","Hello1");

    // Now this works and chains correctly
    cout - obj - obj2 ;
    cout <<endl;
    cout + obj + obj2 ;
    cout <<endl;

    //cout - obj - " " - obj2 - "\n";
    
    return 0;
}
