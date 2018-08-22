CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


PROJECT(OpenFLUIDjs)


FIND_PACKAGE(OpenFLUIDHelpers REQUIRED)

IF(COMMAND OPENFLUID_DETECT_CXX11)
  OPENFLUID_DETECT_CXX11()
ENDIF()

FIND_PACKAGE(Qt5 COMPONENTS Core REQUIRED)
FIND_PACKAGE(OpenFLUID REQUIRED core base ware machine tools fluidx)


INCLUDE_DIRECTORIES(${OpenFLUID_INCLUDE_DIRS} ${CMAKE_JS_INC}
                                              ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api
                                              ${CMAKE_SOURCE_DIR}/../node-addon-api
                   )

SET(OpenFLUIDjs_CPP_HPP src/OpenFLUIDjsWrapper.cpp)

ADD_LIBRARY(OpenFLUIDjs SHARED ${OpenFLUIDjs_CPP_HPP})

SET_TARGET_PROPERTIES(OpenFLUIDjs PROPERTIES PREFIX "lib" SUFFIX ".node")

TARGET_LINK_LIBRARIES(OpenFLUIDjs ${OpenFLUID_LIBRARIES}
                                  Qt5::Core
                                  ${CMAKE_JS_LIB}
                     )
