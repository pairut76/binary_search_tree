
#include <iostream>

#include <fstream>


template <typename T>
class LinkedList
{
	struct Node
	{
		T key;
		Node *next;
		Node *prev;
		Node(const T &keys, Node *newnext=NULL, Node *newprev=NULL):
		 key(keys), next(newnext), prev(newprev){}
	};
	Node *head;
	Node *tail;
	int size=0; //size of the linkedlist
public:
	~LinkedList()
	{
		while(size!=0)
		{
			delete_node();
		}
	}
	
	void delete_node()
	{
		
		
			Node *node=NULL;

			if(size==1)
			{
				node=head;
				head=NULL;
				tail=NULL;
				size--;
			}
			else
			{
				node=head;
				head=head->next;
				head->prev=NULL;
				size--;
			}
			delete node;
			
	}

	void insert(int index, T key)
	{
		if(index>size||size<0)//check for valid index
		{
			return;
		}
		Node *nnode=new Node(key);

			if(size==0)
			{
				//std::cout<<"m1"<<std::endl;
				head=nnode;
				tail=nnode;
				nnode->next=NULL;
				nnode->prev=NULL;
				size++;
			}
			/*
			else if(index==0)
			{
				std::cout<<"---------------m2"<<std::endl;

				head->prev=nnode;
				nnode->next=head;
				head=nnode;
				size++;
			}
			*/
			else if(index==size)
			{
				//std::cout<<"-----------m3"<<std::endl;

				nnode->prev=tail;
				nnode->next=NULL;
				tail->next=nnode;
				tail=nnode;
				size++;
			}
			/*
			else
			{
				std::cout<<"----------------m4"<<std::endl;

				Node *n=head;
				for(int i=0; i<index; i++)
					n=n->next;
				nnode->next=n;
				nnode->prev=n->prev;
				n->prev->next=nnode;
				n->prev=nnode;
				size++;
			}
			*/
		//}
		return;
	}
	T getKey(int index)
	{
		//std::cout<<"size in getItem: "<<size<<std::endl;
		//return if(index<size)? getKey(index-1)->next->key: NULL;//head->key

		if(index<size)
		{
			Node *temp=head;
			//std::cout<<"temp: "<<temp->key<<std::endl;
			for(int i=0; i<size; i++)
			{
				if(i==index)
					return temp->key;
				temp=temp->next;

			}
		}
		return NULL;
	
	}

	int size_LL()
	{
		return size;
	}
	int exists(const T& find_key)//returns index
	{
		Node *hnode=head;
		//std::cout<<"size: "<<size<<std::endl;
		for(int i=0; i<size;i++)
		{
			//std::cout<<"node->key: "<<hnode->key<<std::endl;
			if(hnode->key==find_key)
				return i;
			hnode=hnode->next;
		}
		return -1;
			
	}
	
	
};
















