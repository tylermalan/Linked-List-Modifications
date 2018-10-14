// CS212 Spring 2018
// Created by Gordon Malan on 5/20/2018.

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <stdexcept>

using namespace std;

template<typename T>
class Node
{
public:
    T element;  // Element contained in the node
    Node<T>* next; // Pointer to the next node

    Node() // No-arg constructor
    {
        next = NULL;
    }

    Node(T element) // Constructor
    {
        this->element = element;
        next = NULL;
    }
};

template<typename T>
class Iterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
    Iterator(Node<T>* p)
    {
        current = p;
    };

    Iterator operator++() // Prefix ++
    {
        current = current->next;
        return *this;
    }

    Iterator operator++(int dummy) // Postfix ++
    {
        Iterator temp(current);
        current = current->next;
        return temp;
    }

    T& operator*()
    {
        return current->element;
    }

    bool operator==(const Iterator<T>& iterator)
    {
        return current == iterator.current;
    }

    bool operator!=(const Iterator<T>& iterator)
    {
        return current != iterator.current;
    }

private:
    Node<T>* current;
};

template<typename T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(LinkedList<T>& list);
    virtual ~LinkedList();
    void addFirst(T element);
    void addLast(T element);
    T getFirst() const;
    T getLast() const;
    T removeFirst();
    T removeLast();
    void add(T element);
    void add(int index, T element);
    void clear();
    T get(int index) const;
    int indexOf(T element) const;
    bool isEmpty() const;
    int getSize() const;
    T removeAt(int index);

    // ------------- HERE BEGIN THE EXERCISE FUNCTIONS -------------
    bool contains(T element) const;
    int lastIndexOf(T element) const;
    void remove(T element);
    T set(int index, T element);
    LinkedList<T>& addAll(const LinkedList<T>& otherList);
    LinkedList<T>& removeAll(const LinkedList<T>& otherList);
    LinkedList<T>& retainAll(const LinkedList<T>& otherList);
    LinkedList<T> operator+(const LinkedList<T>& otherList);
    LinkedList<T> operator-(const LinkedList<T>& otherList);
    LinkedList<T> operator^(const LinkedList<T>& otherList);
    T& operator[](int index);
    const LinkedList<T>& operator=(const LinkedList<T>& otherList);

    Iterator<T> begin() const
    {
        return Iterator<T>(head);
    };

    Iterator<T> end() const
    {
        return Iterator<T>(tail->next);
    };

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

template<typename T>
LinkedList<T>::LinkedList()
{
    head = tail = NULL;
    size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>& list)
{
    head = tail = NULL;
    size = 0;

    Node<T>* current = list.head;
    while (current != NULL)
    {
        this->add(current->element);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<typename T>
void LinkedList<T>::addFirst(T element)
{
    Node<T>* newNode = new Node<T>(element);
    newNode->next = head;
    head = newNode;
    size++;

    if (tail == NULL)
        tail = head;
}

template<typename T>
void LinkedList<T>::addLast(T element)
{
    if (tail == NULL)
    {
        head = tail = new Node<T>(element);
    }
    else
    {
        tail->next = new Node<T>(element);
        tail = tail->next;
    }

    size++;
}

template<typename T>
T LinkedList<T>::getFirst() const
{
    if (size == 0)
        throw runtime_error("Index out of range");
    else
        return head->element;
}

template<typename T>
T LinkedList<T>::getLast() const
{
    if (size == 0)
        throw runtime_error("Index out of range");
    else
        return tail->element;
}

template<typename T>
T LinkedList<T>::removeFirst()
{
    if (size == 0)
        throw runtime_error("No elements in the list");
    else
    {
        Node<T>* temp = head;
        head = head->next;
        if (head == NULL) tail = NULL;
        size--;
        T element = temp->element;
        delete temp;
        return element;
    }
}

template<typename T>
T LinkedList<T>::removeLast()
{
    if (size == 0)
        throw runtime_error("No elements in the list");
    else if (size == 1)
    {
        Node<T>* temp = head;
        head = tail = NULL;
        size = 0;
        T element = temp->element;
        delete temp;
        return element;
    }
    else
    {
        Node<T>* current = head;

        for (int i = 0; i < size - 2; i++)
            current = current->next;

        Node<T>* temp = tail;
        tail = current;
        tail->next = NULL;
        size--;
        T element = temp->element;
        delete temp;
        return element;
    }
}

template<typename T>
void LinkedList<T>::add(T element)
{
    addLast(element);
}

template<typename T>
void LinkedList<T>::add(int index, T element)
{
    if (index == 0)
        addFirst(element);
    else if (index >= size)
        addLast(element);
    else
    {
        Node<T>* current = head;
        for (int i = 1; i < index; i++)
            current = current->next;
        Node<T>* temp = current->next;
        current->next = new Node<T>(element);
        (current->next)->next = temp;
        size++;
    }
}

template<typename T>
void LinkedList<T>::clear()
{
    while (head != NULL)
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    tail = NULL;
    size = 0;
}

template<typename T>
T LinkedList<T>::get(int index) const
{
    if (index < 0 || index > size - 1)
        throw runtime_error("Index out of range");

    Node<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current->element;
}

template<typename T>
int LinkedList<T>::indexOf(T element) const
{
    Node<T>* current = head;
    for (int i = 0; i < size; i++)
    {
        if (current->element == element)
            return i;
        current = current->next;
    }

    return -1;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
    return head == NULL;
}

template<typename T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<typename T>
T LinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= size)
        throw runtime_error("Index out of range");
    else if (index == 0)
        return removeFirst();
    else if (index == size - 1)
        return removeLast();
    else
    {
        Node<T>* previous = head;

        for (int i = 1; i < index; i++)
        {
            previous = previous->next;
        }

        Node<T>* current = previous->next;
        previous->next = current->next;
        size--;
        T element = current->element;
        delete current;
        return element;
    }
}

