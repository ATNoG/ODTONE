project(nlwrap)

find_package(PkgConfig)
pkg_check_modules(LIBNL REQUIRED libnl-3.0)
pkg_check_modules(LIBNL_ROUTE REQUIRED libnl-route-3.0)
pkg_check_modules(LIBNL_GEN REQUIRED libnl-genl-3.0)

set(libnlwrap_MAJOR_VERSION ${odtone_MAJOR_VERSION})
set(libnlwrap_MINOR_VERSION ${odtone_MINOR_VERSION})
set(libnlwrap_MICRO_VERSION ${odtone_MICRO_VERSION})
set(libnlwrap_VERSION "${libnlwrap_MAJOR_VERSION}.${libnlwrap_MINOR_VERSION}.${libnlwrap_MICRO_VERSION}")
set(libnlwrap_SOVERSION "${libnlwrap_MAJOR_VERSION}.${libnlwrap_MINOR_VERSION}")

set(libnlwrap_SRC
nl_cb.cpp
nl_socket.cpp
nl_msg.cpp
genl_msg.cpp
genl_socket.cpp
rtnl_socket.cpp
rtnl_link.cpp
rtnl_link_cache.cpp
)

include_directories("../../../../inc"
                    ${INCLUDE_DIRECTORIES}
                    ${LIBNL_INCLUDE_DIRS}
                    ${LIBNL_ROUTE_INCLUDE_DIRS}
                    ${LIBNL_GEN_INCLUDE_DIRS})
add_library(libnlwrap SHARED ${libnlwrap_SRC})
target_link_libraries(libnlwrap ${LIBNL_LIBRARIES} ${LIBNL_ROUTE_LIBRARIES} ${LIBNL_GEN_LIBRARIES} libodtone)
set_target_properties(libnlwrap PROPERTIES OUTPUT_NAME "nlwrap"
                                           VERSION ${libnlwrap_VERSION}
                                           SOVERSION ${libnlwrap_SOVERSION}
                                           DEFINE_SYMBOL LIBNLWRAP_EXPORTS)

# install libnlwrap
install(FILES ${libnlwrap_HEADERS} DESTINATION include/nlwrap/mih)
install(TARGETS libnlwrap EXPORT nlwrap
                          LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                          ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                          RUNTIME DESTINATION bin)
