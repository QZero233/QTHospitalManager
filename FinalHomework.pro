QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddAppointmentDialog.cpp \
    AddDoctorDialog.cpp \
    AddDutyDialog.cpp \
    AppointmentDao.cpp \
    AppointmentEditDelegate.cpp \
    AppointmentModel.cpp \
    AppointmentService.cpp \
    DataSource.cpp \
    DepartmentDao.cpp \
    DepartmentDelegate.cpp \
    DepartmentModel.cpp \
    DepartmentService.cpp \
    Doctor.cpp \
    DoctorDao.cpp \
    DoctorDelegate.cpp \
    DoctorModel.cpp \
    DoctorService.cpp \
    Duty.cpp \
    DutyDao.cpp \
    DutyDelegate.cpp \
    DutyModel.cpp \
    DutyService.cpp \
    InputPasswordDialog.cpp \
    InputTelDialog.cpp \
    QueryAppointmentDialog.cpp \
    ReadOnlyDelegate.cpp \
    RegistrationWindow.cpp \
    SelectDutyDialog.cpp \
    ShowAppointmentsDialog.cpp \
    ShowDepartmentDutiesDialog.cpp \
    TimeUtils.cpp \
    departmenteditdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddAppointmentDialog.h \
    AddDoctorDialog.h \
    AddDutyDialog.h \
    Appointment.h \
    AppointmentDao.h \
    AppointmentEditDelegate.h \
    AppointmentModel.h \
    AppointmentService.h \
    DataSource.h \
    Department.h \
    DepartmentDao.h \
    DepartmentDelegate.h \
    DepartmentModel.h \
    DepartmentService.h \
    Doctor.h \
    DoctorDao.h \
    DoctorDelegate.h \
    DoctorModel.h \
    DoctorService.h \
    Duty.h \
    DutyDao.h \
    DutyDelegate.h \
    DutyModel.h \
    DutyService.h \
    InputPasswordDialog.h \
    InputTelDialog.h \
    QueryAppointmentDialog.h \
    ReadOnlyDelegate.h \
    RegistrationWindow.h \
    SelectDutyDialog.h \
    ShowAppointmentsDialog.h \
    ShowDepartmentDutiesDialog.h \
    TimeUtils.h \
    departmenteditdialog.h \
    mainwindow.h

FORMS += \
    AddAppointmentDialog.ui \
    AddDoctorDialog.ui \
    AddDutyDialog.ui \
    InputPasswordDialog.ui \
    InputTelDialog.ui \
    QueryAppointmentDialog.ui \
    RegistrationWindow.ui \
    SelectDutyDialog.ui \
    ShowAppointmentsDialog.ui \
    ShowDepartmentDutiesDialog.ui \
    departmenteditdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icons.qrc
