#include "DepartmentService.h"
#include "StorageUtils.h"

#include <QDateTime>
#include <stdexcept>

using namespace std;

DepartmentService::DepartmentService() {
	dataSourcePtr = DataSource::getInstance();
}

void DepartmentService::addDepartment(const Department& department) {
	dataSourcePtr->addDepartment(department);
}

void DepartmentService::deleteDepartment(int id) {
    Department department=dataSourcePtr->getDepartment(id);
    if(department.getAppointments().size()!=0){
        throw runtime_error("此门诊部门还有未处理的预约，无法删除");
    }
	dataSourcePtr->deleteDepartment(id);
}

void DepartmentService::updateDepartment(const Department& department) {
    if(department.getCapacity()<department.getAppointments().size()){
        throw runtime_error("修改后的容量无法容纳现有的预约数量");
    }

    //Check if all appointment satisfy changed time
    vector<Appointment> appointments=department.getAppointments();
    for(Appointment appointment:appointments){
        long time=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).time().msecsSinceStartOfDay();
        if(time<department.getAppointmentStartTime() || time>department.getAppointmentEndTime()){
            throw runtime_error("存在不满足新的时间规定的预约信息，其ID为"+to_string(appointment.getId()));
        }
    }

	dataSourcePtr->updateDepartment(department);
}

Department DepartmentService::getDepartment(int id) {
	return dataSourcePtr->getDepartment(id);
}

vector<Department> DepartmentService::getAllDepartments(){
    return dataSourcePtr->getAllDepartments();
}

