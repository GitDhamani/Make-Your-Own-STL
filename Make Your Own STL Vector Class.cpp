#include <iostream>

template <typename T>
class Vector
{
    T* ptr;
    int m_size = 0;
    int m_capacity = 2;
    
    public:
    Vector() { ptr = new T[2]; }
    ~Vector() { delete [] ptr; }
    int size() { return m_size; };
    
    void Reallocate(int val)
    {
        std::cout<<"New Allocation"<<std::endl;
        T* newptr = new T[val];
        if (val < m_size) m_size = val; //Incase Shrink
         
        for (int i = 0; i < m_size; i++)
        newptr[i] = ptr[i];
        
        delete [] ptr;  //De-allocate old array
        ptr = newptr; //Point our pointer at New Array
        newptr = nullptr; //Null out temp pointer
        m_capacity = val;
        std::cout<<"New Capacity is: "<<m_capacity<<std::endl;
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
    
    //For R Values we move them straight in
    void pushback(T&& val)
    {
        if (m_size == m_capacity)
        Reallocate(1.5*m_capacity); 
        ptr[m_size++] = std::move(val);
    }
};

int main()
{
    Vector<int> v;
    
    v.pushback(100);
    std::cout<<v[0]<<std::endl;
    
    v.pushback(200);
    std::cout<<v[1]<<std::endl;
    
    v.pushback(300);
    std::cout<<v[2]<<std::endl;
    
    v.pushback(400);
    std::cout<<v[3]<<std::endl;
    
    v.pushback(500);
    std::cout<<v[4]<<std::endl;
    
    v.pushback(600);
    std::cout<<v[5]<<std::endl;
    
    v.pushback(700);
    std::cout<<v[6]<<std::endl;
    
    //Subscript Operator Check
    v[0] = 5;
    std::cout<<v[0]<<std::endl;
    
    for (int i = 0; i<v.size(); i++)
    std::cout<<v[i]<<" ";
    
    return 0;  
}