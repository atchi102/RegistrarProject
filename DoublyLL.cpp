#include <iostream>
#include "ListNode.cpp"


using namespace std;

template <class T>
class DoublyLL
{
    private:
      ListNode<T> *head;
      ListNode<T> *back;
      unsigned int size;

    public:
      DoublyLL();
      ~DoublyLL();
      void insertFront(T d);
      T removeFront();

      void insertBack(T d);
      T removeBack();

      ListNode<T>* getFront();
      ListNode<T>* getBack();

      T getAt(T pos);
      bool insertAfter(T key, T value);

      T deleteNode(T key);

      unsigned int getSize();
      bool isEmpty();

};

template <class T>
DoublyLL<T>::DoublyLL()
{
  size = 0;
  head = NULL;
  back = NULL;
}

template <class T>
DoublyLL<T>::~DoublyLL()
{

}

template <class T>
void DoublyLL<T>::insertFront(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0)
  {
    back = node;
  }
  else
  {
    head->prev = node;
    node->next = head;
  }
  head = node;
  ++size;
}

template <class T>
T DoublyLL<T>::removeFront()
{
  ListNode<T> *temp = head;
  if(head->next == NULL)
  {
    back = NULL;
  }
  else
  {
    head->next->prev = NULL;
  }

  head=head->next;
  T val = temp->data;
  size--;

  return val;
}

template <class T>
T DoublyLL<T>::deleteNode(T key)
{
  ListNode<T> *current = head;

  while(current->data !=key)
  {
    current = current->next;
    if(current == NULL)
      return NULL;
  }

  //we found something
  if(current == head)
  {
    head = current->next;
  }
  else
  {
    current->prev->next = current->next;
  }

  if(current == back)
  {
    back = current->prev;
  }
  else
  {
    current->next->prev = current->prev;
  }

  current->next = NULL;
  current->prev = NULL;

  --size;
  return current->data;
}

template <class T>
void DoublyLL<T>::insertBack(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0)
  {
    head = node;
  }
  else
  {
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <class T>
T DoublyLL<T>::removeBack()
{
  ListNode<T> *temp = back;
  if(back->prev == NULL)
  {
    head = NULL;
  }
  else
  {
    back->prev->next = NULL;
  }

  back=back->prev;
  T val = temp->data;

  return val;
}

template <class T>
ListNode<T>* DoublyLL<T>::getFront()
{
  return head;
}

template <class T>
ListNode<T>* DoublyLL<T>::getBack()
{
    return back;
}

template <class T>
T DoublyLL<T>::getAt(T pos)
{
  ListNode<T> *current = head;
  int index = 0;

  while(index != pos)
  {
    current = current->next;
    if(current == NULL)
      return NULL;
  }
  return current->data;
}

template <class T>
bool DoublyLL<T>::insertAfter(T key, T value)
{
  ListNode<T> *current = head;

  while(current->data != key)
  {
    current = current->next;
    if(current == NULL)
      return false;
  }

  ListNode<T> *node = new ListNode<T>(value);
  if(current == back)
  {
    insertBack(value);
  }
  else
  {
    node->prev = current;
    node->next = current->next;
    current->next->prev = node;
    current->next = node;
  }
  return true;
}

template <class T>
unsigned int DoublyLL<T>::getSize()
{
  return size;
}

template <class T>
bool DoublyLL<T>::isEmpty()
{
  if(size == 0)
    return true;
  else
    return false;
}
