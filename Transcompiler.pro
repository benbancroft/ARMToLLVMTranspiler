TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    elf.cpp \
    arminstructions/arminstruction.cpp \
    arminstructions/dataprocessinginstruction.cpp \
    arminstructions/singledatatransferinstruction.cpp \
    arminstructions/blockdatatransferinstruction.cpp \
    arminstructions/armutils.cpp \
    utils.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    elf.h \
    arminstructions/arminstruction.h \
    arminstructions/dataprocessinginstruction.h \
    arminstructions/singledatatransferinstruction.h \
    arminstructions/blockdatatransferinstruction.h \
    utils.h \
    arminstructions/armutils.h
