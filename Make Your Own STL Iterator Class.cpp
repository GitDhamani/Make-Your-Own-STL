#include <iostream>

//Our Iterator Class Call it anything You want
template <typename V> //Template variable is now a container, not just a type.
class ITRClass  
{
    public:
    using ValueType = typename V::ValueType;   //Now we drill down into the container to get type
    using PointerType = ValueType*;
    ITRClass(PointerType ptr): m_ptr{ptr}{}  //Single Arg Constructor
    
    bool operator!=(const ITRClass& obj) { return (m_ptr != obj.m_ptr); }
    ValueType* operator++(int) { return ++m_ptr; }  //Postfix++
    ValueType* operator++() { return ++m_ptr; }     //++Prefix (Range Based For Loop Uses this)
    ValueType operator*() { return *m_ptr; }
    
    //For some reason friend functions of templates need to be written inside the class
    //But still expressed globally
    friend std::ostream& operator<<(std::ostream& os, const ITRClass& obj)
    { os << obj.m_ptr; return os; }
   
    //Usually declare Private Variables up top but it relies on the PointerType and so the
    //Using typedef needs to come first.
    private:    
    PointerType m_ptr;    
};

//Our Vector Container
template <typename T>
class Vector
{
    T* ptr;
    int m_size = 0;
    int m_capacity = 2;
    
    public:

    using ValueType = T; 
    using iterator = ITRClass<Vector<T>>; //Now the alias is for the container    
    //Remember we have to have an iterator data type which the For loop is looking for
    //inside the Vector Class
 
    Vector() { ptr = new T[2];}
    ~Vector() { delete [] ptr;  }
    int size() { return m_size; }
    
    void Reallocate(int val)
    {
        T* newptr = new T[val];
        if (val < m_size) m_size = val; //Incase Shrink
       
        for (int i = 0; i < m_size; i++)
        newptr[i] = ptr[i];
        
        delete[] ptr;  //De-allocate old array
        ptr = newptr; //Point our pointer at New Array
        newptr = nullptr; //Null out temp pointer
        m_capacity = val;
    }    
    
    T& operator[](int index)
    {
        return  *(ptr + index);             
    }    
    
    void pushback(const T& val)
    {
        if (m_size == m_capacity)
        Reallocate(1.5*m_capacity); 
        ptr[m_size++] = val;
    }
    
    iterator begin() {return iterator(ptr);}  
    //Now Creates and Returns an Iterator Object: ITRClass<Vector<T>>(ptr) 
    
    
    iterator end() {return iterator(ptr + m_size);}
    //Now Creates and Returns an Iterator Object: ITRClass<T>(ptr + msize) 
};

int main()
{
    Vector<int> vec;
    vec.pushback(1);
    vec.pushback(2);
    vec.pushback(3);
    vec.pushback(4);
    vec.pushback(5);
    
    for(Vector<int>::iterator it = vec.begin(); it!=vec.end(); it++)  //postfix incremenet i++
    std::cout<<*it<<" ";
    std::cout<<std::endl;
    
    for(Vector<int>::iterator it = vec.begin(); it!=vec.end(); ++it)  //prefix increment ++i
    std::cout<<*it<<" ";
    std::cout<<std::endl;
    
    for (auto element: vec)  //The Range based for loop uses ++it which is the prefix++ version
    std::cout<<element<<" ";
    std::cout<<std::endl;
    
    return 0;  
}