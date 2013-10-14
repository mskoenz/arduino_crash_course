// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 20:29:20 CEST
// File:    list_class.hpp

#ifndef __LIST_CLASS_HEADER
#define __LIST_CLASS_HEADER

typedef unsigned int size_type;

//------------------- node -------------------
template<typename T>
struct list_node
{
    list_node(list_node<T> * pre, list_node<T> * nxt, T dat): data(dat), prev(pre), next(nxt) {}
    
    T data;
    list_node<T> * prev;
    list_node<T> * next;
};


//------------------- list -------------------
template<typename T>
class list
{
public:
    list(): node_zero(NULL), last_node(NULL), size_(0) {}
    
    //------------------- push_back -------------------
    inline void push_back(T data)
    {
        if(last_node == NULL)
        {
            node_zero = new list_node<T>(NULL, NULL, data);
            ++size_;
            last_node = node_zero;
        }
        else
        {
            last_node->next = new list_node<T>(last_node, NULL, data);
            ++size_;
            last_node = last_node->next;
        }
    }
    //------------------- back -------------------
    inline T back() const
    {
        if(last_node != NULL)
            return last_node->data;
        else
            return T();
    }
    //------------------- top -------------------
    inline T top()
    {
        return back();
    }
    //------------------- pop -------------------
    inline void pop()
    {
        if(last_node != NULL)
        {
            if(last_node != node_zero)
            {
                list_node<T> * temp = last_node->prev;
                temp->next = NULL;
                delete last_node;
                --size_;
                last_node = temp;
            }
            else
            {
                delete last_node;
                --size_;
                last_node = NULL;
                node_zero = NULL;
                
            }
        }
    }
    //------------------- front -------------------
    inline T front() const
    {
        if(node_zero != NULL)
            return node_zero->data;
        else
            return T();
    }
    //------------------- pop_front -------------------
    inline void pop_front()
    {
        if(node_zero != NULL)
        {
            if(node_zero != last_node)
            {
                list_node<T> * temp = node_zero->next;
                temp->prev = NULL;
                delete node_zero;
                --size_;
                node_zero = temp;
            }
            else
            {
                delete node_zero;
                --size_;
                node_zero = NULL;
                last_node = NULL;
                
            }
        }
    }
    //------------------- remove -------------------
    void remove(T data)
    {
        
        if(node_zero != NULL)
        {
            if(node_zero->data == data)
            {
                pop_front();
                return;
            }
            if(node_zero->next != NULL)
            {
                
                for(list_node<T> * pos = node_zero->next; pos != last_node; pos = pos->next)
                {
                    if(pos->data == data)
                    {
                        pos->prev->next = pos->next;
                        pos->next->prev = pos->prev;
                        delete pos;
                        --size_;
                        return;
                    }
                }
                
                if(last_node->data == data)
                {
                    pop();
                }
            }
        }
    }
    //------------------- size_ -------------------
    inline size_type size()
    {
        return size_;
    }
    //------------------- vector syntax -------------------
    inline T & operator[](size_type const index)
    {
        list_node<T> * pos = node_zero;
        
        for(size_type i = 0; i < index; ++i)
        {
            pos = pos->next;
        }
        
        return pos->data;
    }
    inline T const & operator[](size_type const index) const
    {
        list_node<T> * pos = node_zero;
        
        for(size_type i = 0; i < index; ++i)
        {
            pos = pos->next;
        }
        
        return pos->data;
    }
    
    
    //------------------- print only for test -------------------
    #ifdef GCC
        void print()
        {
            if(node_zero != NULL)
            {
                int i = 0;
                for(list_node<T> * pos = node_zero; pos != last_node; pos = pos->next)
                {
                    std::cout << "node: " << i <<  "  " << pos->data << std::endl;
                    ++i;
                }
                std::cout << "node: " << i << "  " << last_node->data << std::endl;
            }
        }
    #endif
private:
    list_node<T> * node_zero;
    list_node<T> * last_node;
    size_type size_;
};

#endif //__LIST_CLASS_HEADER
