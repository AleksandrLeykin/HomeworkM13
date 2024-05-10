#pragma once
#include "Person.h"

class TreeChat
{
public:
	struct Node {
		
		Node(Person person, Node* p = nullptr);
		~Node();

		Node* parent;
		Node* left;
		Node* right;

		Person m_person;
	};

	TreeChat();
	~TreeChat();

	//добавления нового(adding new)
	void addPerson(Person newperson);
	//поиск героя(find Person)
	Node* findPersonByName(Person findPerson);

	//определение узел лисе? check - проверять
	bool isLeaf(Node* check) { return check->left == nullptr && check->right == nullptr; }
	// проверка, являтся ли узел корневым
	bool isRoot(Node* check) { return check == root; }
	// установка для родителя узла child нового дочернего
	// узла newChild вместо child (для дальнейшего удаления узла)
	void setNewChild(Node* child, Node* newChild = nullptr);
	//удаление листа
	void delLeaf(Node* leaf);
	//удалить узел с одним дочерним узлом из дерева
	void delNodeWithOneChild(Node* delNode);
	//удаление(delete)
	void delPerson(Person delperson);
	
	void print();
private:
	Node* root;
};