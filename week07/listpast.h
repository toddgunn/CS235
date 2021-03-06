/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    This will contain just the prototype for list().
 * Author
 *    Garrett Smith, Aiden Reid, Ian Stubbs
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>
using namespace std;

namespace custom
{
	/****************************************************
	* list
	* A class that holds stuff as part of a linked list
	***************************************************/
	template <class T>
	class list
	{
	private:
		Node <T> *pHead;
		Node <T> *pTail;
		int numElements;
	public:
		//The Node Class
		class Node;

		// the various iterator interfaces
		class iterator;
		class reverse_iterator;

		list() : numElements(0) 
		{ 
			pHead();
			pTail(); 
			pHead->pNext = pTail;
			pTail->pPrev = pHead;
		}
		list(const list & rhs) throw (const char *);
		~list() {this->clear()};

		list & operator = (const list & rhs);

		int size() const { return numElements; }
		bool empty() const { return (numElements == 0) ? true : false; }
		void clear();

		void push_back(const T & t) throw (const char *);
		void push_front(const T & t) throw (const char *);
		void pop_back();
		void pop_front();

		T & back()       throw (const char *);
		T & front()       throw (const char *);
		T & back() const throw (const char *);
		T & front() const throw (const char *);

		iterator find(T t) const throw (const char *);
		iterator erase(iterator it) throw (const char *);
		iterator insert(iterator it, T &t) throw (const char *);
		iterator insert(iterator it, T &t, bool after) throw (const char *);
		iterator begin() { return iterator(pHead); }
		iterator end() { return iterator(pTail->pNext); }

		reverse_iterator rbegin() { return iterator(pTail); }
		reverse_iterator rend() { return iterator(pHead->pPrev); }

		;

	};





	/*******************************************
	* list :: Assignment
	 *******************************************/
	template <class T>
	list <T> & list <T> :: operator = (const list <T> & rhs) throw (const char *)
	{

		this->num = rhs.num;
		this->pHead = rhs->pHead;
		this->pTail = rhs->pTail;

		return *this;
	}

	/*******************************************
	 * list :: COPY CONSTRUCTOR
	 *******************************************/
	template <class T>
	list <T> ::list(const list <T> & rhs) throw (const char *)
	{
		this->num = rhs.num;
		this->pHead = rhs.pHead;
		this->pTail = rhs.pTail;
	}

	template<class T>
	void list<T>::clear()
	{
		for (iterator it = begin(); it != end(); it = erase(it));
	}

	template<class T>
	void list<T>::push_back(const T & t) throw(const char *)
	{
		try
		{
			iterator it(end());
			insert(it, t);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: unable to allocate a new node for a list" << endl;
		}
	}

	template<class T>
	void list<T>::push_front(const T & t) throw(const char *)
	{
		try
		{
			iterator it(pHead);
			insert(it, t, true);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: unable to allocate a new node for a list" << endl;
		}
	}

	template<class T>
	void list<T>::pop_back()
	{
		try
		{
			iterator it(pTail);
			erase(it);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not find due to - " << e.what() << endl;
		}
	}

	template<class T>
	void list<T>::pop_front()
	{
		try
		{
			iterator it(pHead);
			erase(it);
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not find due to - " << e.what() << endl;
		}
	}

	/**********************************************
	 * list : FRONT
	 * returns the most recent value added, if no
	 * values have been added, throw exception
	 **********************************************/

	template <class T>
	T &list<T>::front() throw (const char*)
	{

		if (size() > 0)
			return pHead->data;
		else
			throw "ERROR: unable to access data from an empty list";

	}

	/**********************************************
	 * list : BACK
	 * returns the most recent value added, if no
	 * values have been added, throw exception
	 **********************************************/
	template <class T>
	T &list<T>::back() throw (const char*)
	{

		if (size() > 0)
			return pTail->data;
		else
			throw "ERROR: unable to access data from an empty list";

	}

	template<class T>
	typename list <T> ::iterator list <T>::find(T t) const throw(const char *)
	{
		try
		{
			if (pHead->data == t)
			{
				return iterator(pHead);
			}
			else
			{
				if (pHead->pNext != NULL) return find(pHead->pNext, t);
			}

			return end();
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not find due to - " << e.what() << endl;
		}
	}

