#pragma once
#include <string>

struct Person {
	std::string m_name;
	int m_age;

	Person(std::string name, int age): m_name(name), m_age(age) {}
	~Person() = default;
};