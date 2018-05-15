QT += core
QT -= gui
QT +=widgets
TARGET = untitled6
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    catalogwatcher.cpp
CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14
INCLUDEPATH += C:/Boost1_6_4/boost_1_64_0/boost_mingw_530/include/boost-1_64
LIBS += -LC:/Boost1_6_4/boost_1_64_0/boost_mingw_530/lib -llibboost_system-mgw49-mt-1_64 -llibboost_filesystem-mgw49-mt-1_64 -lws2_32

HEADERS += \
    catalogwatcher.h

