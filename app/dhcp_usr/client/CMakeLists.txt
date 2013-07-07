project(dhcp_usr)
include(ExternalProject)

find_package(Threads REQUIRED)

add_definitions(-D_GNU_SOURCE)

ExternalProject_Add(dhcp_libs_client
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs"
   BUILD_IN_SOURCE 1
   CONFIGURE_COMMAND "${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/configure"
   BUILD_COMMAND "make"
   INSTALL_COMMAND ""
)

ExternalProject_Get_Property(dhcp_libs_client install_dir)

add_library(libomapi STATIC IMPORTED)
set_property(TARGET libomapi PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/omapip/libomapi.a)
add_dependencies(libomapi dhcp_libs_client)

add_library(libdhcp STATIC IMPORTED)
set_property(TARGET libdhcp PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/common/libdhcp.a)
add_dependencies(libdhcp dhcp_libs_client)

add_library(libdns STATIC IMPORTED)
set_property(TARGET libdns PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/bind/lib/libdns.a)
add_dependencies(libdns dhcp_libs_client)

add_library(libisc STATIC IMPORTED)
set_property(TARGET libisc PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/bind/lib/libisc.a)
add_dependencies(libisc dhcp_libs_client)

set(app_SRC
clparse.c
dhc6.c
dhclient.c
dhcp_control.cpp
dhcp_usr.cpp
log.cpp
main.cpp
)

include_directories("../../../inc" "../libs/includes")
add_executable(odtone-dhcp_usr ${app_SRC})
target_link_libraries(odtone-dhcp_usr ${CMAKE_THREAD_LIBS_INIT} libnlwrap libodtone libomapi libdhcp libdns libisc)

# install app
install(FILES dhcp_usr.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-dhcp_usr EXPORT odtone-dhcp_usr
                                 LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                                 ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                                 RUNTIME DESTINATION bin)
