TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        SimulatedAnnealing.cpp \
        TSPFileReader.cpp \
        main.cpp

HEADERS += \
    SimulatedAnnealing.h \
    TSPFileReader.h
