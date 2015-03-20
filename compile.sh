g++ ArgusServer.cpp Summary.cpp MsgSerial.cpp ArgusMonitor.cpp DataAnalysis.cpp -Wall -lboost_system -lboost_date_time -lboost_thread -g -o serv
g++ ArgusClient.cpp Summary.cpp MsgSerial.cpp CPUusage.cpp Memusage.cpp Diskusage.cpp LoadAverage.cpp -Wall -lboost_thread -lboost_system -lpthread -lboost_date_time -g -o client
