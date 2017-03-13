#if !defined (QUEUELINKED_H)
#define QUEUELINKED_H

#include "NextNode.h"

template < class T >
class QueueLinked
{

   private:
      NextNode<T>* back;
      int sze;
	  QueueLinked<T>* list;

   public:
      QueueLinked();
      ~QueueLinked();
      bool isEmpty();
      int size();
      void dequeueAll(); 
      T* peek();
      T* dequeue();
      void enqueue(T* item);

};

template < class T >
QueueLinked<T>::QueueLinked()
{
   back = NULL;
   sze = 0;
   
}

template < class T >
QueueLinked<T>::~QueueLinked()
{
   dequeueAll();
}

template < class T >
bool QueueLinked<T>::isEmpty()
{
    return sze == 0;
}

template < class T >
int QueueLinked<T>::size()
{
    return sze;
}

template < class T >
void QueueLinked<T>::dequeueAll()
{
   if (sze == 0) return;

   NextNode<T>* prev = NULL;
   NextNode<T>* curr = back->getNext();  //the head
   back->setNext(NULL);  //break the bridge link

   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      delete prev;
   }

   sze = 0;
}

template < class T >
T* QueueLinked<T>::peek()
{
    T* item = NULL;
    if (!isEmpty()) 
    {  
      // queue is not empty; retrieve front
      NextNode<T>* head = back->getNext();
      item = head->getItem();
    }
    return item;
}

template < class T >
void QueueLinked<T>::enqueue(T* item)
{
    NextNode<T>* node = new NextNode<T>(item);

    //DO THIS (enqueueing the first item is a special case)

	if (sze == 0) // adding the first item
	{
		back = node; //node becomes the back
		node->setNext(node); //node points to itself
	}
	else 
	{
		node->setNext(back->getNext());//sets the node's next to the head
		back->setNext(node);// sets back so that is now point to the new node
		back = node;//makes our new node the new back
	}

    sze++;
}

template < class T >
T* QueueLinked<T>::dequeue()
{
    T* item = NULL;

    //DO THIS (dequeueing the last item is a special case)
    //also, check that there are items before dequeueing

	if(sze == 0) return NULL; //if the array is empty do nothing
	
	if(sze == 1)
	{
		item = getNext(back);
		back->setNext(NULL);
		back = NULL;
	}
	else
	{
		item = getNext(back);
		NextNode<T>* temp = getNext(back);
		NextNode<T>* node = getNext(back);
		
		node = getNext(node); //gets the item after head
		back->setNext(node); //makes the item after the current head the new head
		
		item->setNext(NULL); //destroys the item's link
	}
	
	sze--;
    return item;
}

#endif
