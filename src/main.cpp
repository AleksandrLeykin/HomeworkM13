#include <iostream>
#include "TreeChat.h"

int main()
{
	setlocale(LC_ALL, "ru");
	std::cout << "Привет!" << std::endl;

	Person sasha("Sasha", 53);
	Person ira("Irina", 55);
	Person genia("Evgeniy", 26);
	Person karina("Karina", 31);
	Person liza("Elizaveta", 16);
	Person egor("Egor", 28);

	TreeChat chat;
	chat.addPerson(sasha);
	chat.addPerson(ira);
	chat.addPerson(genia);
	chat.addPerson(karina);
	chat.addPerson(liza);
	chat.addPerson(egor);

	chat.print();

	chat.delPerson(sasha);
	std::cout << std::endl;
	chat.print();

	return 0;
}