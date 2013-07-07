project(dhcp_server)
include(ExternalProject)

find_package(Threads REQUIRED)

add_definitions(-D_GNU_SOURCE)

ExternalProject_Add(dhcp_libs_server
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs"
   BUILD_IN_SOURCE 1
   CONFIGURE_COMMAND "${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/configure"
   BUILD_COMMAND "make"
   INSTALL_COMMAND ""
)

ExternalProject_Get_Property(dhcp_libs_server install_dir)

add_library(libomapi STATIC IMPORTED)
set_property(TARGET libomapi PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/omapip/libomapi.a)
add_dependencies(libomapi dhcp_libs_server)

add_library(libdhcp STATIC IMPORTED)
set_property(TARGET libdhcp PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/common/libdhcp.a)
add_dependencies(libdhcp dhcp_libs_server)

add_library(libdns STATIC IMPORTED)
set_property(TARGET libdns PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/bind/lib/libdns.a)
add_dependencies(libdns dhcp_libs_server)

add_library(libisc STATIC IMPORTED)
set_property(TARGET libisc PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/app/dhcp_usr/libs/bind/lib/libisc.a)
add_dependencies(libisc dhcp_libs_server)

set(app_SRC
bootp.c
class.c
confpars.c
db.c
ddns.c
dhcp.c
dhcpd.c
dhcpleasequery.c
dhcpv6.c
failover.c
ldap.c
ldap_casa.c
mdb6.c
mdb.c
omapi.c
salloc.c
stables.c
dst/base64.c
dst/dst_api.c
dst/dst_support.c
dst/hmac_link.c
dst/md5_dgst.c
dst/prandom.c
)

include_directories("../../../inc" "../libs/includes")
add_executable(odtone-dhcp_server ${app_SRC})
target_link_libraries(odtone-dhcp_server ${CMAKE_THREAD_LIBS_INIT} libnlwrap libodtone libomapi libdhcp libdns libisc)

# install app
install(TARGETS odtone-dhcp_server EXPORT odtone-dhcp_server
                                 LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                                 ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                                 RUNTIME DESTINATION bin)
