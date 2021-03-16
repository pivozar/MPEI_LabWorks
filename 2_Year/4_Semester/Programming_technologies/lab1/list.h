#pragma once

template <typename Type>
class List {
public:
	struct Node {
		Node(Type new_value, Node* next)
			: value(new_value), next(next) {};
		Type value;
		Node* next;
	};

	List();
	List(const List& list);

	~List();

	List& operator=(const List& right);

	void PushFront(const Type& value);
	void PushBack(const Type& value);
	void InsertAfter(Node* node, const Type& value);
	void RemoveAfter(Node* node);
	void PopFront();

	Node* GetHead() { return head; }
	const Node* GetHead() const { return head; }
	void _clear();

private:
	Node* head = nullptr;
	Node* tail = nullptr;
};

template <typename Type>
List<Type>::List() : head(nullptr), tail(nullptr) {}

template <typename Type>
List<Type>::List(const List<Type>& list) {
	if (list.GetHead() != nullptr) {
		head = new Node(list.GetHead()->value, nullptr);
		Node* prev_node = head;
		for (auto i = list.GetHead(); i != nullptr; i = i->next) {
			if (i == list.GetHead())
				continue;
			prev_node->next = new Node(i->value, nullptr);
			prev_node = prev_node->next;
		}
		tail = prev_node;
	}
}

template <typename Type>
List<Type>::~List() {
	_clear();
}

template <typename Type>
void List<Type>::_clear() {
	while (head) {
		PopFront();
	}
}

template <typename Type>
List<Type>& List<Type>::operator=(const List& right) {
	if (this == &right)
		return *this;
	_clear();
	if (right.GetHead() != nullptr)
		for (auto i = right.GetHead(); i != nullptr; i = i->next)
			PushBack(i->value);
	return *this;
}

template <typename Type>
void List<Type>::PushFront(const Type& value) {
	if (head == nullptr) {
		head = new Node(value, nullptr);
		tail = head;
	}
	head = new Node(value, head);
}

template <typename Type>
void List<Type>::PushBack(const Type& value) {
	if (head == nullptr) {
		head = new Node(value, nullptr);
		tail = head;
	}
	else {
		tail->next = new Node(value, nullptr);
		tail = tail->next;
	}
}

template <typename Type>
void List<Type>::InsertAfter(Node* node, const Type& value) {
	node->next = new Node(value, node->next);
	if (node == tail)
		tail = node->next;
}

template <typename Type>
void List<Type>::RemoveAfter(Node* node) {
	Node* to_remove = node->next;
	if (tail == to_remove) {
		tail = node;
	}
	node->next = to_remove->next;
	delete to_remove;
}

template <typename Type>
void List<Type>::PopFront() {
	Node* to_remove = head;
	head = head->next;
	delete to_remove;
}