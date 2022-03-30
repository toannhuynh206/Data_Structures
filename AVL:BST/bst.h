#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cmath>
/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    //void print() const;
    bool empty() const; 
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();
        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator++();
    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions

    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;
    void helper_clear(Node<Key, Value>* root);
    Node<Key, Value>* recursive_find(Node<Key, Value>* current, const Key& k)const; 
    int recursive_balance(const Node<Key,Value>* root)const;
    Node<Key,Value>* iterative_insert(Node<Key,Value>* new_insert);
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value>* remove_helper(const Key& k); 
    


protected:
      Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_=ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_=nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (rhs.current_==this->current_){
        return true;
    }
    else {
        return false;
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (rhs.current_!=this->current_){
        return true;
    }
    else {
        return false;
    }
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    Node<Key,Value> *temp=this->current_;
    if(temp->getRight()!=nullptr){
        temp=temp->getRight(); //case where there is a right child
        while(temp->getLeft()!=nullptr){
            temp=temp->getLeft();
        }
        BinarySearchTree<Key,Value>::iterator it=iterator(temp);
        this->current_=temp;
        return it;
    }
    else{
         Node<Key,Value> *root=this->current_;
         while(root->getParent()!=nullptr){
             root=root->getParent(); //case where there is no right child
         }                           //get the root node
         Node<Key,Value> *it_next=nullptr;
         while(root!=this->current_){   //
            if(root->getKey() > this->current_->getKey()){
                it_next=root;       //we know that once we find the current node the sucessor is the node with the current node as it's left child
                root=it_next->getLeft();
            }
            else{ //keep 
                root=root->getRight();
            }
         }

        BinarySearchTree<Key,Value>::iterator it=iterator(it_next);
        this->current_=it_next;
        return it;
    }
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_=nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == nullptr;
}




/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/

template<class Key,class Value>
Node<Key,Value>* BinarySearchTree<Key,Value>::iterative_insert(Node<Key, Value>*  new_node){
    bool searching=true;
    if(this->root_ == nullptr){
       this->root_ = new_node;
       return new_node;
   }
    Node<Key, Value>* temp = internalFind(new_node->getKey()); 
    if (temp != nullptr){
        temp->setValue(new_node->getValue()); //overwrite curr value with updated value
        delete new_node; 
        return temp;
    }
   Node<Key, Value>* curr = this->root_; //start at the top
   while(searching){ //runs until it returns the new node that's been inserted
        if(new_node->getKey()>=curr->getKey()){ //first case handles = or greater
            if(curr->getKey()==new_node->getKey()){ //if we find the key is already in list update the node
                curr->setValue(new_node->getValue()); 
                searching=false;        //if the inserted node is greater go to the right child
                return curr;
            }
           if(curr->getRight() == nullptr){ 
               curr->setRight(new_node);
               new_node->setParent(curr);
               searching=false;
               return new_node;
           }
           else{
               curr = curr->getRight();
           }
       }
       else if(new_node -> getKey()<curr->getKey()){   //if the inserted node is smaller go to left child
            if(curr->getLeft() == nullptr){
                curr->setLeft(new_node);
                new_node->setParent(curr);
                searching=false;
                return new_node;
            }
           else{
               curr = curr->getLeft();
           }
       }
   }
}



template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Node<Key,Value>* new_insert=new Node<Key,Value>(keyValuePair.first,keyValuePair.second,nullptr); //create new node then call helper
    iterative_insert(new_insert);  
}

