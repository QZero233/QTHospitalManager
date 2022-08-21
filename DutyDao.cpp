#include "DutyDao.h"

int DutyDao::getIndexById(int id) throw(runtime_error) {
    for (int i = 0; i < dutiesPtr->size(); i++) {
        if (dutiesPtr->at(i).getId() == id)
            return i;
    }

    throw runtime_error("不能找到ID为"+to_string(id)+"的值班记录");
}

bool DutyDao::existById(int id) {
    try {
        getIndexById(id);
        return true;
    }
    catch (runtime_error& e) {
        return false;
    }
}

void DutyDao::addDuty(const Duty& duty) throw(invalid_argument) {
    if (existById(duty.getId())) {
        throw invalid_argument("ID为"+to_string(duty.getId())+"的值班记录已存在，无法添加");
    }

    dutiesPtr->push_back(duty);
}

void DutyDao::deleteDuty(int id) {
    int index = getIndexById(id);

    vector<Duty> backup = *dutiesPtr;
    *dutiesPtr = vector<Duty>();
    for (int i = 0; i < backup.size(); i++) {
        if (i != index)
            dutiesPtr->push_back(backup[i]);
    }
}

void DutyDao::updateDuty(const Duty& duty) {
    int index = getIndexById(duty.getId());
    (*dutiesPtr)[index]=duty;
}

Duty DutyDao::getDuty(int id) {
    int index = getIndexById(id);
    return dutiesPtr->at(index);
}

vector<Duty> DutyDao::getAllDuties(){
    return *dutiesPtr;
}

