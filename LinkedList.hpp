#ifndef LINKED_LIST
#define LINKED_LIST

#include "List.hpp"
#include "LinkedListNode.hpp"



template <class item_t>
class LinkedList : public List<item_t>
{
  protected:
   LinkedListNode<item_t>* head;
   LinkedListNode<item_t>* tail;
   int size;

   LinkedListNode<item_t>* getNode(int index) const;

  public:
   LinkedList();
   virtual ~LinkedList();
   
   virtual void pushFront(const item_t& item);
   virtual const item_t& getFront() const;
   virtual void popFront();

   virtual void pushBack(const item_t& item);
   virtual const item_t& getBack() const;
   virtual void popBack();

   virtual void insert(int index, const item_t& item); 
   virtual void remove(int index);

   virtual const item_t& getItem(int index) const;
   virtual void setItem(int index, const item_t& item);

   virtual int getSize() const;
   virtual bool isEmpty() const;
};



#include "LinkedList.tpp"
#endif 