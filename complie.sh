g++ ArgusServer.cpp Summary.cpp MsgSerial.cpp -lboost_system -g -o serv
g++ ArgusClient.cpp Summary.cpp MsgSerial.cpp CPUusage.cpp -lboost_thread -lboost_system -g -o client

