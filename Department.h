#pragma once
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <stdexcept>
#include <vector>

#include "Appointment.h"

using namespace std;

class Department{
private:
	int id;
	string name;
	string address;
	string telephone;

public:
	Department() :
    id(-1),name(""),address(""),telephone("") {

	}

    Department(int id,const string& name, string address, string telephone):
    id(id),
    name(name),
    address(address),
    telephone(telephone){}

	void setId(int id) {
		this->id = id;
	}

	int getId() const{
		return id;
	}

	void setName(const string& name) {
		this->name = name;
	}

	string getName() const {
		return name;
	}

	void setAddress(const string& address) {
		this->address = address;
	}

	string getAddress() const {
		return address;
	}

	void setTelephone(const string& tel) {
		telephone = tel;
	}

	string getTelephone() const {
		return telephone;
	}
};

#endif

