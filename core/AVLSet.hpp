// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP
//#include "LinkedList.hpp"
#include "Set.hpp"
#include <string>


template <typename T>
class AVLSet : public Set<T>
{
public:
    struct avl_node
    {
        T key;
        avl_node *left, *right;
        int height;
        //int size_avl;
        

        avl_node(const T& item)
        {
            key=item;
            left=NULL;
            right=NULL;
            height=1;
            //size_avl=0;
        }

    };
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);
    virtual void copier(avl_node *&dest, avl_node *&source);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);
  	

    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;
    virtual void balance(avl_node *&_root);
    virtual int setHeight(avl_node *&_root);
    virtual int getHeight(avl_node *loc);
    virtual void RotateL(avl_node *&_root);
    virtual void RotateR(avl_node *&_root);
    virtual int check_balance(avl_node *loc);

    //virtual void copier(avl_node *copy, avl_node *original);
 



    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);
    virtual void addr(avl_node  *&_root, const T& element);
    virtual void delete_nodes(avl_node *&_root, const T& element);
    //virtual avl_node * findlowest(avl_node *_root);
    virtual avl_node * find(avl_node *_root, const T&element) const;

    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


    


private:
    avl_node *root;
    int size_avl;

};


template <typename T>
AVLSet<T>::AVLSet()
{
    root=NULL;
    size_avl=0;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    //remove(root->item)

    while(root!=NULL)
    {
        delete_nodes(root, root->key);
    }
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
	//AVLSet new_root;
	/*
	avl_node *temp=new avl_node(root->key);
    s.root=temp;
    s.size_avl++;

	//AVLSet new_root;
    while(root!=NULL)
	{
		//if(s.root->key==element)
		//{
			addr(s.root, root->key);
		//}
		if(s.root->left!=NULL)
			root=root->left;
		else
			root=root->right;
	}
	*/
	if(s.root==NULL)
        root=NULL;
    else
        copier(this->root, s.root);
}
template <typename T>
void AVLSet<T>::copier(avl_node *& dest, avl_node *&source)
{
	if(source!=NULL)
	{
		copier(dest, source->left);
		copier(dest, source->right);
		addr(dest, source->key);
	}
}

template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    //root=copyNodes(s.root);
    //AVLSet new_root;
    //copier(new_root.root, s.root)
    //return new_root;
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    //std::cout<<"being added: "<<element<<std::endl;

    if(root==NULL)
    {
    	//std::cout<<"root==NULL add"<<std::endl;
        //avl_node *temp=
        root=new avl_node(element);
        size_avl++;
        return;
    }
    else
    {
        //std::cout<<"root value add: "<<root->key<<std::endl;
        addr(root,element);
    }
    
}

template <typename T>

void AVLSet<T>::addr(avl_node *&_root, const T& element)
{
	//std::cout<<element<<std::endl;
   //std::cout<<"enter addr"<<std::endl;
    //std::cout<<_root->key<<std::endl;
    if(_root==NULL)
    {
    	//std::cout<<"root==NULL addr"<<std::endl;
        //std::cout<<"value added"<<std::endl;
        _root=new avl_node(element);
        size_avl++;
    }
    else if(element >_root->key)
    {
    	//std::cout<<"current rootL "<<_root->key<<std::endl;
    	//std::cout<<"element: "<<element<<std::endl;
        //std::cout<<"element>root"<<std::endl;
        //_root->right;
        //std::cout<<_root->key<<std::endl;
        addr(_root->right, element);
    }
    else if(element<_root->key)
    {
        //std::cout<<"element<root"<<std::endl;
        //_root->left;
        //std::cout<<_root->key<<std::endl;
        addr(_root->left,element);
    }
    
    if(element==root->key)
        return;
    //balance
    //balance(_root);
    //check balance//
    //int h_left=getHeight(_root->left);
    //int h_right=getHeight(_root->right);
    //std::cout<<"Left, Right: "<<h_left<<" "<<h_right<<std::endl;
    //int bal=check_balance(_root);
    //std::cout<<"root: "<<_root->key<<std::endl;
    //while(!(bal<=1 && bal>=-1))
    //{
    //	std::cout<<"unbalanced: "<<_root->key<<std::endl;
    //	if(_root==NULL)
    //	{
    //		break;
    //	}
    //std::cout<<"balancing"<<std::endl;
    balance(_root);
    //	bal=check_balance(_root);

    //}
    //std::cout<<bal<<std::endl;
    //int balance=check_balance(_root);
    //std::cout<<balance<<std::endl;



    //balance(_root);
}
template <typename T>
int AVLSet<T>::check_balance(avl_node * loc)
{
	return getHeight(loc->left)-getHeight(loc->right);
}