	template<class T>
	typename list <T> ::iterator list <T>::erase(iterator it) throw(const char *)
	{
		try
		{
			Node <T> * temp;

			if (it == end()) return;

			//Handles most cases but removing the first element or last element in the list
			else if (it != begin())
			{
				it->pPrev->pNext = it->pNext;
				temp = it->pPrev;
				if (it->pNext != end())
				{
					it->pNext->pPrev = it->pPrev;
					temp = it->pNext;
				}
				return iterator(temp);
			}

			//Handles removing the first element but not the last element in the list
			else if (it->pNext != end())
			{
				it->pNext->pPrev = it->pPrev;
				temp = it->pNext;
				return iterator(temp);
			}

			//Handles removing the last element in the list
			else
			{
				return;
			}
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
		return iterator();
	}

	template<class T>
	typename list <T> ::iterator list <T>::insert(iterator it, T &t) throw(const char *)
	{
		try
		{
			if (it != NULL)
			{
				Node <T> * newNode = new Node <T>(t);
				if (it != begin())
					it->pPrev->pNext = newNode;
				newNode->pNext = it.p;
				newNode->pPrev = it->pPrev;

				it->pPrev = newNode;
				return iterator(newNode);
			}
			else
			{
				Node <T> * newNode = new Node <T>(t);
				return iterator(newNode);
			}
		}
		catch (const bad_alloc & e)
		{
			cout << "ERROR: Can not insert due to - " << e.what() << endl;
		}
	}

	template<class T>
	typename list <T>:: iterator list <T>::insert(iterator it, T &t, bool after) throw(const char *)
	{
		try
		{
			if (after && it != NULL)
			{
				Node <T> * newNode = new Node <T>(t);
				if (it->pNext != end())
					it->pNext->pPrev = newNode;
				newNode->pNext = it->pNext;
				newNode->pPrev = it.p;
				it->pNext = newNode;
				return iterator(newNode);
			}
			else if (!after && it != NULL)
			{
				insert(it, t);
			}
			else
			{
				Node <T> * newNode = new Node <T>(t);
				return newNode;
			}
		}





		/**************************************************
		* set ITERATOR
		* An iterator through list
		*************************************************/
		template <class T>
		class list <T> ::iterator
		{
		private:
			Node *p;
		public:
			// constructors, destructors, and assignment operator
			iterator() : p(NULL) {}
			iterator(Node *p) : p(p) {}
			iterator(const iterator & rhs) : p(rhs.p) {}


			iterator & operator = (const iterator & rhs)
			{
				this->p = rhs.p;
				return *this;
			}

			iterator & operator = (const T p)
			{
				*this->p = p;
				return *this;
			}

			// equals, not equals operator
			bool operator != (const T *p) const { return (this->p != p); }
			bool operator == (const T *p) const { return (this->p == p); }

			// equals, not equals operators for iterators
			bool operator != (const iterator & rhs) const { return p != rhs.p; }
			bool operator == (const iterator & rhs) const { return p == rhs.p; }

			// less than and greater than
			bool operator < (const T *p) const { return (this->p < p); }
			bool operator > (const T *p) const { return (this->p > p); }

			// less than or greater than
			bool operator < (const iterator & rhs) const { return p < rhs.p; }
			bool operator > (const iterator & rhs) const { return p > rhs.p; }

			// dereference operator
			T & operator * () { return *p; }

			//Addition
			iterator & operator + (int val)
			{
				for (int i = 0; i < val > 0; i++)
					p++;
				return *this;
			}

			// prefix increment
			iterator & operator ++ ()
			{
				p++;
				return *this;
			}

			// postfix increment
			iterator operator ++ (int postfix)
			{
				iterator tmp(*this);
				p++;
				return tmp;
			}

			// prefix decrement
			iterator & operator -- ()
			{
				p--;
				return *this;
			}

			// postfix decrement
			iterator operator -- (int postfix)
			{
				iterator tmp(*this);
				p--;
				return tmp;
			}
		};

		/**************************************************
		* LIST REVERSE_ITERATOR
		* An reverse_iterator through list
		*************************************************/
		template <class T>
		class list <T> ::reverse_iterator
		{
		private:
			Node *p;
		public:
			// constructors, destructors, and assignment operator
			reverse_iterator() : p(NULL) {}
			reverse_iterator(Node *p) : p(p) {}
			reverse_iterator(const reverse_iterator & rhs) : p(rhs.p) {}


			reverse_iterator & operator = (const reverse_iterator & rhs)
			{
				this->p = rhs.p;
				return *this;
			}

			reverse_iterator & operator = (const T p)
			{
				*this->p = p;
				return *this;
			}

			// equals, not equals operator
			bool operator != (const T *p) const { return (this->p != p); }
			bool operator == (const T *p) const { return (this->p == p); }

			// equals, not equals operators for reverse_iterators
			bool operator != (const reverse_iterator & rhs) const { return p != rhs.p; }
			bool operator == (const reverse_iterator & rhs) const { return p == rhs.p; }

			// less than and greater than
			bool operator < (const T *p) const { return (this->p > p); }
			bool operator > (const T *p) const { return (this->p < p); }

			// less than or greater than
			bool operator < (const reverse_iterator & rhs) const { return p > rhs.p; }
			bool operator > (const reverse_iterator & rhs) const { return p < rhs.p; }

			// dereference operator
			T & operator * () { return *p; }

			//Addition
			reverse_iterator & operator + (int val)
			{
				for (int i = 0; i < val > 0; i++)
					p--;
				return *this;
			}

			// prefix increment
			reverse_iterator & operator ++ ()
			{
				p--;
				return *this;
			}

			// postfix increment
			reverse_iterator operator ++ (int postfix)
			{
				reverse_iterator tmp(*this);
				p--;
				return tmp;
			}

			// prefix decrement
			reverse_iterator & operator -- ()
			{
				p++;
				return *this;
			}

			// postfix decrement
			reverse_iterator operator -- (int postfix)
			{
				reverse_iterator tmp(*this);
				p++;
				return tmp;
			}
		};

		/****************************************************
		* Node
		* A class that holds stuff as part of a linked list
		***************************************************/
		template <class T>
		class list <T> ::Node
		{
		public:
			T data;
			Node *pNext;
			Node *pPrev;

			// constructors and destructors
			Node() : data(T()), pNext(NULL), pPrev(NULL) {}
			Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
		};

	};
};
#endif // list_H