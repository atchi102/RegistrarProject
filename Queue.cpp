#include <iostream>
#include "DoublyLL.cpp"

using namespace std;


template <class T>
class Queue
{
  public:
    Queue();
    ~Queue();
    void insert(T data);
    T remove();
    T peek();
    bool isEmpty();
    int numElements;
    int getSize();
    DoublyLL<T> myQueue;
};


template <class T>
Queue<T>::Queue()
{
  numElements = 0;
}


template <class T>
Queue<T>::~Queue()
{

}


template <class T>
void Queue<T>::insert(T data)//enqueue
{
  myQueue.insertBack(data);
  numElements++;
}


template <class T>
T Queue<T>::remove()//dequeue
{
  T temp = myQueue.removeFront();
  --numElements;
  return temp;
}


template <class T>
T Queue<T>::peek()
{
  return myQueue.getFront()->data;
}


template <class T>
bool Queue<T>::isEmpty()
{
  return (numElements == 0);
}


template <class T>
int Queue<T>::getSize()
{
  return numElements;
}