template <typename T>
void AVLSet<T>::delete_nodes(avl_node *&_root, const T& element)
{
    //std::cout<<"deleting! "<<_root->key<<std::endl;

    if(_root==NULL)
    {
    	//std::cout<<"root==NULL delete"<<std::endl;
        //std::cout<<"done"<<std::endl;
        return;
    }

    else if(element > _root->key)
    {
        //std::cout<<"element>root "<<element<<std::endl;
        delete_nodes(_root->right, element);
    }
        
    else if(element < _root->key)
     {
        //std::cout<<"element<root "<<element<<std::endl;
        //std::cout<<_root->left<<std::endl;
        delete_nodes(_root->left, element);
    }
    
    else if(_root->right==NULL)
    {
        //std::cout<<"delete left"<<std::endl;
        avl_node * temp=_root;
        _root=_root->left;
        delete temp;
        size_avl--;
    }
    else if(_root->left==NULL)
    {
        //std::cout<<"delete right"<<std::endl;
        avl_node * temp=_root;
        _root=_root->right;
        delete temp;
        size_avl--;
    }

    else
    {
        //std::cout<<"being deleted: "<<_root->key<<std::endl;
        //T l_key;

        //_root->key=findlowest(_root->right)->key;


        avl_node *lowest=_root;
        lowest=lowest->right;
        while(lowest->left!=NULL)
    	{
    	//std::cout<<_root->key<<std::endl;
        	lowest=lowest->left;
        	//std::cout<<"in loop: "<<lowest->key<<std::endl;
    	}
    	_root->key=lowest->key;
   	 	//return _root;

        
        //_root->key=findMin(_root->right)->key;
        
        //avl_node *root_copy=_root;
        //root_copy=root_copy->right;
        //std::cout<<root_copy->key<<std::endl;
        //std::cout<<root->right<<std::endl;

        /*
        root=root->right;
        while(root->left!=NULL)
        {
        	std::cout<<"in loop: "<<std::endl;
        	std::cout<<root->key<<std::endl;
            root=root->left;
           
        }
        std::cout<<"key being replaced: "<<_root->key<<std::endl;
        _root->key=root->key;
        std::cout<<"key found: "<<root->key<<std::endl;
        */

        //root->key=l_key;
        //_root->key=_root->key
        delete_nodes(_root->right, _root->key);
    }
    balance(_root);

}

template <typename T>
void AVLSet<T>::balance(avl_node *&_root)
{

    //std::cout<<"balancing tree"<<std::endl;
//while(!(check_balance(_root)<=1&&check_balance(_root)>=1))
 //{
    //std::cout<<"balancing"<<std::endl;
    //std::cout<<"height_before: "<<_root->height<<std::endl;
    if(_root==NULL)
    {

        return;
    }
    //std::cout<<"setHeight"<<std::endl;
    
    _root->height=setHeight(_root);
    //std::cout<<"height: "<<_root->height<<std::endl;

    //std::cout<<_root->left->height<<" h on left"<<std::endl;
    //std::cout<<_root->right->height<<" h on right"<<std::endl;
    //if(_root->right!=NULL&&_root->left!=NULL)

    //{
    //int balance=getHeight(_root->left)-getHeight(t->right);
    //if( <=-1 )
    	if(check_balance(_root) > 1)
    	{
    		if(getHeight(_root->left->right) > getHeight(_root->left->left))
    		{
    			//std::cout<<"in rotate L"<<std::endl;
        		RotateL(_root->left);
    		}
    		//rotate right
   			RotateR(_root);
        	//std::cout<<"balance right"<<std::endl;
        	//balanceRight(_root);
    	}
    	if(check_balance(_root) < -1)
    	{
        	//std::cout<<"balance left"<<std::endl;
    		if(getHeight(_root->right->left) > getHeight(_root->right->right))
    		{
    			//std::cout<<"in rotate R"<<std::endl;
    			RotateR(_root->right);
    		}
    		RotateL(_root);
        	//balanceLeft(_root);
    	}
    //}
    _root->height=setHeight(_root);
    //std::cout<<"height_after: "<<_root->height<<std::endl;

// }
}
template <typename T>
int AVLSet<T>::getHeight(avl_node *loc)
{
	/*
	if(loc==NULL)
	{
		return 0;
	}
	else
		return loc->height;
		*/
	return loc==NULL? 0: loc->height;
}

