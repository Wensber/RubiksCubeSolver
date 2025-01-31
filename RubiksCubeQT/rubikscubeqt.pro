QT += widgets opengl openglwidgets

HEADERS     = helper.h \
              widget.h \
              window.h
SOURCES     = helper.cpp \
              main.cpp \
              widget.cpp \
              window.cpp

# install
target.path = rubikscubeqt
INSTALLS += target
