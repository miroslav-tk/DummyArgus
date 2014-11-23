g++ ArgusServer.cpp Summary.cpp MsgSerial.cpp -lboost_system -lboost_date_time -g -o serv
g++ ArgusClient.cpp Summary.cpp MsgSerial.cpp CPUusage.cpp -lboost_thread -lboost_system -lpthread -lboost_date_time -g -o client

