CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(max7456-osd)

#set the board which you want to use
SET(MY_SOC "STM32F031K4T6")
#SET(MY_SOC "STM32F031K4T6")

#set the compile mode with dynamic or static 
OPTION(MY_STATIC "Compile with staitc mode" ON)

#set soc compiler and arch 
IF (MY_SOC STREQUAL "Allwinner H5")
	SET(MY_GCC "aarch64-linux-gnu-gcc")
	SET(MY_G++ "aarch64-linux-gnu-g++")
	SET(MY_ARC "aarch64")
ELSEIF (MY_SOC  STREQUAL "Exynos4412")
	SET(MY_GCC "arm-none-linux-gnueabi-gcc")
	SET(MY_G++ "arm-none-linux-gnueabi-g++")
	SET(MY_ARC "arm")
ELSE (MY_SOC STREQUAL "Native")
	SET(MY_GCC "gcc")
	SET(MY_G++ "g++")
	SET(MY_ARC "amd64")
ENDIF()

#set compile mode
IF (MY_STATIC)
	SET(MY_MOD "Static Compile")
	SET(MY_LNK "opencv_legacy opencv_video opencv_calib3d opencv_features2d opencv_flann opencv_imgproc opencv_core pthread zlib")
	SET(CMAKE_EXE_LINKER_FLAGS -static) 
	SET(MY_LIB_TYPE "static") 
ELSE () 
	SET(MY_MOD "Dynamic Compile") 
	SET(MY_LNK "opencv_legacy opencv_video opencv_imgproc opencv_core pthread zlib") 
	SET(MY_LIB_TYPE "dynamic") 
ENDIF ()

#user should modify this base on your path
SET(MY_LIB_BASEPTH "~/Workspace/opencv/install")
SET(MY_LIB_VERSION "3.4.0")
SET(MY_LIB_SOCARCH "opencv_${MY_ARC}")
SET(MY_LIB "${MY_LIB_BASEPTH}/${MY_LIB_SOCARCH}/${MY_LIB_VERSION}/${MY_LIB_TYPE}/lib")
SET(MY_INC "${MY_LIB_BASEPTH}/${MY_LIB_SOCARCH}/${MY_LIB_VERSION}/${MY_LIB_TYPE}/include")

#set cmake compile
SET(CMAKE_C_COMPILER ${MY_GCC})
SET(CMAKE_CXX_COMPILER ${MY_G++})

SET(CMAKE_CXX_FLAGS "-std=c++11 -Wl,-Map,system.map")
#SET(CMAKE_CXX_FLAGS "-std=gnu++11")

#show set info
MESSAGE("")
MESSAGE("**********************************************************")
MESSAGE(" SOC: ${MY_SOC}")
MESSAGE(" ARC: ${MY_ARC}")
MESSAGE(" MOD: ${MY_MOD}")
MESSAGE(" GCC: ${MY_GCC}")
MESSAGE(" G++: ${MY_G++}")
MESSAGE(" LIB: ${MY_LIB}")
MESSAGE(" INC: ${MY_INC}")
MESSAGE(" LNK: ${MY_LNK}")
MESSAGE("**********************************************************")
MESSAGE("")

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

INCLUDE_DIRECTORIES(inc ${MY_INC})
LINK_DIRECTORIES(${MY_LIB})
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

#Bug: Use ${MY_LNK} not success 
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${MY_LNK})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} opencv_objdetect opencv_ml opencv_video opencv_imgcodecs IlmImf libwebp libjasper libpng libjpeg opencv_highgui opencv_calib3d opencv_features2d opencv_flann opencv_videoio opencv_imgproc opencv_core tbb dl pthread zlib )
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} opencv_legacy opencv_video opencv_imgproc opencv_core pthread)

