TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    eco/eco.cpp \
    eco/feature_extractor.cpp \
    eco/feature_operator.cpp \
    eco/ffttools.cpp \
    eco/fhog.cpp \
    eco/gradient.cpp \
    eco/interpolator.cpp \
    eco/optimize_scores.cpp \
    eco/regularization_filter.cpp \
    eco/sample_update.cpp \
    eco/training.cpp \
    eco/wrappers.cpp

HEADERS += \
    eco/eco.h \
    eco/feature_extractor.h \
    eco/feature_operator.h \
    eco/ffttools.h \
    eco/fhog.h \
    eco/gradient.hpp \
    eco/interpolator.h \
    eco/optimize_scores.h \
    eco/recttools.h \
    eco/regularization_filter.h \
    eco/sample_update.h \
    eco/sse.hpp \
    eco/training.h \
    eco/parameters.h \
    eco/wrappers.hpp


INCLUDEPATH += /usr/local/include/opencv4 \
               `pkg-config --cflags opencv`
LIBS += `pkg-config --libs opencv` \
        -lpthread \
        -lfftw3   \
        -ltbb