// ------------------------------------------------------------------------------
// ------------- HERE BEGIN THE EXERCISE FUNCTIONS ------------------------------
// ------------------------------------------------------------------------------

// Returns true if the list contains the specified element.
template<typename T>
bool LinkedList<T>::contains(T element) const
{
    Node<T>* current = head;
    for (int i = 0; i < size; i++)
    {
        if (current->element == element)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Returns the highest index in the list of the specified element.
// If the element is not found, return -1.
template<typename T>
int LinkedList<T>::lastIndexOf(T element) const
{
    int lastIndex = -1;
    Node<T>* current = head;
    for (int i = 0; i < size; i++)
    {
        if (current->element == element)
        {
            lastIndex = i;
        }
        current = current->next;
    }
    return lastIndex;
}

// Removes all occurrences of the specified element from the list.
template<typename T>
void LinkedList<T>::remove(T element)
{
    // Determine in which node the element to be removed is located
    int index = 0;
    Node<T>* current = head;
    int originalSize = size;
    for (int i = 0; i < originalSize; i++)
    {
        if (current->element == element)
        {
            if (index == 0) {
                removeFirst();
                current = head;
            } else if (index == size - 1) {
                removeLast();
            } else {
                // Establish new connections that are required post-removal and then remove
                Node<T> *previous = head;
                for (int j = 0; j < index; j++) {
                    previous = previous->next;
                }
                previous->next = current->next;
                delete current;
                current = previous->next;
                size--;
            }
        } else {
            current = current->next;
            index++;
        }
    }
}

// Sets the node at the specified index's element to the specified element
template<typename T>
T LinkedList<T>::set(int index, T element)
{
    Node<T>* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    T oldElement = current->element;
    current->element = element;
    return oldElement;
}

// Add the elements in otherList to this list and return this list.
template<typename T>
LinkedList<T>& LinkedList<T>::addAll(const LinkedList<T>& otherList)
{
    // Attach the tail node of the current list to the head of otherList
    // and properly adjust size
    size += otherList.size;
    tail->next = otherList.head;
    // Reassign the tail of the current list to the new final node
    tail = otherList.tail;
    return *this;
}

// Remove all the elements contained in otherList from this list
// and return this list.
template<typename T>
LinkedList<T>& LinkedList<T>::removeAll(const LinkedList<T>& otherList)
{
    Node<T>* current = otherList.head;
    for (int i = 0; i < otherList.size; i++)
    {
        if (contains(current->element))
        {
            remove(current->element);
        }
        current = current->next;
    }
    return *this;
}

// Retain the elements in this list if they are also in otherList
// and return this list.
template<typename T>
LinkedList<T>& LinkedList<T>::retainAll(const LinkedList<T>& otherList)
{
    Node<T>* current = head;
    for (int i = 0; i < size; i++)
    {
        if (!otherList.contains(current->element))
        {
            current = current->next;
            removeAt(i);
            size--;
            i--;
        } else {
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& otherList)
{
    return addAll(otherList);
}

template<typename T>
LinkedList<T> LinkedList<T>::operator-(const LinkedList<T>& otherList)
{
    return removeAll(otherList);
}

template<typename T>
LinkedList<T> LinkedList<T>::operator^(const LinkedList<T>& otherList)
{
    return retainAll(otherList);
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
    if (index < 0 || index > size - 1)
        throw runtime_error("Index out of range");

    Node<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current->element;
}

template<typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& otherList)
{
    // Create a node to copy the head of otherList
    Node<T>* firstNode = new Node<T>(otherList.head->element);
    this->head = firstNode;
    size = 1;
    Node<T>* current = firstNode;
    // Loop through otherList, creating copy nodes and connecting them
    for (int i = 1; i < otherList.size; i++) {
        current->next = new Node<T>(otherList.get(i));
        current = current->next;
        size++;
    }
    // Assign this->tail to the last copied node
    this->tail = current;
    return *this;
}

#endif //LINKEDLIST_LINKEDLIST_H