project(miis_rdf_server)

find_package(Threads REQUIRED)
find_package(PkgConfig)
pkg_check_modules(REDLAND REQUIRED redland)

set(app_SRC
miis_rdf_server.cpp
)

include_directories("../../inc" ${nlwrap_SOURCE_DIR} ${REDLAND_INCLUDE_DIRS})
add_executable(odtone-miis_rdf_server ${app_SRC})
target_link_libraries(odtone-miis_rdf_server libodtone ${REDLAND_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# install app
install(FILES miis_rdf_server.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-miis_rdf_server EXPORT odtone-miis_rdf_server
                               LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                               ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                               RUNTIME DESTINATION bin)
