#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include "Summary.h"
#include "MsgSerial.h"
#include "DataAnalysis.h"
#include "ArgusServer.h"
#include "ArgusMonitor.h"

using boost::asio::ip::tcp;
using argusnet::MsgBody;
using namespace argusserver;

class Session
  :public boost::enable_shared_from_this<Session>
{
 public:
  Session(boost::asio::io_service& io_service)
      : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&Session::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
  }


  void set_analysis(DataAnalysisPtr analysis_ptr)
  {
    analysis_ptr_ = analysis_ptr;
  }
  void get_analysis(DataAnalysisPtr& analysis_ptr)
  {
    analysis_ptr = analysis_ptr_;
  }
 private:
  void handle_read(const boost::system::error_code& error,
                   size_t bytes_transferred)
  {
    if (!error)
    {
      msg_body_.set_data(data_,bytes_transferred);
      msg_body_.Deserialize(suminfo_);
      if(analysis_ptr_)
      {
        analysis_ptr_->Collect(suminfo_);
      }

      ArgusMonitor am;
      am.ThresholdAlarm(analysis_ptr_);
      //analysis_ptr_->PrintHostList();
      //std::cout << suminfo_.hostname << std::endl;
      //std::cout << suminfo_.content << std::endl;
      //std::cout << suminfo_.val << std::endl;
      //std::cout << suminfo_.time << std::endl;
    }
    shared_from_this()->start();
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  MsgBody msg_body_;
  SummaryInfo suminfo_;
  DataAnalysisPtr analysis_ptr_;
};

typedef boost::shared_ptr<Session> SessionPtr;

class Server
{
 public:
  Server(boost::asio::io_service& io_service,
         const tcp::endpoint& endpoint)
      : io_service_(io_service),
      acceptor_(io_service, endpoint)
  {
    analysis_ptr_ = (DataAnalysisPtr)(new DataAnalysis());
    start_accept();
  }

 private:
  void start_accept()
  {
    SessionPtr new_session(new Session(io_service_));
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&Server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(SessionPtr new_session,
                     const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->set_analysis(analysis_ptr_);
      new_session->start();
    }

    start_accept();
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  DataAnalysisPtr analysis_ptr_;
};

typedef boost::shared_ptr<Server> ServerPtr;
typedef std::list<ServerPtr> ServerPtrList;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>";
      return 1;
    }

    boost::asio::io_service io_service;

    ServerPtrList servers;
    for (int i = 1; i < argc; ++i)
    {
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      ServerPtr server_p(new Server(io_service, endpoint));
      servers.push_back(server_p);
      ArgusMonitor am;
      //am.ThresholdAlarm()
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "";
  }

  return 0;
}
