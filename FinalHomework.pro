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
    AddUserDialog.cpp \
    AppointmentDao.cpp \
    AppointmentEditDelegate.cpp \
    AppointmentModel.cpp \
    AppointmentService.cpp \
    DataSource.cpp \
    DepartmentDao.cpp \
    DepartmentDelegate.cpp \
    DepartmentModel.cpp \
    DepartmentService.cpp \
    DoctorDao.cpp \
    DoctorDelegate.cpp \
    DoctorModel.cpp \
    DoctorService.cpp \
    DoctorStatisticDialog.cpp \
    DoctorStatisticModel.cpp \
    DutyDao.cpp \
    DutyDelegate.cpp \
    DutyModel.cpp \
    DutyService.cpp \
    LoginWindow.cpp \
    ReadOnlyDelegate.cpp \
    RegistrationWindow.cpp \
    SelectDateDialog.cpp \
    SelectDutyDialog.cpp \
    ShowAppointmentsDialog.cpp \
    ShowDepartmentDutiesDialog.cpp \
    ShowTimeDutyDialog.cpp \
    StatisticDelegate.cpp \
    StatisticModel.cpp \
    TableDutyModel.cpp \
    TimeDutyDelegate.cpp \
    TimeDutyModel.cpp \
    TimeUtils.cpp \
    User.cpp \
    UserDao.cpp \
    UserDelegate.cpp \
    UserModel.cpp \
    UserService.cpp \
    departmenteditdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddAppointmentDialog.h \
    AddDoctorDialog.h \
    AddDutyDialog.h \
    AddUserDialog.h \
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
    DoctorStatisticDialog.h \
    DoctorStatisticModel.h \
    Duty.h \
    DutyDao.h \
    DutyDelegate.h \
    DutyModel.h \
    DutyService.h \
    LoginWindow.h \
    ReadOnlyDelegate.h \
    RegistrationWindow.h \
    SelectDateDialog.h \
    SelectDutyDialog.h \
    ShowAppointmentsDialog.h \
    ShowDepartmentDutiesDialog.h \
    ShowTimeDutyDialog.h \
    StatisticDelegate.h \
    StatisticModel.h \
    TableDutyModel.h \
    TimeDutyDelegate.h \
    TimeDutyModel.h \
    TimeUtils.h \
    User.h \
    UserDao.h \
    UserDelegate.h \
    UserModel.h \
    UserService.h \
    departmenteditdialog.h \
    mainwindow.h

FORMS += \
    AddAppointmentDialog.ui \
    AddDoctorDialog.ui \
    AddDutyDialog.ui \
    AddUserDialog.ui \
    DoctorStatisticDialog.ui \
    LoginWindow.ui \
    RegistrationWindow.ui \
    SelectDateDialog.ui \
    SelectDutyDialog.ui \
    ShowAppointmentsDialog.ui \
    ShowDepartmentDutiesDialog.ui \
    ShowTimeDutyDialog.ui \
    departmenteditdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icons.qrc
