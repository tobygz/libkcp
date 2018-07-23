cmake_minimum_required(VERSION 2.8.7)
project(kcp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -lpthread")

set(EP_TEST ep_server.cpp)
set(MAIN_TEST kcp_test.cpp)
#set(FEC_TEST fec_test.cpp)
#set(SER_TEST kcp_serv.cpp)
set(SOURCE_FILES ikcp.c sessServer.cpp sess.cpp galois.cpp galois_noasm.cpp matrix.cpp inversion_tree.cpp reedsolomon.cpp fec.cpp galois_table.c)
add_executable(kcp_test ${SOURCE_FILES} ${MAIN_TEST})
add_executable(ep_kcp ${SOURCE_FILES} ${EP_TEST})
#add_executable(fec_test ${SOURCE_FILES} ${FEC_TEST})
#add_executable(kcp_serv ${SOURCE_FILES} ${SER_TEST})
