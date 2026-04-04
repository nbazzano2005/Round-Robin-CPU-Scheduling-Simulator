#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "LinkedList.hpp"


template <class item_t>
static item_t& __ll_default_ref() {
    static item_t __d{};
    return __d;
}

template <class item_t>
LinkedList<item_t>::LinkedList() 
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class item_t>
LinkedList<item_t>::~LinkedList() {
    auto cur = head;
    while (cur) {
        auto nxt = cur->getNext();
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    size = 0;
}

template <class item_t>
LinkedListNode<item_t>* LinkedList<item_t>::getNode(int index) const {
    if (index < 0 || index >= size) 
        return nullptr;
    auto* cur = head;
    for (int i = 0; i < index; ++i) 
        cur = cur->getNext();
    return cur;
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item) {
    
    auto* node = new LinkedListNode<item_t>(nullptr, item);
    if (!head) {
        head = tail = node;
    } else {
        tail->setNext(node);
        tail = node;
    }
    ++size;
}

template <class item_t>
void LinkedList<item_t>::popBack() {
    if (size <= 0) return;
    if (size == 1) {
        delete head;
        head = tail = nullptr;
        size = 0;
        return;
    }
   
    auto* cur = head;
    while (cur->getNext() != tail) 
        cur = cur->getNext();
    delete tail;
    tail = cur;
    tail->setNext(nullptr);
    --size;
}

template <class item_t>
const item_t& LinkedList<item_t>::getBack() const {
    if (size > 0 && tail) 
        return tail->getItem();
    return __ll_default_ref<item_t>();
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item) {
    
    auto* node = new LinkedListNode<item_t>(head, item);
    head = node;
    if (!tail) 
        tail = node;
    ++size;
}

template <class item_t>
void LinkedList<item_t>::popFront() {
    if (size <= 0) 
        return;
    auto* old = head;
    head = head->getNext();
    delete old;
    --size;
    if (size == 0) 
        tail = nullptr;
}

template <class item_t>
const item_t& LinkedList<item_t>::getFront() const {
    if (size > 0 && head) 
        return head->getItem();
    return __ll_default_ref<item_t>();
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const {
    auto* node = getNode(index);
    if (!node) 
        return __ll_default_ref<item_t>();
    return node->getItem();
}

template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item) {
    auto* node = getNode(index);
    if (!node) 
        return;
    node->setItem(item);
}

template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item) {
    if (index < 0 || index > size) 
        return; 
    if (index == 0) 
    { 
        pushFront(item); 
        return; 
    }
    if (index == size) 
    { 
        pushBack(item); 
        return; 
    }

    auto* prev = getNode(index - 1);
    if (!prev) 
        return;
    auto* node = new LinkedListNode<item_t>(prev->getNext(), item); 
    prev->setNext(node);
    ++size;
}

template <class item_t>
void LinkedList<item_t>::remove(int index) {
    if (index < 0 || index >= size) 
        return;
    if (index == 0) 
    { 
        popFront(); 
        return; 
    }
    if (index == size - 1) 
    { 
        popBack(); 
        return; 
    }

    auto* prev = getNode(index - 1);
    if (!prev) 
        return;
    auto* toRemove = prev->getNext();
    prev->setNext(toRemove->getNext());
    delete toRemove;
    --size;
}

template <class item_t>
int LinkedList<item_t>::getSize() const 
{ 
    return size; 
}

template <class item_t>
bool LinkedList<item_t>::isEmpty() const 
{ 
    return size == 0; 
}

#endif
