project(dns_usr)

find_package(Threads REQUIRED)

set(app_SRC
dns_usr.cpp
log.cpp
main.cpp
query_book.cpp
)

include_directories("../../inc")
add_executable(odtone-dns_usr ${app_SRC})
target_link_libraries(odtone-dns_usr libodtone ${CMAKE_THREAD_LIBS_INIT})

# install app
install(FILES dns_usr.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-dns_usr EXPORT odtone-dns_usr
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
