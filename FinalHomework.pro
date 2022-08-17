QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddAppointmentDialog.cpp \
    AppointmentDao.cpp \
    AppointmentEditDelegate.cpp \
    AppointmentModel.cpp \
    AppointmentService.cpp \
    DataSource.cpp \
    DepartmentDao.cpp \
    DepartmentModel.cpp \
    DepartmentService.cpp \
    ReadOnlyDelegate.cpp \
    ShowAppointmentsDialog.cpp \
    TimeUtils.cpp \
    departmenteditdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddAppointmentDialog.h \
    Appointment.h \
    AppointmentDao.h \
    AppointmentEditDelegate.h \
    AppointmentModel.h \
    AppointmentService.h \
    DataSource.h \
    Department.h \
    DepartmentDao.h \
    DepartmentModel.h \
    DepartmentService.h \
    ReadOnlyDelegate.h \
    ShowAppointmentsDialog.h \
    StorageUtils.h \
    TimeUtils.h \
    departmenteditdialog.h \
    mainwindow.h

FORMS += \
    AddAppointmentDialog.ui \
    ShowAppointmentsDialog.ui \
    departmenteditdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
