project(link_sap_icmp)

find_package(Threads REQUIRED)

set(app_SRC
main.cpp
link_sap.cpp
)

include_directories("../../inc")
add_executable(odtone-link_sap_icmp ${app_SRC})
target_link_libraries(odtone-link_sap_icmp libodtone ${CMAKE_THREAD_LIBS_INIT})

# install app
install(FILES link_sap_icmp.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-link_sap_icmp EXPORT odtone-link_sap_icmp
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
