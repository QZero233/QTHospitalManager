#include "DepartmentService.h"
#include "StorageUtils.h"

#include <stdexcept>

using namespace std;

DepartmentService::DepartmentService() {
	dataSourcePtr = DataSource::getInstance();
}

void DepartmentService::addDepartment(const Department& department) {
	dataSourcePtr->addDepartment(department);
}

void DepartmentService::deleteDepartment(int id) {
    //Check if there is appointments left and then delete
	dataSourcePtr->deleteDepartment(id);
}

void DepartmentService::updateDepartment(const Department& department) {
    //TODO when capacity changed, check if appointment number exceeds, and reject update if necessary
    //TODO when time changed, check if it's still available for all existing appointments
	dataSourcePtr->updateDepartment(department);
}

Department DepartmentService::getDepartment(int id) {
	return dataSourcePtr->getDepartment(id);
}

vector<Department> DepartmentService::getAllDepartments(){
    return dataSourcePtr->getAllDepartments();
}

