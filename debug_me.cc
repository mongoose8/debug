// compile with: g++ -Wall -ggdb -o debug_me debug_me.cc

#include <iostream>
# include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int number_instantiated = 0;

template <class T> class Item {
public:
  Item (const T &value, Item<T> *next = 0) : value_(value), next_(next) {
    cout << "Creating Item, "
         << ++number_instantiated
         << " currently in existence." << endl;
  }
  ~Item () {
    cout << "Destroying Item, "
         << --number_instantiated
         << " currently in existence." << endl;
    next_ = 0;
  }

  Item<T>* next () const { return next_; }
  void next (Item<T> *new_next) { next_ = new_next; };
  const T& value () const { return value_; }
  void value (const T &value) { value_ = value; }

private:
  Item ();
  T value_;
  Item<T> *next_;
};
  
template <class T> class LinkedList {
public:
  LinkedList () : head_(0) {};
  ~LinkedList () { delete_nodes (); };

  // returns 0 on success, -1 on failure
  int insert (const T &new_item) {
    return ((head_ = new Item<T>(new_item, head_)) != 0) ? 0 : -1;
  }

  // returns 0 on success, -1 on failure
  int remove (const T &item_to_remove) {
    Item<T> *marker = head_;
    Item<T> *temp = 0;  // temp points to one behind as we iterate
      

    while (marker != 0) 
     {
         
      if (marker->value() == item_to_remove) 
       {
        if (temp == 0) 
         {  //marker is the first element in the list
          if (marker->next() == 0) 
            
           {
           
            head_ = 0;
            
            delete marker; // marker is the only element in the list
            
            marker = 0;
            //break;
           } 
           else 
           {
            head_ = new Item<T>(marker->value(), marker->next());
            delete marker;
           // delete temp;
            marker = 0;
           // break;
            }
          return 0;
          } 
          else 
          {
           
          temp->next (marker->next());
         // delete temp;
          delete marker;
          //temp=0;
          marker = 0;
         // break;
          return 0;
          }
           
      }
      //marker = 0;  // reset the marker
      
      //break;
      temp = marker;
      //delete marker;
      marker = temp->next();
     
     
    }

    return -1;	// failure
  }

  void print() {
    Item<T> *marker = head_;
    cout << "Current state of list:" << endl;
    do {
      cout << marker->value() << endl;
      
      marker = marker->next();
    } while (marker != 0);
    cout << endl;
   
  }

//private:
  void delete_nodes() {
    Item<T> *marker = head_;
    while (marker != 0) {
      Item<T> *temp = marker;
      delete marker;
      marker = temp->next();
    }
  }
        
  Item<T> *head_;
};

int main(int argc, char* argv[]) {

  LinkedList<int> *list = new LinkedList<int> ();

  list->insert (1);
  list->insert (2);
  list->insert (3);
  list->insert (4);

  list->print();
 
  cout << endl << "Now removing elements:" << endl;
  
  list->remove(2);
  list->print();
  
 
  list->remove(4);
  list->print();
  
 
  list->remove(1);
  list->print();
  
 
  list->remove(2);
  list->print();
  
 
  list->remove(3);
  list->print();

  delete list;

  return 0;
}
