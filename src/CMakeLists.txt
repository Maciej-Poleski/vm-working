set(QT_USE_IMPORTED_TARGETS  TRUE)
find_package(Qt4 4.8 REQUIRED QtCore QtGui)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR} )

set(INPUT_SOURCES
    Processor.cxx
    MachineWidget.cxx
    ProcessorStateWidget.cxx
    DecoderStateWidget.cxx
    DecoderWidget.cxx
    Register.cxx
    Decoder.cxx
    Machine.cxx
    InstructionsProvider.cxx)

set(INPUT_HEADERS
    Processor.hxx
    MachineWidget.hxx
    ProcessorStateWidget.hxx
    DecoderStateWidget.hxx
    DecoderWidget.hxx
    Register.hxx
    Decoder.hxx
    Machine.hxx
    InstructionsProvider.hxx)

set(INPUT_UIS
    MachineWidget.ui
    ProcessorStateWidget.ui
    DecoderStateWidget.ui
    DecoderWidget.ui)

QT4_WRAP_CPP(OUTPUT_SOURCES ${INPUT_HEADERS})
QT4_WRAP_UI(OUTPUT_UIS ${INPUT_UIS})

add_library(vmCore ${INPUT_SOURCES} ${OUTPUT_SOURCES} ${OUTPUT_UIS})

add_executable(vm main.cxx)
target_link_libraries(vm ${QT_LIBRARIES} vmCore)

