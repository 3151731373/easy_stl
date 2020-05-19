#pragma warning(disable: 4786)
#include <iostream>
#include <string>
using namespace std;
template <class T>
struct ListNode {
    ListNode *_prev;
    ListNode *_next;
    T _data;
};
template <class T>
class myList{
//TODO
public:
    typedef ListNode<T>* iterator;
    typedef const ListNode<T>* const_iterator;

    typedef size_t size_type;
    size_type size()const{return tail-head;}

    iterator begin(){return head;}
    const_iterator begin()const{return head;}
    iterator end(){return tail;}
    const_iterator end()const{return tail;}

    myList(){create();}
    ~myList(){uncreate();}
    void push_back(const T&val);
    void print();
    void sort();

private:
    iterator head, tail;

    void create();
    void uncreate();
    std::allocator<T> alloc;
};

template <class T>
void myList<T>:: create()
{
    head = new ListNode<T>;
    tail = new ListNode<T>;
    head->_next=tail;
    tail->_prev=head;
}

template <class T>
void myList<T>:: uncreate()
{
    iterator tmp=tail;
    while(tmp!=head)
    {
        iterator head_pre=tmp->_prev;
        delete tmp;
        tmp = head_pre;
    }
    delete tmp;
}

template <class T>
void myList<T>:: push_back(const T &val)
{
    iterator ptr;
    ptr = new ListNode<T>;
    ptr->_data=val;
    iterator tail_tmp = end();
    iterator head_tmp = tail_tmp->_prev;

    head_tmp->_next=ptr;
    ptr->_prev=head_tmp;
    ptr->_next=tail_tmp;
    tail_tmp->_prev=ptr;
}

template <class T>
void myList<T>:: print()
{
    iterator it = head->_next;
    while(it!=tail)
    {
        cout<<it->_data<<" ";
        it = it->_next;
    }
}

template <class T>
void myList<T>:: sort()
{
    for(iterator it = tail->_prev;it!=begin();it=it->_prev)
    {
        iterator pre_temp = head->_next;
        iterator temp = pre_temp->_next;
        while(temp!=end())
        {
            if(pre_temp->_data>temp->_data)
                swap(pre_temp->_data,temp->_data);
            pre_temp=pre_temp->_next;
            temp=temp->_next;
        }
    }

}

