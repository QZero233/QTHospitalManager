#include "DepartmentDao.h"

int DepartmentDao::getIndexById(int id) throw(runtime_error) {
    for (int i = 0; i < departmentsPtr->size(); i++) {
        if (departmentsPtr->at(i).getId() == id)
            return i;
    }

    throw runtime_error("不能找到ID为"+to_string(id)+"的门诊部门");
}

bool DepartmentDao::existById(int id) {
    try {
        getIndexById(id);
        return true;
    }
    catch (runtime_error& e) {
        return false;
    }
}

void DepartmentDao::addDepartment(const Department& department) throw(invalid_argument) {
    if (existById(department.getId())) {
        throw invalid_argument("ID为"+to_string(department.getId())+"的门诊部门已存在，无法添加");
    }

    departmentsPtr->push_back(department);
}

void DepartmentDao::deleteDepartment(int id) {
    int index = getIndexById(id);

    vector<Department> backup = *departmentsPtr;
    *departmentsPtr = vector<Department>();
    for (int i = 0; i < backup.size(); i++) {
        if (i != index)
            departmentsPtr->push_back(backup[i]);
    }
}

void DepartmentDao::updateDepartment(const Department& department) {
    int index = getIndexById(department.getId());
    (*departmentsPtr)[index]=department;
}

Department DepartmentDao::getDepartment(int id) {
    int index = getIndexById(id);
    return departmentsPtr->at(index);
}

vector<Department> DepartmentDao::getAllDepartments(){
    return *departmentsPtr;
}