template<class Key, class Value>
Node<Key,Value>* BinarySearchTree<Key, Value>::remove_helper(const Key& k)
{
    BinarySearchTree<Key,Value>::iterator it=find(k); //find X
    if(it.current_==nullptr){
        return nullptr;
    }
    Node<Key,Value>* temp=it.current_;
    if(temp->getLeft()==nullptr&&temp->getRight()==nullptr){  //LEAF NODE
         Node<Key,Value>* p=temp->getParent();
         if(p==nullptr){  //case where are our tree only has 1 node
             delete temp;
             root_=nullptr;
             return nullptr;
         }
         if(p->getRight()==temp){   //case where it is a leaf node, if it's a leaf node just delete the node and set it's parents to null
             p->setRight(nullptr);
         }
         else{
             p->setLeft(nullptr);
         }
        delete temp; //delete the node
        return p;   //return the parent 
    }
    else if(temp->getRight()==nullptr&&temp->getLeft()!=nullptr){  //case where X has 1 child, delete X then promote its child
        Node<Key,Value>* child=temp->getLeft();
        Node<Key,Value>* p=temp->getParent();
        if(p==nullptr){
            if(temp->getRight()==child){
            child->setRight(nullptr);
            child->setParent(nullptr);
             delete temp;
             root_=child;
            return child;
            }
            else{
                child->setLeft(nullptr);
                child->setParent(nullptr);
                delete temp;
                root_=child;
                return child;
            }
        }
         if(p->getRight()==temp){
            p->setRight(child);
            child->setParent(p);
        }
        else{
            p->setLeft(child);
            child->setParent(p);
        }
        
         delete temp;
         return child;
    }
    else if(temp->getRight()!=nullptr&&temp->getLeft()==nullptr){ //case where X has 1 child delete X then promote it's child
        Node<Key,Value>* child=temp->getRight();
        Node<Key,Value>* p=temp->getParent();
         if(p==nullptr){
            if(temp->getRight()==child){
            child->setRight(nullptr);
            child->setParent(nullptr);
            delete temp;
            root_=child;
            return child;
            }
             else{
                child->setLeft(nullptr);
                child->setParent(nullptr);
                delete temp;
                root_=child;
                return child;
            }
        }
        if(p->getRight()==temp){
            p->setRight(child);
            child->setParent(p);
        }
        else{
            p->setLeft(child);
            child->setParent(p);
        }
         delete temp;
         return child;
    }
    else if(temp->getRight()!=nullptr&&temp->getLeft()!=nullptr){ //case where 2 childs where we swap with predecessor
         Node<Key,Value>* pred=predecessor(temp);
         nodeSwap(pred,temp);
         if(temp->getLeft()==nullptr&&temp->getRight()==nullptr){    //if x is a leaf after the swap we simply just delete it
            Node<Key,Value>* p=temp->getParent();
            if(p->getRight()==temp){   
                p->setRight(nullptr);
            }
            else{
                p->setLeft(nullptr);
            }
        delete temp;
        return p;
    }
        else if(temp->getRight()==nullptr&&temp->getLeft()!=nullptr){ //case where X has 1 child, delete X then promote its child
            Node<Key,Value>* child=temp->getLeft();
            Node<Key,Value>* p=temp->getParent();
            if(p==nullptr){
                if(temp->getRight()==child){
                    child->setRight(nullptr);
                    child->setParent(nullptr);
                    delete temp;
                    root_=child;
                    return child;
                }
            else{
                child->setLeft(nullptr);
                child->setParent(nullptr);
                root_=child;
                delete temp;
                return child;
            }
        }
            if(p->getRight()==temp){
                p->setRight(child);
                child->setParent(p);
            }
            else{
                p->setLeft(child);
                child->setParent(p);
            }
            delete temp;
            return child;
            }
        }
    }

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
   remove_helper(key);
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
   Node<Key,Value>* temp=current->getLeft(); //the left subtree's most right child
   while(temp->getRight()!=nullptr){
       temp=temp->getRight();
   }
   return temp;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/

template<class Key,class Value>
 void BinarySearchTree<Key,Value>::helper_clear(Node<Key, Value>* root){
     if(root==nullptr){
         return;
     }
    helper_clear(root->getLeft());
    helper_clear(root->getRight());
    delete root;
 }



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    if(root_==nullptr){
        return;
    }
    if(root_->getLeft()==nullptr&&root_->getRight()==nullptr){
        delete root_;
        root_=nullptr;
    }
    else{
        helper_clear(root_);
        root_=nullptr;
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if(root_==nullptr){
        return nullptr;
    }
    Node<Key,Value> *temp=root_; //smallest node is the most left node in the tree
    while(temp->getLeft()!=nullptr){
        temp=temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/


template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::recursive_find(Node<Key, Value>* current,const Key& k) const
{
    if(current==nullptr){ //this means we reached the bottom of the tree and the item does not exist
       return nullptr;
   }
   else if(current->getKey()==k){
           return current;  //return current if we found the item
       }
   else if(current->getKey()>=k){ //depending on what we are trying to insert go left or right 
       recursive_find(current->getLeft(),k);
   }
   else if(current->getKey()<=k){
     recursive_find(current->getRight(),k);
   }
   
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    Node<Key,Value>* temp=recursive_find(root_,key);
    return temp;
}

/**
 * Return true iff the BST is balanced.
 */

template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::recursive_balance(const Node<Key,Value>* root) const{
    if(root==nullptr){
        return -1;    //post order traversal to find balance, start from the bottom finding heights
    }           
    int left_subtree=recursive_balance(root->getLeft());
    if(left_subtree==-2){
        return -2;
    }
    int right_subree=recursive_balance(root->getRight());
    if(right_subree==-2){
        return -2;
    }
    int difference=abs(left_subtree-right_subree);
    if(difference>1){ //if left subtree and right subtree difference greater than one that means it is unbalanced
        return -2;
    }
    else{
    return (1+std::max(left_subtree,right_subree));
    }
}


template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
  int r= recursive_balance(root_);
  if(r==-2){
      return false;
  }
    else{
        return true;
    }
}
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
//#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
