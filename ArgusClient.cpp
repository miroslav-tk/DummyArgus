#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "Summary.h"
#include "CPUusage.h"

using boost::asio::ip::tcp;

typedef std::deque<SummaryInfo> SummaryInfo_queue;


class ArgusClient
{
 public:
  ArgusClient(boost::asio::io_service& io_service,
              tcp::resolver::iterator endpoint_iterator)
      : io_service_(io_service),
      socket_(io_service)
  {
    boost::asio::async_connect(socket_, endpoint_iterator,
                               boost::bind(&ArgusClient::handle_connect, this,
                                           boost::asio::placeholders::error));
  }

  void write(const SummaryInfo& msg)
  {
    io_service_.post(boost::bind(&ArgusClient::do_write, this, msg));
  }

  void close()
  {
    io_service_.post(boost::bind(&ArgusClient::do_close, this));
  }

 private:

  void handle_connect(const boost::system::error_code& error)
  {
    if (!error)
    {
      boost::asio::async_read(socket_,
                              boost::asio::buffer((char*)(&read_msg_)
                                                  ,sizeof(SummaryInfo)),
                              boost::bind(&ArgusClient::handle_read, this,
                                          boost::asio::placeholders::error));
    }
  }

  void handle_read(const boost::system::error_code& error)
  {
    if (!error)
    {
/*      std::cout.write(read_msg_.body(), read_msg_.body_length());*/
      //std::cout << "";
      //boost::asio::async_read(socket_,
                              //boost::asio::buffer(read_msg_.data(), SummaryInfo::header_length),
                              //boost::bind(&ArgusClient::handle_read_header, this,
                                          /*boost::asio::placeholders::error));*/
    }
    else
    {
      do_close();
    }
  }

  void do_write(SummaryInfo msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      boost::asio::async_write(socket_,
                               boost::asio::buffer( (char* )(&(write_msgs_.front())),
                                                   sizeof(SummaryInfo)),
                               boost::bind(&ArgusClient::handle_write, this,
                                           boost::asio::placeholders::error));
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      write_msgs_.pop_front();
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
                               boost::asio::buffer( (char* )(&(write_msgs_.front())),
                                                   sizeof(SummaryInfo)),
                                 boost::bind(&ArgusClient::handle_write, this,
                                             boost::asio::placeholders::error));
      }
    }
    else
    {
      do_close();
    }
  }

  void do_close()
  {
    socket_.close();
  }

 private:
  boost::asio::io_service& io_service_;
  tcp::socket socket_;
  SummaryInfo read_msg_;
  SummaryInfo_queue write_msgs_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: ArgusClient <host> <port>";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    ArgusClient c(io_service, iterator);

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    SummaryInfo msg;
    CPUusage cpuusage;
	  bool b_got_cpu = cpuusage.CalCPUusage(msg);
    c.write(msg);

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "";
  }

  return 0;
}
