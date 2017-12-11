cmake_minimum_required(VERSION 2.8.12)

PROJECT(Prashant2)

set(OpenCV_DIR /usr/local/share/OpenCV/)

find_package( OpenCV REQUIRED)

ADD_EXECUTABLE(tracking tracking.cpp)
TARGET_LINK_LIBRARIES(tracking ${OpenCV_LIBS})
