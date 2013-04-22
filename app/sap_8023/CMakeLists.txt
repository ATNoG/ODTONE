project(sap_8023)

find_package(Threads REQUIRED)
find_package(PkgConfig)
pkg_check_modules(LIBNL REQUIRED libnl-3.0)

set(app_SRC
main.cpp
timer_task.cpp
)

if(UNIX)
	LIST(APPEND app_SRC linux/if_8023.cpp linux/ethtool.cpp)
endif()

include_directories("../../inc"
                    ${LIBNL_INCLUDE_DIRS}
                    ${nlwrap_SOURCE_DIR})
add_executable(odtone-sap_8023 ${app_SRC})
target_link_libraries(odtone-sap_8023 ${LIBNL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} libnlwrap libodtone)

# install app
install(FILES sap_8023.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-sap_8023 EXPORT odtone-sap_8023
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
