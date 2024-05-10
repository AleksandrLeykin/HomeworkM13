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
	// чистим память
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
	// если дерево пустое, то новый персонаж станет корнем
	if (root == nullptr)
		root = new Node(newperson);
	else {
		Node* current = root;
		Node* newNode = nullptr;
		//цикл пока найдем место для нового персонажa
		while (newNode == nullptr) {
			//если текущий персонаж старше
			if (current->m_person.m_age >= newperson.m_age) {
				if (current->left != nullptr) {
					current = current->left;
					continue;
				}
				//нашли место записываем его и родителя
				newNode = new Node(newperson, current);
				//указать текущему , что его новый left равен newNode
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
		std::cout << "Чат пуст" << std::endl;
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
		std::cout << "Нет такого персонажа" << findPerson.m_name << std::endl;
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
		// обнуляем указатель на удаляемый узел у родителя
		setNewChild(leaf);
	}
	// удаляем листовой узел
	delete leaf;
}

void TreeChat::delNodeWithOneChild(Node* delNode)
{
	if (delNode->left != nullptr) {
		// если имеет левый узел
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
		// если правый узел
		if (isRoot(delNode)) {
			root = delNode->right;
		}
		else {
			setNewChild(delNode, delNode->right);
		}
		delNode->right->parent = delNode->parent;
		delNode->right = nullptr;
	}
	//удаляем узел
	delete delNode;
}

void TreeChat::delPerson(Person delperson)
{
	if (root == nullptr) {
		std::cout << "Чат пуст" << std::endl;
		return;
	}
	Node* temp = findPersonByName(delperson);
	if (temp == nullptr)
		return;
	// если это лист, просто удалим его
	if (isLeaf(temp)) {
		delLeaf(temp);
	}
	else {
		// если не лист, то удаление сложнее
		if (temp->left == nullptr || temp->right == nullptr) {
			// случай, когда у узла только один дочерний
			delNodeWithOneChild(temp);
		}
		else {
			// ищем правый элемент левого поддерева
			Node* mostright = temp->left;
			while (mostright->right != nullptr) {
				mostright = mostright->right;
			}
			// записали данные из правого вместо данных в удаляемом узле  
			temp->m_person.m_age = mostright->m_person.m_age;
			temp->m_person.m_name = mostright->m_person.m_name;

			// удалили правый элемент (он может содержать только левый узел)
			if (mostright->left != nullptr)
				delNodeWithOneChild(mostright);
			else
				delLeaf(mostright);
		}
	}


	//Node* current = temp->parent;
	////если персонаж лист
	//if (temp->left == nullptr && temp->right == nullptr) {
	//	if (temp == root)
	//		root = nullptr;
	//	delete temp;
	//	return;
	//}	
	//else {//если есть 1 ребенок 
	//	if (temp->left == nullptr || temp->right == nullptr) {
	//		if (root == temp) {
	//			//есть правый ребенок
	//			if (temp->left == nullptr) {
	//				root = temp->right;
	//				root->parent = nullptr;
	//				temp->right = nullptr;
	//			}				
	//			else {//есть левый ребенок
	//				root = temp->left;
	//				root->parent = nullptr;
	//				temp->left = nullptr;
	//			}				
	//		}
	//	}
	//	////Если удаляемый узел является поддеревом
	//	//else {
	//	//	//есть правый ребенок
	//	//	if (temp->left == nullptr) {
	//	//		//Если удаляемый узел является правым поддеревом
	//	//		if (current->right == temp)
	//	//			current->right = temp->right;
	//	//		else
	//	//			current->left = temp->right;
	//	//		temp->right->parent = temp->parent;
	//	//		temp->right = nullptr;
	//	//	}
	//	//	//есть левый ребенок
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
	////Если узел имеет оба ребенка
	//Node* leftmax = temp->left;
	////находим крайний правый
	//while (leftmax->right != nullptr) {
	//	leftmax = leftmax->right;
	//}
	////меняем данные из  узлов и потом удаляем тот который нашли
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
	//массив очередь узлов
	Node* queue[100];
	//счетчик
	int queCounter = 0;
	//записываем корень
	queue[queCounter++] = root;

	while (queCounter != 0) {
		//тякущий узел
		Node* current = queue[0];
		//уменьшить счетчик
		queCounter--;
		//смещаем массив
		for (int i = 0; i < queCounter; i++)
		{
			queue[i] = queue[i + 1];
		}
		//если есть родитель его показываем
		if (current->parent)
			std::cout << current->parent->m_person.m_name;
		std::cout << " " << current->m_person.m_name << std::endl;
		if (current->left)
			queue[queCounter++] = current->left;
		if (current->right)
			queue[queCounter++] = current->right;
	}

}
