#include <iostream>

template<typename T, int N>
class Array
{
    T arr[N];
    
    public:
    int size() { return N; }
    T& operator[](const int& index) {return arr[index];}
    T* getbuffer() {return arr;}
};

int main()
{
    Array<int, 5> test;
    test[0] = 1;
    test[1] = 2;
    test[2] = 3;
    test[3] = 4;
    test[4] = 5;
    
    for (int i = 0; i<test.size(); i++)
    std::cout<<test[i]<<" ";
    std::cout<<std::endl;
    
    Array<char, 5> newtest;
    newtest[0] = 'A';
    newtest[1] = 'B';
    newtest[2] = 'C';
    newtest[3] = 'D';
    newtest[4] = 'E';
    
    for (int i = 0; i<newtest.size(); i++)
    std::cout<<newtest[i]<<" ";
    std::cout<<std::endl;
    
    return 0;
}