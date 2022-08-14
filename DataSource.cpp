#include "DataSource.h"
#include "StorageUtils.h"

#include <stdexcept>

using namespace std;

DataSource* DataSource::instance = NULL;

DataSource* DataSource::getInstance() {
	if (instance == NULL)
		instance = new DataSource;
	return instance;
}

int DataSource::getIndexById(int id) {
	for (int i = 0; i < departments.size(); i++) {
		if (departments[i].getId() == id)
			return i;
	}

	throw runtime_error("Can not find department with given id");
}

bool DataSource::existById(int id) {
	try {
		getIndexById(id);
		return true;
	}
	catch (runtime_error& e) {
		return false;
	}
}

void DataSource::setStorageFilePath(const string& fileName) {
	storageFileName = fileName;
}

void DataSource::loadFromFile() {
	departments = StorageUtils::readRecordFromFile(storageFileName);
}

void DataSource::saveToFile() {
	StorageUtils::saveRecordToFile(storageFileName, departments);
}

void DataSource::addDepartment(const Department& department) {
	if (existById(department.getId())) {
		throw invalid_argument("Can not add a department with an existing id");
	}
	departments.push_back(department);
}

void DataSource::deleteDepartment(int id) {
	int index = getIndexById(id);

	vector<Department> backup = departments;
	departments = vector<Department>();
	for (int i = 0; i < backup.size(); i++) {
		if (i != index)
			departments.push_back(backup[i]);
	}
}

void DataSource::updateDepartment(const Department& department) {
	int index = getIndexById(department.getId());
	departments[index] = department;
}

Department DataSource::getDepartment(int id) {
	int index = getIndexById(id);
	return departments[index];
}

vector<Department> DataSource::getAllDepartments(){
    return departments;
}
