#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the hidapiBrowserPlugin project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    *.h
    *.cmake
    )

include_directories(${PLUGIN_INCLUDE_DIRS})

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

if (APPLE)
SET (EXTRA_HIDAPI ${FB_ROOT}/external/hidapi/mac/hid.c)
elseif (WIN32)
SET (EXTRA_HIDAPI ${FB_ROOT}/external/hidapi/windows/hid.c)
else()
SET (EXTRA_HIDAPI )
endif ()

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    ${EXTRA_HIDAPI}
    )

# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

# Include hidapi

set (HIDAPI_PATH ${FB_ROOT}/external/hidapi)
include_directories(${HIDAPI_PATH}/hidapi)
if (WIN32)
target_link_libraries(${PROJECT_NAME} debug "setupapi.lib")
target_link_libraries(${PROJECT_NAME} optimized "setupapi.lib")
elseif (APPLE)
target_link_libraries(${PROJECT_NAME} debug "-framework IOKit")
target_link_libraries(${PROJECT_NAME} optimized "-framework IOKit")
else()
target_link_libraries(${PROJECT_NAME} debug "${HIDAPI_PATH}/libusb/.libs/libhidapi-libusb.so")
target_link_libraries(${PROJECT_NAME} optimized "${HIDAPI_PATH}/libusb/.libs/libhidapi-libusb.so")
endif ()

#this will build a Chrome package
#add_chrome_package(${PLUGIN_NAME}
#	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#	"${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
#	"${CMAKE_CURRENT_SOURCE_DIR}/sign/package_key.pem"
#	${PROJECT_NAME})

#this will build a XPI package using XPISigner (see http://code.google.com/p/xpisigner/ )
# add_signed_xpi_installer(${PLUGIN_NAME}
# 	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#   "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
# 	$ENV{XPI_PATH} 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx" 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
# 	${PROJECT_NAME})

