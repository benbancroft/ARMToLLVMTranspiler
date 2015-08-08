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
    arminstructions/branchinstruction.cpp \
    arminstructions/armutils.cpp \
    basicblock.cpp \
    elfutils.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    elf.h \
    arminstructions/arminstruction.h \
    arminstructions/dataprocessinginstruction.h \
    arminstructions/singledatatransferinstruction.h \
    arminstructions/blockdatatransferinstruction.h \
    arminstructions/branchinstruction.h \
    arminstructions/armutils.h \
    basicblock.h \
    elfheader.h \
    elfutils.h \
    utils.h
