#ifndef ARRAY_LIST_TPP
#define ARRAY_LIST_TPP


template <class item_t>
static void __al_grow_if_needed(item_t*& items, int& size, int& capacity, int minNeeded)
{
    if (capacity >= minNeeded) return;

    int newCap;
    if (capacity > 0)
        newCap = capacity;   
    else
        newCap = 1;          

    while (newCap < minNeeded) newCap *= 2;

    item_t* n = new item_t[newCap];
    for (int i = 0; i < size; ++i) n[i] = items[i];
    delete[] items;
    items = n;
    capacity = newCap;
}


template <class item_t>
ArrayList<item_t>::ArrayList()
    : items(nullptr), size(0), capacity(10)
{
    items = new item_t[capacity];
}

template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)    
{
    
    items = nullptr;
    size = 0;

    
    if (capacity <= 0)
        this->capacity = 1;
    else
        this->capacity = capacity;

    items = new item_t[this->capacity];
}

template <class item_t>
ArrayList<item_t>::~ArrayList()
{
    delete[] items;
    items = nullptr;
    size = 0;
    capacity = 0;
}


template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
    __al_grow_if_needed(items, size, capacity, size + 1);
    items[size++] = item;
}

template <class item_t>
void ArrayList<item_t>::popBack()
{
    if (size <= 0) return; 
    --size;
}

template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
    if (size > 0) return items[size - 1];
    static item_t __default{};
    return __default; // fallback reference
}


template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
    __al_grow_if_needed(items, size, capacity, size + 1);
    // shift right in-place
    for (int i = size; i > 0; --i) 
        items[i] = items[i - 1];
    items[0] = item;
    ++size;
}

template <class item_t>
void ArrayList<item_t>::popFront()
{
    if (size <= 0) return; 
    for (int i = 0; i < size - 1; ++i) items[i] = items[i + 1];
    --size;
}

template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
    if (size > 0) return items[0];
    static item_t __default{};
    return __default;
}


template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{
    if (index >= 0 && index < size) return items[index];
    static item_t __default{};
    return __default;
}

template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
    if (index < 0 || index >= size) return;
    items[index] = item;
}


template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
    if (index < 0 || index > size) return;
    __al_grow_if_needed(items, size, capacity, size + 1);

    for (int i = size; i > index; --i) items[i] = items[i - 1];
    items[index] = item;
    ++size;
}

template <class item_t>
void ArrayList<item_t>::remove(int index)
{
    if (index < 0 || index >= size) return;
    for (int i = index; i < size - 1; ++i) items[i] = items[i + 1];
    --size;
}


template <class item_t>
int ArrayList<item_t>::getSize() const
{
    return size;
}

template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{
    return size == 0;
}

template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
    return capacity;
}

#endif 