g++ ArgusServer.cpp Summary.cpp MsgSerial.cpp DataAnalysis.cpp -Wall -lboost_system -lboost_date_time -g -o serv
g++ ArgusClient.cpp Summary.cpp MsgSerial.cpp CPUusage.cpp Memusage.cpp Diskusage.cpp -Wall -lboost_thread -lboost_system -lpthread -lboost_date_time -g -o client
