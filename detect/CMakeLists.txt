cmake_minimum_required(VERSION 2.8)
project( FindBalls )
set(raspicam_DIR "/usr/local/lib/cmake")
find_package( raspicam REQUIRED )
find_package( OpenCV REQUIRED )
find_package( wiringPi REQUIRED )
include_directories(${WIRINGPI_INCLUDE_DIRS}) 
add_executable( balldetect balldetect.cpp )
target_link_libraries( balldetect ${OpenCV_LIBS} ${raspicam_CV_LIBS} ${WIRINGPI_LIBRARIES})
add_executable( FindBalls FindBalls.cpp )
target_link_libraries( FindBalls ${OpenCV_LIBS} ${raspicam_CV_LIBS} ${WIRINGPI_LIBRARIES})
