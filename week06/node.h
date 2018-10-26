/***********************************************************************
 * Header:
 *    node
 * Summary:
 *    This class contains the notion of an node
 * Author
 *    Garrett Smith & Aiden Reid
 ************************************************************************/

#ifndef node_H
#define node_H

#include <cassert>
#include <iostream>
using namespace std;

 // a little helper macro to write debug code
#ifdef NDEBUG
#define Debug
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

	/****************************************************
	 * node
	 * A class that holds stuff as part of a linked list
	 ***************************************************/
	template <class T>
	class Node
	{
	public:
		T data;
		Node *pNext;
		Node *pPrev;
		// constructors and destructors
		Node() : data(T), pNext(NULL), pPrev(NULL) {}
		Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
	};

	template<class T>
	Node<T> * find(Node<T>* pHead, const T & t)
	{
	}

	template<class T>
	void freeData(Node<T> * head) throw (const char *)
	{
		try
		{
			if (head->pPrev != NULL)
			{
				throw ("Cannot delete without head of list.");
			}
			if (head->pNext == NULL)
				delete head;
			else
				freeData(head->pNext);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
	}
	template<class T>
	Node<T> *remove(const Node<T>* pNode) throw (const char *)
	{
		try
		{
			Node <T> temp();
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;

			if (pNode->pPrev != NULL)
			{
				temp = pNode->pPrev;
			}
			else
			{
				temp = pNode->pNext;
			}

			delete pNode;
			return temp;
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
	}

	template <class T>
	Node <T> * copy(const Node <T> * pNode) throw (const char *)
	{
		try
		{
			if (pNode != NULL)
			{
				cout << pNode->data << " ";
				display(pNode->pNext);
			}
			else
				return 0;
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not display due to - " << e.what() << endl;
		}
	}

	template <class T>
	Node <T> * insert(Node <T> * pNode, const T & t) throw (const char *)
	{
		try
		{
			if(pNode != NULL)
			{
				Node <T> * newNode = new Node <T>(t);
				newNode->pNext = pNode;
				newNode->pPrev = pNode->pPrev;
				pNode->pPrev = newNode;
				return newNode;
			}
			else
			{
				Node <T> * newNode = new Node <T>(t);
				return newNode;
			}
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
	}

	template <class T>
	Node <T> *insert(Node <T> * pNode, const T & t, const bool after) throw (const char *)
	{
		try
		{
			if (after && pNode != NULL)
			{
				Node <T> * newNode = new Node <T> (t);
				if(pNode->pNext != NULL)
					pNode->pNext->pPrev = newNode;
				newNode->pNext = pNode->pNext;
				newNode->pPrev = pNode;
				pNode->pNext = newNode;
				return newNode;
			}
			else if(!after && pNode != NULL)
			{
				Node <T> * newNode = new Node <T>(t);
				newNode->pNext = pNode;
				newNode->pPrev = pNode->pPrev;
				pNode->pPrev = newNode;
				return newNode;
			}
			else
			{
				Node <T> * newNode = new Node <T>(t);
				return newNode;
			}
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
	}

	template <class T>
	void display(const Node <T> * pNode) throw (const char *)
	{
		try
		{
			if (pNode != NULL)
			{
				cout << pNode->data << " ";
				display(pNode->pNext);
			}
			else
				return;
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not display due to - " << e.what() << endl;
		}
	}

	template <class T>
	ostream & operator <<(ostream & out, const Node <T> * pNode) throw (const char *)
	{
		try
		{
			display(pNode);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Insertion operator not working due to - " << e.what() << endl;
		}
	}
}; // namespace custom

#endif // set_H