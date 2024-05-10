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

	//���������� ������(adding new)
	void addPerson(Person newperson);
	//����� �����(find Person)
	Node* findPersonByName(Person findPerson);

	//����������� ���� ����? check - ���������
	bool isLeaf(Node* check) { return check->left == nullptr && check->right == nullptr; }
	// ��������, ������� �� ���� ��������
	bool isRoot(Node* check) { return check == root; }
	// ��������� ��� �������� ���� child ������ ���������
	// ���� newChild ������ child (��� ����������� �������� ����)
	void setNewChild(Node* child, Node* newChild = nullptr);
	//�������� �����
	void delLeaf(Node* leaf);
	//������� ���� � ����� �������� ����� �� ������
	void delNodeWithOneChild(Node* delNode);
	//��������(delete)
	void delPerson(Person delperson);
	
	void print();
private:
	Node* root;
};