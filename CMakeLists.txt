project(vm)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(QT_USE_IMPORTED_TARGETS  TRUE)
find_package(Qt4 4.8 REQUIRED QtCore QtGui)
include(${QT_USE_FILE})
add_executable(vm main.cxx)
target_link_libraries(vm ${QT_LIBRARIES})

