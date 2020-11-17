file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

message(${SRC_FILES})

# list(APPEND SRCS ${LAYER_ARCH_SRC})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -fPIC -std=c++11 -fopenmp")
add_library(VisionEngine STATIC ${SRC_FILES})

find_package(OpenCV)
message("Opencv Version: ${OPENCV_VERSION}" )
include_directories(${CMAKE_SOURCE_DIR}/ncnn/include)
link_directories(${CMAKE_SOURCE_DIR}/ncnn/lib)
target_link_libraries(VisionEngine PUBLIC ${OpenCV_LIBS} ncnn)

if(MIRROR_OPENMP)
    find_package(OpenMP)
    if(NOT TARGET OpenMP::OpenMP_CXX AND (OpenMP_CXX_FOUND OR OPENMP_FOUND))
        target_compile_options(VisionEngine PRIVATE ${OpenMP_CXX_FLAGS})
    endif()
endif()

if(MIRROR_OPENMP AND OpenMP_CXX_FOUND)
    message("Building with OpenMP")
    target_link_libraries(VisionEngine PUBLIC OpenMP::OpenMP_CXX)
endif()

#
target_include_directories(VisionEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include/vision>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common>

        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/face>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/face/common>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/face/detecter>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/face/detecter/anticonv>
)

if(MIRROR_INSTALL_SDK)
    install(TARGETS VisionEngine EXPORT VisionEngine ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib)
    install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/common/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/face/face_engine.h
        DESTINATION ${PROJECT_BINARY_DIR}/include
    )
endif()

if(MIRROR_BUILD_FACE)
    add_executable(face ${CMAKE_SOURCE_DIR}/examples/test_face.cpp)
    target_link_libraries(face PUBLIC VisionEngine)
endif()
