#ifndef __VEC_H
#define __VEC_H
#include <memory>
#include <mm_malloc.h>
//TODO

template <class T>
class Vec{
public:

    typedef T* iterator;
    typedef const T* const_iterator;

    typedef size_t size_type;
    size_type size()const{return avail-data;};

    iterator begin(){return data;}
    const_iterator begin()const{return data;}

    iterator end(){return avail;}
    const_iterator end()const{return avail;}

    void push_back(const T& val);
    void pop_back();

    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    //赋值函数只有一个
    Vec<T>& operator=(const Vec & rhs);

    T& operator[](size_type i){return data[i];}
    const T& operator[](size_type i)const{return data[i];};

    //构造函数可以有多个,但复制构造函数只有一个
    Vec(){create();}
    explicit Vec(std::size_t n,const T& Val=T()){create(n,Val);}
    //复制构造函数只有一个，一个参数（常量引用的类本身的类型），返回值类型是类本身的类型
    Vec(const Vec&v){create(v.begin(),v.end());}
    ~Vec(){uncreate();}

    void clear();
    //一个类中只有一个析构函数，没有参数也没有返回值

private:
    iterator data, avail, limit;
    std::allocator<T> alloc;
    void create(){data=avail=limit=0;}
    void create(size_type n,const T& Val);
    void create(const_iterator i_begin,const_iterator i_end);
    void uncreate();
    void grow();
    void unchecked_append(const T& val)
    {
        alloc.construct(avail++,val);//在给定位置构造一个元素，额外参数用来初始化对象。
    }
};


template <class T>
void Vec<T>::create(size_type n,const T& Val)
{
    data=alloc.allocate(n,0);
    avail=limit=data+n;
    std::uninitialized_fill(data,limit,Val);//将元素拷贝到未构造空间中

}

template <class T>
void Vec<T>::create(const_iterator i_begin,const_iterator i_end)
{
    size_type n = i_end-i_begin;
    data = alloc.allocate(n*2,0);
    avail = data + n;
    limit = data + 2*n;

    iterator new_avail = std::uninitialized_copy(i_begin,i_end,data);
    avail = new_avail;
}



//析构函数负责释放内存空间
template <class T>
void Vec<T>::uncreate()
{
    if(data){
        iterator it=avail;
        while(it!=data)
            alloc.destroy(--it);//destroy析构vector中的元素（可能申请的空间）
        alloc.deallocate(data,limit-data);//deallocate释放向量所占的空间
    }
    data=avail=limit=0;
}
//clear只是逻辑上的清空向量，使得向量中的有效元素个数为0就可以
template <class T>
void Vec<T>::clear()
{
    if(data){
        iterator it=avail;
        while(it!=data)
            alloc.destroy(--it);
        //alloc.deallocate(data,limit-data);
    }
    avail=data;
}


template <class T>
void Vec<T>:: push_back(const T& val){
    if(avail==limit)
        grow();
    unchecked_append(val);
}

template <class T>
void Vec<T>:: pop_back(){
    if(data)
    {
        alloc.destroy(--avail);
    }
}

template <class T>
void Vec<T>::grow()
{
    size_type new_size=1;
    if(limit!=data)new_size=2*(limit-data);
    iterator new_data = alloc.allocate(new_size,0);//分配原始的未构造的内存
    iterator new_avail = std::uninitialized_copy(data,avail,new_data);

    uncreate();
    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}


template <class T>
Vec<T> & Vec<T>::operator=(const Vec& rhs)
{
    if(&rhs!=this)
    {
        uncreate();
        create(rhs.begin(),rhs.end());
    }
    return *this;
}

#endif
