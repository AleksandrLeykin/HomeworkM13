#include "TreeChat.h"
#include <iostream>

TreeChat::Node::Node(Person person, Node* p) :
	m_person(person)
	,parent(p)
	,left(nullptr)
	,right(nullptr)
{}

TreeChat::Node::~Node()
{
	// ������ ������
	if (left != nullptr) delete left;
	if (right != nullptr) delete right;
}

TreeChat::TreeChat()
{
	root = nullptr;
}

TreeChat::~TreeChat()
{
	if (root != nullptr)
		delete root;
}

void TreeChat::addPerson(Person newperson)
{
	// ���� ������ ������, �� ����� �������� ������ ������
	if (root == nullptr)
		root = new Node(newperson);
	else {
		Node* current = root;
		Node* newNode = nullptr;
		//���� ���� ������ ����� ��� ������ ��������a
		while (newNode == nullptr) {
			//���� ������� �������� ������
			if (current->m_person.m_age >= newperson.m_age) {
				if (current->left != nullptr) {
					current = current->left;
					continue;
				}
				//����� ����� ���������� ��� � ��������
				newNode = new Node(newperson, current);
				//������� �������� , ��� ��� ����� left ����� newNode
				current->left = newNode;
			}
			else {
				if (current->right != nullptr) {
					current = current->right;
					continue;

				}
				newNode = new Node(newperson, current);
				current->right = newNode;
			}
		}
	}
}

TreeChat::Node* TreeChat::findPersonByName(Person findPerson)
{
	if (root == nullptr) {
		std::cout << "��� ����" << std::endl;
		return nullptr;
	}
	else {
		Node* current = root;
		while (current != nullptr) {
			if (current->m_person.m_name == findPerson.m_name && current->m_person.m_age == findPerson.m_age) {
				return current;
			}
			if (current->m_person.m_age > findPerson.m_age) {
				current = current->left;
				continue;
			}
			else {
				current = current->right;
				continue;
			}
		}
		std::cout << "��� ������ ���������" << findPerson.m_name << std::endl;
		return nullptr;
	}
}



void TreeChat::setNewChild(Node* child, Node* newChild)
{
	Node* parent = child->parent;
	if (parent != nullptr) {
		if (parent->left == child)
			parent->left = newChild;
		else
			parent->right = newChild;
	}
}

void TreeChat::delLeaf(Node* leaf)
{
	if (isRoot(leaf))
		root == nullptr;
	else {
		// �������� ��������� �� ��������� ���� � ��������
		setNewChild(leaf);
	}
	// ������� �������� ����
	delete leaf;
}

void TreeChat::delNodeWithOneChild(Node* delNode)
{
	if (delNode->left != nullptr) {
		// ���� ����� ����� ����
		if (isRoot(delNode)) {
			root = delNode->left;
		}
		else {
			setNewChild(delNode, delNode->left);
		}
		delNode->left->parent = delNode->parent;
		delNode->left = nullptr;
	}
	else {
		// ���� ������ ����
		if (isRoot(delNode)) {
			root = delNode->right;
		}
		else {
			setNewChild(delNode, delNode->right);
		}
		delNode->right->parent = delNode->parent;
		delNode->right = nullptr;
	}
	//������� ����
	delete delNode;
}

void TreeChat::delPerson(Person delperson)
{
	if (root == nullptr) {
		std::cout << "��� ����" << std::endl;
		return;
	}
	Node* temp = findPersonByName(delperson);
	if (temp == nullptr)
		return;
	// ���� ��� ����, ������ ������ ���
	if (isLeaf(temp)) {
		delLeaf(temp);
	}
	else {
		// ���� �� ����, �� �������� �������
		if (temp->left == nullptr || temp->right == nullptr) {
			// ������, ����� � ���� ������ ���� ��������
			delNodeWithOneChild(temp);
		}
		else {
			// ���� ������ ������� ������ ���������
			Node* mostright = temp->left;
			while (mostright->right != nullptr) {
				mostright = mostright->right;
			}
			// �������� ������ �� ������� ������ ������ � ��������� ����  
			temp->m_person.m_age = mostright->m_person.m_age;
			temp->m_person.m_name = mostright->m_person.m_name;

			// ������� ������ ������� (�� ����� ��������� ������ ����� ����)
			if (mostright->left != nullptr)
				delNodeWithOneChild(mostright);
			else
				delLeaf(mostright);
		}
	}


	//Node* current = temp->parent;
	////���� �������� ����
	//if (temp->left == nullptr && temp->right == nullptr) {
	//	if (temp == root)
	//		root = nullptr;
	//	delete temp;
	//	return;
	//}	
	//else {//���� ���� 1 ������� 
	//	if (temp->left == nullptr || temp->right == nullptr) {
	//		if (root == temp) {
	//			//���� ������ �������
	//			if (temp->left == nullptr) {
	//				root = temp->right;
	//				root->parent = nullptr;
	//				temp->right = nullptr;
	//			}				
	//			else {//���� ����� �������
	//				root = temp->left;
	//				root->parent = nullptr;
	//				temp->left = nullptr;
	//			}				
	//		}
	//	}
	//	////���� ��������� ���� �������� ����������
	//	//else {
	//	//	//���� ������ �������
	//	//	if (temp->left == nullptr) {
	//	//		//���� ��������� ���� �������� ������ ����������
	//	//		if (current->right == temp)
	//	//			current->right = temp->right;
	//	//		else
	//	//			current->left = temp->right;
	//	//		temp->right->parent = temp->parent;
	//	//		temp->right = nullptr;
	//	//	}
	//	//	//���� ����� �������
	//	//	else {
	//	//		if (current->right == temp)
	//	//			current->right = temp->left;
	//	//		else
	//	//			current->left = temp->left;
	//	//		temp->left->parent = temp->parent;
	//	//		temp->left = nullptr;
	//	//	}
	//	//}
	//	
	//	delete temp;
	//	return;
	//}
	////���� ���� ����� ��� �������
	//Node* leftmax = temp->left;
	////������� ������� ������
	//while (leftmax->right != nullptr) {
	//	leftmax = leftmax->right;
	//}
	////������ ������ ��  ����� � ����� ������� ��� ������� �����
	//temp->m_person.m_age = leftmax->m_person.m_age;
	//temp->m_person.m_name = leftmax->m_person.m_name;

	//if (leftmax->parent->left == leftmax)
	//	leftmax->parent->left = nullptr;
	//else
	//	leftmax->parent->right = nullptr;
	//delete leftmax;
}

void TreeChat::print()
{
	//������ ������� �����
	Node* queue[100];
	//�������
	int queCounter = 0;
	//���������� ������
	queue[queCounter++] = root;

	while (queCounter != 0) {
		//������� ����
		Node* current = queue[0];
		//��������� �������
		queCounter--;
		//������� ������
		for (int i = 0; i < queCounter; i++)
		{
			queue[i] = queue[i + 1];
		}
		//���� ���� �������� ��� ����������
		if (current->parent)
			std::cout << current->parent->m_person.m_name;
		std::cout << " " << current->m_person.m_name << std::endl;
		if (current->left)
			queue[queCounter++] = current->left;
		if (current->right)
			queue[queCounter++] = current->right;
	}

}
