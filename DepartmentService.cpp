#include "DepartmentService.h"
#include "StorageUtils.h"

#include <QDateTime>
#include <stdexcept>

using namespace std;

DepartmentService::DepartmentService() {

}

void DepartmentService::checkDepartmentData(const Department& department) throw(invalid_argument){
    //Check appointment time
    if(department.getAppointmentStartTime()<0 || department.getAppointmentEndTime()<0)
        throw invalid_argument("时间必须大于0");

    if(department.getAppointmentEndTime()-department.getAppointmentStartTime()<=0)
        throw invalid_argument("结束时间不能早于开始时间");

    //Check capacity
    if(department.getCapacity()<=0)
        throw invalid_argument("容量必须为正数");

    int currentAppointmentCount=appointmentDao.getCountByDepartmentId(department.getId());
    if (currentAppointmentCount > department.getCapacity()) {
        throw invalid_argument("预约数量超出容量");
    }
}

void DepartmentService::addDepartment(const Department& department) throw(invalid_argument) {
    checkDepartmentData(department);
    dao.addDepartment(department);
}

void DepartmentService::deleteDepartment(int id) throw(runtime_error) {
    int currentAppointmentCount=appointmentDao.getCountByDepartmentId(id);
    if(currentAppointmentCount!=0){
        throw runtime_error("此门诊部门还有未处理的预约，无法删除");
    }
    dao.deleteDepartment(id);
}

void DepartmentService::updateDepartment(const Department& department) throw(invalid_argument,runtime_error){
    checkDepartmentData(department);
    //Check if all appointment satisfy changed time
    vector<Appointment> appointments=appointmentDao.getAllByDepartmentId(department.getId());
    for(Appointment appointment:appointments){
        long time=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).time().msecsSinceStartOfDay();
        if(time<department.getAppointmentStartTime() || time>department.getAppointmentEndTime()){
            throw runtime_error("存在不满足新的时间规定的预约信息，其ID为"+to_string(appointment.getId()));
        }
    }

    dao.updateDepartment(department);
}

Department DepartmentService::getDepartment(int id) {
    return dao.getDepartment(id);
}

vector<Department> DepartmentService::getAllDepartments(){
    return dao.getAllDepartments();
}

int DepartmentService::getAppointmentCountById(int departmentId){
    return appointmentDao.getCountByDepartmentId(departmentId);
}

