#include <iostream>
using namespace std;

template <class T> class SLinkedList {
public:
  class Node;

protected:
  Node *head;
  Node *tail;
  int count;

public:
  SLinkedList(Node *_head = NULL, Node *_tail = NULL) {
    this->head = _head;
    this->tail = _tail;
  };
  ~SLinkedList() {
    delete head;
    delete tail;
  };
  virtual void add(T e);
  virtual void addIdx(int index, const T &e);
  virtual T get(int index);
  virtual void set(int index, const T &e);
  virtual int indexOf(const T &e);
  virtual bool contains(const T &e);
  virtual bool removeItem(const T &e);
  virtual T removeAt(int index);
  virtual int size();
  virtual bool isEmpty();
  virtual void clear();
  virtual void print();

public:
  class Node {
  private:
    T data;
    Node *next;
    friend class SLinkedList<T>;

  public:
    Node() { next = 0; }
    Node(Node *next) { this->next = next; }
    Node(T data, Node *next = NULL) {
      this->data = data;
      this->next = next;
    }
  };
};

template <class T> void SLinkedList<T>::add(const T e) {
  // add tail
  Node *newNode = new Node(e, NULL);
  if (this->head == NULL) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
    this->count++;
  }
};

template <class T> void SLinkedList<T>::addIdx(int index, const T &e) {
  /* Insert an element into the list at given index. */
  Node *newNode = new Node(e, NULL);

  if (this->head == NULL) {
    if (index != 0) {
      return;
    } else {
      this->head = newNode;
      this->tail = newNode;
      this->count++;
      return;
    }
  } else if (this->head != NULL) {
    if (index == 0) {
      newNode->next = this->head;
      head = newNode;
      this->count++;
      return;
    }

    Node *curr = this->head;
    Node *prev = NULL;
    int i = 0;

    while (i < index) {
      prev = curr;
      curr = curr->next;
      i++;
    }
    if (size() == index) {
      tail->next = newNode;
      tail = newNode;
      this->count++;
    } else {
      newNode->next = curr;
      prev->next = newNode;
      this->count++;
    }
  }
}

template <class T> int SLinkedList<T>::size() {
  /* Return the length (size) of list */
  return this->count;
}

template <class T> T SLinkedList<T>::removeAt(int index) {
  Node *curr = this->head;
  Node *prev = NULL;
  int i = 0;
  T temData;

  if (index == 0) {
    temData = head->data;
    // delete head;
    this->head = head->next;
    this->count--;
  } else {
    while (curr != NULL) {
      if (curr == tail) {
        temData = tail->data;
        this->tail = prev;
        prev->next = NULL;
        this->count--;
      } else if (i == index) {
        temData = curr->data;
        prev->next = curr->next;
        delete curr;
        this->count--;
        break;
      }
      prev = curr;
      curr = curr->next;
      i++;
    }
  }
  return temData;
};

template <class T> T SLinkedList<T>::get(int index) {
  /* Give the data of the element at given index in the list. */
  int i = 0;
  Node *curr = this->head;
  if (index < size()) {
    while (i < index) {
      curr = curr->next;
      i++;
    }
    return curr->data;
  }
  return -1;
}

template <class T> void SLinkedList<T>::set(int index, const T &e) {
  /* Assign new value for element at given index in the list */
  int i = 0;
  Node *curr = head;
  if (index < size()) {
    while (i < index) {
      curr = curr->next;
      i++;
    }
    curr->data = e;
  }
  return;
}

template <class T> bool SLinkedList<T>::isEmpty() {
  /* Check if the list is empty or not. */
  if (size() == 0) {
    return 1;
  }
  return 0;
}

template <class T> int SLinkedList<T>::indexOf(const T &item) {
  /* Return the first index wheter item appears in list, otherwise return -1 */
  int i = 0;
  for (Node *curr = this->head; curr != NULL; curr = curr->next) {
    if (get(i) == item) {
      return i;
    }
    i++;
  }
  return -1;
}

template <class T> bool SLinkedList<T>::contains(const T &item) {
  /* Check if item appears in the list */
  if (indexOf(item) != -1) {
    return true;
  }
  return false;
}

template <class T> bool SLinkedList<T>::removeItem(const T &item) {
  /* Remove the first apperance of item in list and return true, otherwise
   * return false */
  Node *curr = this->head;
  Node *prev = NULL;

  if (curr->data == item) {
    delete head;
    head = curr->next;
    this->count--;
    return true;
  } else {
    while (curr != NULL) {
      if (curr->data == item) {
        if (curr == tail) {
          delete prev->next;
          this->tail = prev;
          count--;
          return true;
        }
        prev->next = curr->next;
        delete curr;
        count--;
        return true;
      }
      prev = curr;
      curr = curr->next;
    }
  }
  return false;
}

template <class T> void SLinkedList<T>::clear() {
  /* Remove all elements in list */
  Node *curr = this->head;
  Node *temp = NULL;
  while (curr != NULL) {
    temp = curr->next;
    delete curr;
    curr = temp;
  }

  this->head = NULL;
  this->tail = NULL;
  this->count = 0;
}

template <class T> void SLinkedList<T>::print() {
  Node *curr = this->head;
  cout << "SLinkedList: ";
  while (curr != NULL) {
    cout << curr->data << " ";
    curr = curr->next;
  }
  cout << endl;
}

template <class T> class Stack {
private:
  SLinkedList<T> list;

  // public:
  //   Stack();

public:
  virtual void push(T e);
  virtual T pop();
  virtual T peek();
  virtual bool empty();
  virtual int size();
  virtual void clear();
  virtual bool remove(T item);
  virtual void displayStack();
};

template <class T> void Stack<T>::push(T item) { list.addIdx(0, item); };

template <class T> T Stack<T>::pop() { return list.removeAt(0); };

template <class T> T Stack<T>::peek() { return list.get(0); };

template <class T> bool Stack<T>::empty() { return list.isEmpty(); };

template <class T> void Stack<T>::clear() { return list.clear(); };

template <class T> bool Stack<T>::remove(T item) {
  return list.removeItem(item);
};

template <class T> int Stack<T>::size() { return list.size(); };

template <class T> void Stack<T>::displayStack() { list.print(); };

int main() {
  
  Stack<int> *s = new Stack<int>;
  for (int i = 0; i < 10; i++) {
    (*s).push(i);
  }
  s->displayStack();
  s->pop();
  s->displayStack();
  s->push(100);
  s->push(200);
  s->displayStack();
  s->clear();
  s->displayStack();
  delete s;

  /*SLinkedList<int> *l = new SLinkedList<int>;
  for (int i = 1; i < 10; i++) {
    l->add(i);
  }
  l->print();
  l->removeAt(3);
  l->removeAt(0);
  l->removeAt(6);
  l->print();
  l->addIdx(0, 20);
  l->addIdx(7, 22);
  l->print();
  l->clear();
  l->print();
  delete l;
*/
  return 0;
}
// using nested class after inherit
/*
check isEmpty() or not --> throw exception
when pop() execute;
*/