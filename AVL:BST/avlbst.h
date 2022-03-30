#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"
#include <string>

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    bool isLeftChild(AVLNode<Key,Value>* curr);
    bool isRightChild(AVLNode<Key,Value>* curr);
    int updateHeight(AVLNode<Key,Value>* curr);
    void leftRotation(AVLNode<Key,Value>* Z);
    void rightRotation(AVLNode<Key,Value>* Z);
    void rightLeftZig(AVLNode<Key,Value>* Z);
    void leftRightZig(AVLNode<Key,Value>* Z);
    std::string determineRotation(AVLNode<Key,Value>* Z);
    int findHeight(AVLNode<Key,Value>* curr);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    if(this->root_==nullptr){
       AVLNode<Key,Value>* recent_insert=new AVLNode<Key,Value>(new_item.first,new_item.second,nullptr);
      recent_insert->setHeight(0);  //if tree is empty create new avl node and set it to the root 
       this->root_=recent_insert;
       return;
    }

    AVLNode<Key,Value>* key= new AVLNode<Key,Value>(new_item.first,new_item.second,nullptr); //create avl node pass it into helper function
    AVLNode<Key,Value>* recent_insert=static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::iterative_insert(key));
    recent_insert->setHeight(0); //set its height to 0
    std::string trail="";
    bool update=true;
    int l_sub;
    int r_sub;
    while(update){ //we will keep going up the tree if we are updating heights if we don't do anything we are balanced
        if(recent_insert->getParent()!=nullptr){ //check if we are at the top
            recent_insert=recent_insert->getParent();
        }
        else{
            return;
        }
        if(findHeight(recent_insert)==recent_insert->getHeight()){
            update=false;
            return;
        }
        else{
            int h=findHeight(recent_insert); //if not we will go up the tree updating the heights
            recent_insert->setHeight(h);
            if(recent_insert->getLeft()!=nullptr){
                 l_sub=recent_insert->getLeft()->getHeight(); //now test is the node is balanced
            }
            else{
                l_sub=-1;
            }
            if(recent_insert->getRight()!=nullptr){
                r_sub=recent_insert->getRight()->getHeight();
            }
            else{
                r_sub=-1;
            }
            if(std::abs(l_sub-r_sub)>1){//this means it is unbalanced, so we have to fix with a rotation
               trail=determineRotation(recent_insert);
                if(trail=="LL"){
                    rightRotation(recent_insert); //based on the path make the right rotaton
                }
                else if(trail=="LR"){
                    leftRightZig(recent_insert);
                }
                else if(trail=="RL"){
                    rightLeftZig(recent_insert);
                }
                else if(trail =="RR"){
                    leftRotation(recent_insert);
                }
            }
        }
    }
}



template<class Key,class Value>
int AVLTree<Key,Value>::findHeight(AVLNode<Key,Value>* curr){
    if(curr==nullptr){
        return -1;
    }
    int lhs=findHeight(curr->getLeft());
    int rhs=findHeight(curr->getRight()); //post order travesal to find heights 
    if(lhs>rhs){
        return lhs+1;
    }
    else{
        return rhs+1;
    }
}

