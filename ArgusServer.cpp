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

using boost::asio::ip::tcp;
using argusnet::MsgBody;

int i =2;
class session
  :public boost::enable_shared_from_this<session>
{
 public:
  session(boost::asio::io_service& io_service)
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
                            boost::bind(&session::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
  }

 private:
  void handle_read(const boost::system::error_code& error,
                   size_t bytes_transferred)
  {
    if (!error)
    {
      msg_body_.set_data(data_,bytes_transferred);
      msg_body_.Deserialize(suminfo_);
      analysis.Collect(suminfo_);
      if(i==1) analysis.get_host_list();
      else --i;
      std::cout <<i << std::endl;
      std::cout << suminfo_.hostname << std::endl;
      std::cout << suminfo_.content << std::endl;
      std::cout << suminfo_.val << std::endl;
      std::cout << suminfo_.time << std::endl;
    }
    else
    {
      delete this;
    }
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  MsgBody msg_body_;
  SummaryInfo suminfo_;
  DataAnalysis analysis;
};

typedef boost::shared_ptr<session> session_ptr;

class server
{
 public:
  server(boost::asio::io_service& io_service,
         const tcp::endpoint& endpoint)
      : io_service_(io_service),
      acceptor_(io_service, endpoint)
  {
    start_accept();
  }

 private:
  void start_accept()
  {
    session_ptr new_session(new session(io_service_));
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(session_ptr new_session,
                     const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    //else
    //{
      //delete new_session;
    //}

    start_accept();
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};

typedef boost::shared_ptr<server> server_ptr;
typedef std::list<server_ptr> server_list;

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

    server_list servers;
    for (int i = 1; i < argc; ++i)
    {
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      server_ptr server_p(new server(io_service, endpoint));
      servers.push_back(server_p);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "";
  }

  return 0;
}
