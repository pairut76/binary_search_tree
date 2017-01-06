// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    struct avl_node
    {
        T key;
        avl_node *left, *right;
        //int height;
        avl_node(const T& object)
        {
            key=object;
            left=NULL;
            right=NULL;
            //height=1;
        }
    };
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;
    //virtual int getHeight(avl_node * loc);


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void copier(avl_node *&dest, avl_node *&source);
    virtual void add(const T& element);
    virtual void addr(avl_node *&_root, const T& element);
    //virtual delet_nodes(avl_node *&_root, const T&element);

    virtual void delete_nodes(avl_node *&_root, const T& element);
    virtual avl_node * find(avl_node *_root, const T& element) const;
    //virtual avl_node * find(avl_node *_root, const T& element) const;



    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;
    

private:
    avl_node *root;
    int size_avl;

};


template <typename T>
BSTSet<T>::BSTSet()
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    while(root!=NULL)
        delete_nodes(root, root->key);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    if(s.root==NULL)
        root=NULL;
    else
        copier(this->root, s.root);
}
template <typename T>
void BSTSet<T>::copier(avl_node *&dest, avl_node *&source)
{
    if(source==NULL)
        dest=NULL;
    else
    {
        dest=new avl_node(source->key);
        //dest->key=source->key;
        copier(dest->left, source->left);
        copier(dest->right, source->right);
    }
}

template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    if(root==NULL)
    {
        //avl_node temp=new avl_node(element);
        root=new avl_node(element);
        size_avl++;
        return;
    }
    else
        addr(root, element);
}
template <typename T>
void BSTSet<T>::addr(avl_node *&_root, const T & element)
{
    if(_root==NULL)
    {
        _root=new avl_node(element);
        size_avl++;
    }
    else if(element >_root->key)
    {
        //std::cout<<"adding to right"<<std::endl;
        addr(_root->right, element);
    }
    else//(element <_root->key)
    {
        //std::cout<<"adding to left"<<std::endl;

        addr(_root->left, element);
    }
    //if(element==root->key)
    //    return;        
    
}
template <typename T>
void BSTSet<T>::delete_nodes(avl_node *&_root, const T& element)
{
    
    if(_root==NULL)
        return;
    else if(element>_root->key)
        delete_nodes(_root->right, element);
    else if(element<_root->key)
        delete_nodes(_root->left, element);
    //else if(_root)
    
    else if(_root->right==NULL)
    {
        avl_node *temp=_root;
        _root=_root->left;
        delete temp;
        size_avl--;
    }
    else if(_root->left==NULL)
    {
        avl_node *temp=_root;
        _root=_root->right;
        delete temp;
        size_avl--;
    }
    
    else
    {
        avl_node *lower=_root;
        lower=lower->right;
        while(lower->left!=NULL)
            lower=lower->left;
        _root->key=lower->key;
        delete_nodes(_root->right, _root->key);
    }
/*
    while(_root!=NULL)
    {
        if(element>_root->key)
            _root=_root->right;

        else if(element<_root->key)
            _root=_root->left;
        else if(_root->right==NULL)
        {
            avl_node *temp=_root;
            _root=_root->left;
            delete temp;
            size_avl--;
        }
        else if(_root->left==NULL)
        {
            avl_node *temp=_root;
            _root=_root->right;
            delete temp;
            size_avl--;
        }
        else
        {
            avl_node *lowest=_root;
            lowest=lowest->right;
            while(lowest->left!=NULL)
                lowest=lowest->left;
            _root->key=lowest->key;
        }
        std::cout<<"while"<<std::endl;

    }
    return;
*/
}
template <typename T>
typename BSTSet<T>::avl_node * BSTSet<T>::find(avl_node *_root, const T& element)const
{
    if(_root==NULL)
        return NULL;
    if(_root->key==element)
        return _root;
    else if(_root->key<element)
        return find(_root->right, element);
    else
        return find(_root->left, element);
}
template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
	//BSTSet new_bst;
	//copier(new_bst.root, root);
	//std::cout<<"object: "<<new_bst.root->key<<std::endl;
    return find(root, element)!=NULL;
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return size_avl;
}



#endif // BSTSET_HPP

