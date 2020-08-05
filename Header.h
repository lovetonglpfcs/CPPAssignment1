#pragma once
#include <iostream>
using namespace std;
template<class object>
class List;

template<class object>
class ListItr;

template<class object>
class ListNode {
	ListNode(const object& theElement = object(), ListNode* n = NULL) : element(theElement), next(n) {
	}
	object element;
	ListNode *next;

	friend class List<object>;
	friend class ListItr<object>;
};

template<class object>
class ListItr {
	public:
		ListItr():current(NULL){}
		bool isPastEnd()const { return current == NULL; }
		void advance() { if (!isPastEnd())current = current->next; }
		const object& retrieve() const {
			if (!isPastEnd())return current->element;
			exit(1);
		}
	private:
		ListNode<object> *current;
		ListItr(ListNode<object> *theNode):current(theNode){}
		friend class List<object>;
};

template<class object>
class List {
	public:
		List();
		List(const List & rhs);
		~List();

		bool isEmpty() const;
		void makeEmpty();
		ListItr<object> zeroth() const;
		ListItr<object> first() const;
		void insert(const object& x, const ListItr<object>& p);
		ListItr<object> find(const object & x)const;
		ListItr<object> findPrevious(const object & x)const;
		void remove(const object & x);
		const List& operator=(const List & rhs);

	private:
		ListNode<object>* header;
};
#include <iostream>
using namespace std;
template<class object>
List<object>::List() {
	header = new ListNode<object>;
}

template<class object>
bool List<object>::isEmpty() const {
	return header->next == NULL;
}

template<class object>
ListItr<object> List<object>::zeroth() const {
	return ListItr<object>(header);
}

template<class object>
ListItr<object> List<object>::first() const {
	return ListItr<object>(header->next);
}

template<class object>
ListItr<object> List<object>::find(const object& x) const {
	ListNode<object>* itr = header->next;
	while (itr != NULL && itr->element != x)
		itr = itr->next;
	return ListItr<object>(itr);
}
template<class object>
void List<object>::remove(const object& x) {
	ListItr<object> p = findPrevious(x);
	if (p.current->next != NULL) {
		ListNode<object>* oldNode = p.current->next;
		p.current->next = p.current->next->next;
		delete oldNode;
	}
}

template<class object>
ListItr<object> List<object>::findPrevious(const object& x) const {
	ListNode<object>* itr = header;
	while (itr->next != NULL && itr->next->element != x)
		itr = itr->next;
	return ListItr<object>(itr);
}
template<class object>
void List<object>::insert(const object& x, const ListItr<object>& p) {
	if (p.current != NULL)
		p.current->next = new ListNode<object>(x, p.current->next);
}

template<class object>
void List<object>::makeEmpty() {
	while (!isEmpty())
	{
		remove(first().retrieve());
	}
}

template<class object>
List<object>::~List() {
	makeEmpty();
	delete header;
}

template<class object>
void printList(const List<object>& theList) {
	if (theList.isEmpty())
		cout << "Empty list" << endl;
	else
	{
		ListItr<object> itr = theList.first();
		for (; !itr.isPastEnd(); itr.advance())
			cout << itr.retrieve() << " ";
	}
	cout << endl;
}

