#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <iostream>

template <typename T>
class LinkedQueue : public QueueADT<T>
{
private:
    Node<T>* backPtr;
    Node<T>* frontPtr;

public:
    LinkedQueue();
    bool isEmpty() const;
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
    bool peek(T& frntEntry) const;
    int GetCount() const;              // ✅ ADDED
    void print() const;                // ✅ ADDED
    ~LinkedQueue();
};

// Constructor
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    backPtr = nullptr;
    frontPtr = nullptr;
}

// isEmpty
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontPtr == nullptr);
}

// enqueue
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);
    if (isEmpty())
        frontPtr = newNodePtr;
    else
        backPtr->setNext(newNodePtr);
    backPtr = newNodePtr;
    return true;
}

// dequeue
template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
    if (isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    if (nodeToDeletePtr == backPtr)
        backPtr = nullptr;

    delete nodeToDeletePtr;
    return true;
}

// peek
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
    if (isEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;
}

// ✅ ADDED FUNCTION: GetCount
template <typename T>
int LinkedQueue<T>::GetCount() const
{
    int count = 0;
    Node<T>* current = frontPtr;
    while (current)
    {
        count++;
        current = current->getNext();
    }
    return count;
}

// ✅ ADDED FUNCTION: print
template <typename T>
void LinkedQueue<T>::print() const
{
    Node<T>* current = frontPtr;
    while (current)
    {
        if (current->getItem())
            std::cout << *(current->getItem()) << ", ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

// Destructor
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    std::cout << "\nStarting LinkedQueue destructor...";
    std::cout << "\nFreeing all nodes in the queue...";

    T temp;
    while (dequeue(temp));

    std::cout << "\n Is LinkedQueue Empty now?? ==> " << std::boolalpha << isEmpty();
    std::cout << "\nEnding LinkedQueue destructor..." << std::endl;
}

#endif
