
#ifndef ARRAY_LIST
#define ARRAY_LIST

#include "List.hpp"

#pragma once

template <class item_t>
class ArrayList : public List<item_t>
{
protected:                
    item_t* items;
    int size;
    int capacity;

public:
    
    ArrayList();
    ArrayList(int capacity);
    virtual ~ArrayList(); 

   
    void pushBack(const item_t& item);
    void popBack();
    const item_t& getBack() const;

    void pushFront(const item_t& item);
    void popFront();
    const item_t& getFront() const;

    const item_t& getItem(int index) const;
    void setItem(int index, const item_t& item);

    void insert(int index, const item_t& item);
    void remove(int index);

    int  getSize() const;
    bool isEmpty() const;

    
    virtual int getCapacity() const;
};
#include "ArrayList.tpp"

#endif


