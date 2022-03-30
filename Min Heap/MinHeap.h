
#include <stdexcept>
#include <map>
#include <vector>
#include <iostream>
#include <exception>

template <class T>
  class MinHeap {
     public:
       MinHeap (int d);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
    
       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

       bool isEmpty ();
         /* returns true iff there are no elements on the heap. */

        void Bubbleup(int pos);

        void TrickleDown(int pos); 

        void print();

        void heap_swap(int x ,int y);

        void update(int node, int priority);

        int peek_id () ;

        void print_array();
   private:
     int size;
     int max;
     int d_ary;
     int order_count;
     struct Item{
         Item(const T&,int num,int id);
         T val;
         int priority;
         int id;
     };
     std::vector<Item *> a;
     std::vector<int> map;
  };

template<typename T>
void MinHeap<T>::print_array(){ //helper function to help debug
    for(unsigned int i=0;i<a.size();i++){
        std::cout<<a[i]->id<<" ";
    }
}

template<typename T>
MinHeap<T>::Item::Item(const T& v, int num, int pos){
    val=v;
    id=pos;
    priority=num;
}

template<typename T>
void MinHeap<T>::heap_swap(int x,int y){ //helper swap function
     Item* temp=a[y];
     a[y]=a[x];  //swap for the heap
     a[x]=temp;

     int temp_loc=map[a[y]->id];
     map[a[y]->id]=map[a[x]->id]; //swap for the location of the node in the map array
     map[a[x]->id]=temp_loc;
}




template<typ T>
MinHeap<T>::MinHeap(int d){

    size =0;
    d_ary=d;
    order_count=0;

}

template<class T>
MinHeap<T>::~MinHeap(){

    for(unsigned int i=0;i<a.size();i++){
        delete a[i];
    }

}

template<class T>
bool MinHeap<T>::isEmpty(){

    if(size==0){
        return true;
    }
    return false;

}
template<class T>
void MinHeap<T>::add(T item, int priority){

    Item* n = new Item(item,priority,order_count); //create new item and it to our heap
    a.push_back(n);
    map.push_back(size);
    Bubbleup(size);
    order_count++;
    size++;

}

template <class T>
void MinHeap<T>::Bubbleup(int pos){
    
    if(pos > 0 && a[pos]->priority < a[(pos-1)/d_ary]->priority){
        heap_swap(pos,(pos-1)/d_ary);   // we want to swap only if the child is smaller than the parent then we call bubble up again recursivly to keep bubbling it up
        Bubbleup((pos-1)/d_ary);
    }
    else{
        if(a[pos]->priority==a[(pos-1)/d_ary]->priority){ //breaking ties case 
            if(a[pos]->val<a[(pos-1)/d_ary]->val){
                heap_swap(pos,(pos-1)/d_ary);
                Bubbleup((pos-1)/d_ary);
            }
        }
    }

}

template <class T>
const T& MinHeap<T>::peek()const{

    if(size==0){
        throw std::logic_error("No items in our heap");
    }
    else{
        return a[0]->val;
    }

}

template <class T>
   int MinHeap<T>::peek_id(){ //helper function to help debug

    if(size==0){
        throw std::logic_error("No items in our heap");
    }
    else{
        return a[0]->id;
    }
}



template <class T>
void MinHeap<T>::remove(){

    if(isEmpty()){
        throw std::logic_error("No items in our heap");
    }
    if(size==1){
        size--;
        delete a[0];
        a.clear();
    }
    else{
        heap_swap(0,size-1);
        delete a[size -1];
        a.pop_back();
        size--;
        TrickleDown(0);
    }

}

template<class T>
void MinHeap<T>::TrickleDown(int pos){

    int child=d_ary*pos+1;
    if(child<size){
        for(int i=1;i<=d_ary;i++){ //find the smallest node of the parent so if we swap we swap with the right node
            if(d_ary*pos+i<size){
                if(a[d_ary*pos+i]->priority<a[child]->priority){
                    child= d_ary*pos + i;
                }
            }
        }
        if (a[child]->priority<a[pos]->priority){ //only swap if the parent is smaller than the child, then we call Trickledown reccursily 
            heap_swap(child,pos);
            TrickleDown(child);
        }
        else{
             if(a[child]->priority==a[pos]->priority){
                 if(a[child]->val<a[pos]->val){
                    heap_swap(child,pos);
                    TrickleDown(child);
                 }
             }
        }
    }

}

template<class T>
void MinHeap<T>::update(int node, int priority) {

    int location = map[node];
    if(a[location]->priority < priority) {
      a[location]->priority = priority;
      TrickleDown(location);
    } 
   else {
      a[location]->priority = priority;
       Bubbleup(location);
   }

}





template <class T>
void MinHeap<T>::print(){ //helper function to help debug

    for(int i=0;i<size;i++){
        std::cout<<a[i]->val<<" ";
    }
    
}

