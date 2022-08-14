QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Appointment.cpp \
    AppointmentEditDelegate.cpp \
    AppointmentService.cpp \
    DataSource.cpp \
    Department.cpp \
    DepartmentService.cpp \
    ReadOnlyDelegate.cpp \
    ShowAppointmentsDialog.cpp \
    StorageUtils.cpp \
    TimeUtils.cpp \
    departmenteditdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Appointment.h \
    AppointmentEditDelegate.h \
    AppointmentService.h \
    DataSource.h \
    Department.h \
    DepartmentService.h \
    ReadOnlyDelegate.h \
    ShowAppointmentsDialog.h \
    StorageUtils.h \
    TimeUtils.h \
    departmenteditdialog.h \
    mainwindow.h

FORMS += \
    ShowAppointmentsDialog.ui \
    departmenteditdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
