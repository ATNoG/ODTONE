project(mih_usr)

find_package(Threads REQUIRED)

set(app_SRC
mih_usr.cpp
)

include_directories("../../inc")
add_executable(odtone-mih_usr ${app_SRC})
target_link_libraries(odtone-mih_usr libodtone ${CMAKE_THREAD_LIBS_INIT})

# install app
install(FILES mih_usr.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-mih_usr EXPORT odtone-mih_usr
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
