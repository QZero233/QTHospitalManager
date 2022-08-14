#pragma once

#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include "Department.h"
#include <vector>

using namespace std;

class DataSource
{
private:
	vector<Department> departments;
	string storageFileName;

	static DataSource* instance;

	DataSource(){}
public:
	static DataSource* getInstance();

	int getIndexById(int id);
	bool existById(int id);

	void setStorageFilePath(const string& fileName);

	void loadFromFile();
	void saveToFile();

	void addDepartment(const Department& department);
	void deleteDepartment(int id);
	void updateDepartment(const Department& department);
	Department getDepartment(int id);

    vector<Department> getAllDepartments();
};



#endif