template <typename T>
int AVLSet<T>::setHeight(avl_node *& _root)
{
	//std::cout<<"setting height"<<std::endl;
	return _root==NULL ? 0: getHeight(_root->right)>getHeight(_root->left)? 
	getHeight(_root->right)+1 : getHeight(_root->left)+1;
/*
    if(_root==NULL)
    //if(_root->left==NULL&&_root->right==NULL)
    {
    	//std::cout<<"set height null"<<std::endl;
        return 0;
    }

    //std::cout<<"root: "<<_root->key<<std::endl;
    //if(_root->right!=NULL&&_root->left!=NULL)
    //{
    	//std::cout<<"right is not null"<<std::endl;

    	if(getHeight(_root->right) > getHeight(_root->left))
    	{
    		//std::cout<<"h_right > h_left"<<std::endl;
        	return (getHeight(_root->right))+1;
   		}
    //std::cout<<"afer rot"<<std::endl;
    	//if(_root->right->height < _root->left->height)
    	else
    	{
    		//std::cout<<"h_right < h_left"<<std::endl;
        	return getHeight(_root->left)+1;
    	}
    	//return 1;
   	//}
   	
    
    //else
    //{
    	//std::cout<<"return 1"<<std::endl;
    //	return 1;
    //}
    */
}
template <typename T>
void AVLSet<T>::RotateL(avl_node *& _root)
{
	//std::cout<<"in rotate L"<<std::endl;
    avl_node * _node=_root->right;
    _root->right=_node->left;
    _node->left=_root;
    _root->height=setHeight(_root);
    _root=_node;
}

template <typename T>
void AVLSet<T>::RotateR(avl_node *& _root)
{
	//std::cout<<"in rotate R"<<std::endl;
    avl_node * _node=_root->left;
     _root->left=_node->right;
     _node->right=_root;
    _root->height=setHeight(_root);
    _root=_node;
}


template <typename T>
typename AVLSet<T>::avl_node * AVLSet<T>::find(avl_node * _root, const T& element) const
{
	
	//std::cout<<_root->key<<" find"<<std::endl;
	if(_root==NULL)
	{

		//std::cout<<"-----null"<<std::endl;
		return NULL;
	}
	
	if(_root->key==element)
	{
		//std::cout<<"inside find: "<<_root->key<<std::endl;
		return _root;
	}
	else if(_root->key<element)
	{
		//std::cout<<"<"<<std::endl;
		return find(_root->right, element);
	}

	//else //if(element>_root->key)
	//{
		//
	else //if(_root->key>element)
	{
		//std::cout<<"else"<<std::endl;
		return find(_root->left, element);
	}

	//std::cout<<"inside find: "<<_root->key<<std::endl;
	return NULL;
	//}
	//else 
	//{
	//	find(_root,element);
	//}
	/*
	while(_root!=NULL)
	{
		if(_root->key==element)
		{
			return _root;
		}
		if(element<_root->key)
			_root=_root->left;
		else
			_root=_root->right;
	}
	return NULL;
	*/
}

template <typename T>
bool AVLSet<T>::contains(const T& element) const
{

    //std::cout<<"current root: "<<root->key<<std::endl;
    //for (avl_node * p=root; p; p=p->right)
    //{
     //   std::cout<<root->key<<std::endl;

    //}
    //std::cout<<"word looking for: "<<element<<std::endl;
    //if(find(root, "forgotten"))
    //	std::cout<<find(root, element)->key<<std::endl;
    //avl_node* loc=find(root, element);
    //std::cout<<"after find"<<std::endl;
    //if(loc!=NULL)
    //	std::cout<<"found: "<<loc->key<<std::endl;
    //	return true;
    //return find(root, element)!=NULL;
    //return false;
    //std::cout<<root->key<<" --first"<<std::endl;
    //AVLSet new_root;
    //new_root.root=root;
    return find(root, element)!=NULL;
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return size_avl;
}



#endif // AVLSET_HPP

