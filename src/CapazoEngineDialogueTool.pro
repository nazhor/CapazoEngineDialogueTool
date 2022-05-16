QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomWidgets/ChatmapperExport.cpp \
    CustomWidgets/CustomField.cpp \
    CustomWidgets/ResultDialog.cpp \
    Data/Actor.cpp \
    Data/Conversation.cpp \
    Data/Json.cpp \
    Data/Node.cpp \
    Data/Validation.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    CustomWidgets/ChatmapperExport.h \
    CustomWidgets/CustomField.h \
    CustomWidgets/ResultDialog.h \
    Data/Actor.h \
    Data/Conversation.h \
    Data/Json.h \
    Data/Node.h \
    Data/Validation.h \
    MainWindow.h

FORMS += \
    CustomWidgets/ChatmapperExport.ui \
    CustomWidgets/CustomField.ui \
    CustomWidgets/ResultDialog.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res/resources.qrc

DISTFILES +=

VERSION = 2.0.0
QMAKE_TARGET_COMPANY = "The Brodevhood"
QMAKE_TARGET_PRODUCT = "Capazo Dialogue Tool"
QMAKE_TARGET_DESCRIPTION = "Capazo Dialogue Tool"
QMAKE_TARGET_COPYRIGHT = "The Brodevhood 2022"
win32:RC_ICONS += ../res/images/icon.ico
