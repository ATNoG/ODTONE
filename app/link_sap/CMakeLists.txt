project(link_sap)

find_package(Threads REQUIRED)

set(app_SRC
interface/interface.cpp
interface/if_802_11.cpp
link_sap.cpp
)

if(MSVC)
	LIST(APPEND app_SRC win32/main.cpp win32/win32.cpp)
elseif(UNIX)
	LIST(APPEND app_SRC linux/main.cpp linux/netlink.cpp linux/rtnetlink.cpp)
endif()

include_directories("../../inc")
add_executable(odtone-link_sap ${app_SRC})
target_link_libraries(odtone-link_sap libodtone ${CMAKE_THREAD_LIBS_INIT})

# install app
install(FILES link_sap.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-link_sap EXPORT odtone-link_sap
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