template<class Key,class Value>
std::string AVLTree<Key,Value>::determineRotation(AVLNode<Key,Value>* Z){
    std::string temp="";
    AVLNode<Key,Value>* t=Z;
    int lhs;
    int rhs;
    if(t->getLeft()!=nullptr){      
        lhs=t->getLeft()->getHeight();
    }
    else{ 
        lhs=-1; //if node doesn't exist its height is -1
        }
    if(t->getRight()!=nullptr){
        rhs=t->getRight()->getHeight();
        }
    else{
        rhs=-1;
    }
    
    if(lhs>rhs){
        t=t->getLeft(); //we are going to go down the path with the heigher height
        temp+="L";   //L corresponds to going left, and R is going right 
    }
    else{
        t=t->getRight();
        temp+="R";
    }
    
    if(t->getLeft()!=nullptr){
        lhs=t->getLeft()->getHeight(); //go down to the next level
    }
    else{
        lhs=-1;
        }
    if(t->getRight()!=nullptr){
        rhs=t->getRight()->getHeight();
        }
    else{
        rhs=-1;
    }

    if(lhs==rhs){
        if(temp=="R"){
            temp="RR"; //always break ties by making it a diagonal pathway
        }
        else{
            temp="LL";
        }
    }
    else if(lhs>rhs){ //depending on which height is heigher we will go there
        temp+="L";
    }
    else{
        temp+="R";
    }
    return temp; //this will tell us what rotation to do

}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{

    std::string trail="";
    int l_sub;
    int r_sub;
   AVLNode<Key,Value>* recent_delete=static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::remove_helper(key));
    while(recent_delete!=nullptr){ //we will keep going up the tree until we are at the top 
        if(recent_delete==nullptr){
            return;
        }
        else{
            int h=findHeight(recent_delete); //if not we will go up the tree updating the heights
            recent_delete->setHeight(h); //set it's new height 
            if(recent_delete->getLeft()!=nullptr){
                 l_sub=recent_delete->getLeft()->getHeight(); //now test is the node is balanced
            }
            else{
                l_sub=-1;
            }
            if(recent_delete->getRight()!=nullptr){
                r_sub=recent_delete->getRight()->getHeight();
            }
            else{
                r_sub=-1;
            }
            if(std::abs(l_sub-r_sub)>1){//this means it is unbalanced, so we have to fix with a rotation
               trail=determineRotation(recent_delete);
                if(trail=="LL"){
                    rightRotation(recent_delete); //based on the path make the right rotaton
                }
                else if(trail=="LR"){
                    leftRightZig(recent_delete);
                }
                else if(trail=="RL"){
                    rightLeftZig(recent_delete);
                }
                else if(trail =="RR"){
                    leftRotation(recent_delete);
                }
            }
        }
        recent_delete=recent_delete->getParent(); //make your way up the tree
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: leftRotation(AVLNode<Key,Value>* Z)
{
    AVLNode<Key,Value>* ptemp=Z->getParent();
    AVLNode<Key,Value>* Y=Z->getRight(); //find XYZ
    AVLNode<Key,Value>* X=Y->getRight();
    AVLNode<Key,Value>* temp=Y->getLeft();
    Y->setLeft(Z);
    Z->setParent(Y);  //make the corret rotations
    Z->setRight(temp);
    if(temp!=nullptr){
        temp->setParent(Z);
    }
    Y->setParent(ptemp);
    if(ptemp==nullptr){
       this->root_=Y;
    }
    else{
        if(ptemp->getRight()==Z){
            ptemp->setRight(Y);
        }
        else{
            ptemp->setLeft(Y);
        }
    }
    int h=findHeight(Z); //set the height again to see if it changed after the rotation
        Z->setHeight(h); //adjust the heights
        h=findHeight(Y);
        Y->setHeight(h);
        h=findHeight(X);
        X->setHeight(h);
}

template<class Key, class Value>
void AVLTree<Key, Value>:: rightRotation(AVLNode<Key,Value>* Z)
{
    AVLNode<Key,Value>* ptemp=Z->getParent();
    AVLNode<Key,Value>* Y=Z->getLeft();
    AVLNode<Key,Value>* X=Y->getLeft();
    AVLNode<Key,Value>* temp=Y->getRight();
    Y->setRight(Z);
    Z->setParent(Y);
    Z->setLeft(temp);
    if(temp!=nullptr){
        temp->setParent(Z);
    }
    Y->setParent(ptemp);
    if(ptemp==nullptr){
        this->root_=Y;
    }
    else{
        if(ptemp->getRight()==Z){
            ptemp->setRight(Y);
        }
        else{
            ptemp->setLeft(Y);
        }
    }
     int h=findHeight(Z); //set the height again to see if it changed after the rotation
        Z->setHeight(h);
        h=findHeight(Y);
        Y->setHeight(h);
        h=findHeight(X);
        X->setHeight(h);
}

template<class Key, class Value>
void AVLTree<Key, Value>:: rightLeftZig(AVLNode<Key,Value>* Z)
{
    AVLNode<Key,Value>* ptemp=Z->getParent();
    AVLNode<Key,Value>* Y=Z->getRight();
    AVLNode<Key,Value>* X=Y->getLeft();
    AVLNode<Key,Value>* temp_r=X->getRight();
    AVLNode<Key,Value>* temp_l=X->getLeft();  //double rotation case where we rotate twice
    X->setLeft(Z);
    Z->setParent(X);
    Z->setRight(temp_l);
    if(temp_l!=nullptr){
        temp_l->setParent(Z);
    }
    X->setRight(Y);
    Y->setParent(X);
    Y->setLeft(temp_r);
    if(temp_r!=nullptr){
        temp_r->setParent(Y);
    }
    X->setParent(ptemp);

    if(ptemp==nullptr){
        this->root_=X;
    }
    else{
       if(ptemp->getRight()==Z){
           ptemp->setRight(X);
       }
       else{
           ptemp->setLeft(X);
       }
    } 

     int h=findHeight(Z); //set the height again to see if it changed after the rotation
        Z->setHeight(h);
        h=findHeight(Y);
        Y->setHeight(h);
        h=findHeight(X);
        X->setHeight(h);
}

template<class Key, class Value>
void AVLTree<Key, Value>:: leftRightZig(AVLNode<Key,Value>* Z)
{
    AVLNode<Key,Value>* ptemp=Z->getParent();
    AVLNode<Key,Value>* Y=Z->getLeft();
    AVLNode<Key,Value>* X=Y->getRight();
    AVLNode<Key,Value>* temp_r=X->getRight();
    AVLNode<Key,Value>* temp_l=X->getLeft();
    X->setRight(Z);
    Z->setParent(X);
    Z->setLeft(temp_r);
    if(temp_r!=nullptr){
        temp_r->setParent(Z);
    }
    X->setLeft(Y);
    Y->setParent(X);
    Y->setRight(temp_l);
    if(temp_l!=nullptr){
    temp_l->setParent(Y);
    }
    X->setParent(ptemp);
    if(ptemp==nullptr){
        this->root_=X;
    }   
    else{
       if(ptemp->getRight()==Z){
           ptemp->setRight(X);
       }
       else{
           ptemp->setLeft(X);
       }
    }  
     int h=findHeight(Z); //set the height again to see if it changed after the rotation
        Z->setHeight(h);
        h=findHeight(Y);
        Y->setHeight(h);
        h=findHeight(X);
        X->setHeight(h);
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
