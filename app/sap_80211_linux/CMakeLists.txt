project(sap_80211_linux)

find_package(Threads REQUIRED)
find_package(PkgConfig)
pkg_check_modules(LIBNL_ROUTE REQUIRED libnl-route-3.0)

set(app_SRC
main.cpp
timer_task.cpp
linux/if_80211.cpp
)

include_directories("../../inc" ${nlwrap_SOURCE_DIR} ${LIBNL_INCLUDE_DIRS})
add_executable(odtone-sap_80211 ${app_SRC})
target_link_libraries(odtone-sap_80211 ${CMAKE_THREAD_LIBS_INIT} ${LIBNL_ROUTE_LIBRARIES} libnlwrap libodtone)

# install app
install(FILES sap_80211.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-sap_80211 EXPORT odtone-sap_80211
                                 LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                                 ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                                 RUNTIME DESTINATION bin)
