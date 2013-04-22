project(mihf)

find_package(Threads REQUIRED)

set(mihf_SRC
main.cpp
service_management.cpp
service_access_controller.cpp
event_service.cpp
mihfid.cpp
log.cpp
command_service.cpp
information_service.cpp
utils.cpp
udp_listener.cpp
tcp_listener.cpp
net_sap.cpp
address_book.cpp
link_book.cpp
user_book.cpp
transaction_pool.cpp
src_transaction.cpp
dst_transaction.cpp
transaction.cpp
message_in.cpp
message_out.cpp
transmit.cpp
link_response_pool.cpp
local_transaction_pool.cpp
meta_message.cpp
discover_service.cpp
)

include_directories("../../inc")
add_executable(odtone-mihf ${mihf_SRC})
target_link_libraries(odtone-mihf libodtone ${CMAKE_THREAD_LIBS_INIT})

# install mihf
install(FILES odtone.conf DESTINATION /etc/odtone/)
install(TARGETS odtone-mihf EXPORT odtone-mihf
                            LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                            ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                            RUNTIME DESTINATION bin)

