QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/controller/fakecontroller.cpp \
        src/controller/restshopcontroller.cpp \
        src/main.cpp \
        src/model/product.cpp \
        src/view/productview.cpp \
        src/view/shoppingcartview.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/controller/fakecontroller.hpp \
    src/controller/ishopcontroller.hpp \
    src/controller/restshopcontroller.hpp \
    src/model/product.hpp \
    src/view/productview.hpp \
    src/view/shoppingcartview.hpp

INCLUDEPATH += src
