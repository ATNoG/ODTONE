project(odtone)

cmake_minimum_required(VERSION 2.8)

option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF)

set(Boost_USE_MULTITHREAD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(odtone_MAJOR_VERSION "0")
set(odtone_MINOR_VERSION "5")
set(odtone_MICRO_VERSION "0")
set(odtone_VERSION "${odtone_MAJOR_VERSION}.${odtone_MINOR_VERSION}.${odtone_MICRO_VERSION}")

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed (default is /lib${LIB_SUFFIX})" FORCE)

add_definitions(-DBOOST_ENABLE_ASSERT_HANDLER)
add_subdirectory(lib/odtone)
add_subdirectory(src/mihf)
if(UNIX)
  add_subdirectory(lib/external/libnl/nlwrap)
endif()
add_subdirectory(app/dhcp_usr/client)
add_subdirectory(app/dns_usr)
add_subdirectory(app/link_sap)
add_subdirectory(app/link_sap_icmp)
add_subdirectory(app/mih_usr)
add_subdirectory(app/miis_rdf_server)
if(UNIX)
  add_subdirectory(app/sap_80211_linux)
endif()
add_subdirectory(app/sap_8023)
if(BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif()

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${odtone_VERSION})
add_custom_target(dist
    COMMAND mkdir -p "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}" &&
            git log > "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}/ChangeLog" &&
            git archive --prefix=${ARCHIVE_NAME}/ HEAD --format=tar --output="${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            tar -C "${CMAKE_BINARY_DIR}" --owner=root --group=root -r "${ARCHIVE_NAME}/ChangeLog" -f "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            bzip2 -f9 "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            echo "Source package created at ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2.\n"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
