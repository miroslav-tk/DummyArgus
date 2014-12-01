cmake_minimum_required(VERSION 3.0)

PROJECT(client) 
SET(CLIENT_SRC_LIST ArgusClient.cpp 
	Summary.cpp 
	MsgSerial.cpp 
	CPUusage.cpp
	) 
SET(CMAKE_CXX_COMPILER /usr/bin/clang++-3.5) 
SET(CMAKE_CXX_FLAGS "-Weverything -lboost_thread -lboost_system -lpthread -lboost_date_time")
SET(CMAKE_EXE_LINKER_FLAGS "-lc++ -lc++abi") 
SET(CMAKE_BUILD_TYPE Debug) 
ADD_EXECUTABLE(client ${CLIENT_SRC_LIST})
INSTALL(PROGRAMS client DESTINATION ./bin/)

#PROJECT(serv) 
#SET(SERV_SRC_LIST ArgusServer.cpp 
	#Summary.cpp 
	#MsgSerial.cpp
	#) 
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++-3.5) 
#SET(CMAKE_CXX_FLAGS "-lboost_system -lboost_date_time ")
#SET(CMAKE_EXE_LINKER_FLAGS "-lc++ -lc++abi") 
#SET(CMAKE_BUILD_TYPE Debug) 
#ADD_EXECUTABLE(serv ${SERV_SRC_LIST})
#INSTALL(PROGRAMS serv  DESTINATION ./bin/)

