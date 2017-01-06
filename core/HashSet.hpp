// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include "LinkedList.hpp"


template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
	
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    //virtual void rehash();
   


private:
    HashFunction hashFunction;
    LinkedList<T>* set;
    int set_size = 0;
    int set_store = 0;
   // node* HashSet[DEFAULT_CAPACITY];
   

};


template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
	set_size=DEFAULT_CAPACITY;
	//set=new LinkedList<std::string>[DEFAULT_CAPACITY];
	set=new LinkedList<T>[DEFAULT_CAPACITY];
}


template <typename T>
HashSet<T>::~HashSet()
{
	delete[] set;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
	//for(int i=0; i<s.set_store; i++)
	//{
	HashSet<T> new_set;
	new_set.set=new LinkedList<T>[s.set_store];
	if(s.set==NULL)
	{
		return;
	}
		for(int i=0; i<s.set_store; i++)
		{
			for(int j=0; j<set[i].size_LL;j++)
			{
				if(set[i].getKey!=NULL)
					new_set.set[i]=set[i].getKey(j);
			}
		}
	//}
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        hashFunction = s.hashFunction;

    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}

template <typename T>
void HashSet<T>::add(const T& element)
{
	float ratio;
	
	if(set_size==0)
	{
		ratio=set_size;
	}
	else
	{
		ratio=set_size*.8;
		//std::cout<<std::fixed<<std::setprecision(5)<<ratio<<" ratio"<<std::endl;
	}
	

	//std::cout<<set_size<<"	"<<set_store<<" size ---- store"<<std::endl;
	
	if(set->exists(element)!=-1)
		return;
	if((float)set_store>=ratio)
	{

		//resize
		//std::cout<<set_size<<std::endl;
		//std::cout<<"resize"<<std::endl;
		int old_size=set_size;
		set_size=set_size*2;
		LinkedList<T>* newset=new LinkedList<T>[set_size];
		//std::cout<<"new set_size: "<<set_size<<std::endl;

		for(int i=0; i<old_size;++i)
		{
			int setsize=0;

			setsize=set[i].size_LL();
			//std::cout<<"setsize: "<<setsize<<std::endl;
			if(setsize!=0)
			{
				for(int j=0; j<setsize;++j)
				{
				//std::cout<<"j: "<<j<<std::endl;
				unsigned index=hashFunction(set[i].getKey(j))%set_size;
				newset[index].insert(newset[index].size_LL(), set[i].getKey(j));
				}
			}
		}

		LinkedList<T>* temp=set;
		set=newset;
		delete [] temp;
	}
//}
	//std::cout<<"element being addedd!"<<std::endl;
	//otherwise add element
	unsigned index=hashFunction(element)%set_size;
	set[index].insert(set[index].size_LL(),element);
	set_store++;
	
	
}

template <typename T>
bool HashSet<T>::contains(const T& element) const
{


	//std::cout<<"size: "<<set->size_LL()<<std::endl;
	//std::cout<<"size1: "<<set_size<<std::endl;
	
	
	
	//std::cout<<element<<std::endl;
	//std::cout<<hashFunction<<std::endl;
	//std::cout<<"elements: "<<element<<std::endl;
	unsigned index=hashFunction(element)%set_size;
	//std::cout<<set[index].exists(element)<<std::endl;
	//std::cout<<"get: "<<set->getItem(2)<<std::endl;
	//if(set->exists(element)!=-1)
	//	return true;

    //return false;

    return set[index].exists(element)!=-1;
    //return true;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
	return set_size;
    //return 0;
}



#endif // HASHSET_HPP

