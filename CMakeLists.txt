# set project's name
  PROJECT( koditor )
  
  cmake_minimum_required(VERSION 2.8)

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
  
  # with SET() command you can change variables or define new ones
  # here we define KODITOR_SRCS variable that contains a list of all .cpp files
  # note that we don't need \ at the end of line
  SET( KODITOR_SRCS
    main.cpp
    qonsole.cpp
    mainWindow.cpp
  )
  
  # another list, this time it includes all header files that should be treated with moc
  SET( KODITOR_MOC_HDRS
    qonsole.h
    mainWindow.h  
  )
  
    SET( KODITOR_RCS
        rc.qrc
  )
    SET( KODITOR_UIS
          mainWindow.ui
  )
  
  set(EXECUTABLE_OUTPUT_PATH ${KODITOR_SOURCE_DIR})
  
  # and finally an resource file
  
  # enable warnings
  ADD_DEFINITIONS( -Wall )
  
  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
  
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
  FIND_PACKAGE( Qt4 REQUIRED )
  FIND_PACKAGE( QScintilla REQUIRED)
  
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
  INCLUDE( ${QT_USE_FILE} )
  
  # this command will generate rules that will run rcc on all files from KODITOR_RCS
  # in result KODITOR_RC_SRCS variable will contain paths to files produced by rcc
  QT4_ADD_RESOURCES( KODITOR_RC_SRCS ${KODITOR_RCS} )
  
  # this will run uic on .ui files:
  QT4_WRAP_UI( KODITOR_UI_HDRS ${KODITOR_UIS} )
  
  # and finally this will run moc:
  QT4_WRAP_CPP( KODITOR_MOC_SRCS ${KODITOR_MOC_HDRS} )
  
  # we need this to be able to include headers produced by uic in our code
  # (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
  INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )
  
  # here we instruct CMake to build "koditor" executable from all of the source files
  ADD_EXECUTABLE( koditor ${KODITOR_SRCS} ${KODITOR_MOC_SRCS} ${KODITOR_RC_SRCS} ${KODITOR_UI_HDRS} )
  
  # last thing we have to do is to tell CMake what libraries our executable needs,
  # luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
  TARGET_LINK_LIBRARIES( koditor ${QT_LIBRARIES}  ${QSCINTILLA_LIBRARIES})
  
  install(
    TARGETS
        koditor
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)

