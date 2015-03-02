#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Summary.h"
#include "CPUusage.h"
#include "Memusage.h"
#include "Diskusage.h"
#include "LoadAverage.h"
#include "MsgSerial.h"

using boost::asio::ip::tcp;
using argusnet::MsgBody;

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

  void CPUusage_start(const int& count,const int& stride)
  {
    CPUusage cpuusage;
    SummaryInfo msg;
    int stride_t;
    if(stride <= 0)
    {
      stride_t = 1;
    }
    else
    {
      stride_t = stride;
    }
    for (int i = 0; i < count; ++i)
    {
      cpuusage.CalCPUusage(msg);
      this->write(msg);
      boost::this_thread::sleep(boost::posix_time::seconds(stride_t));
    }
  }

  void Memusage_start(const int& count,const int& stride)
  {
    Memusage memusage;
    SummaryInfo msg;
    int stride_t;
    if(stride <= 0)
    {
      stride_t = 1;
    }
    else
    {
      stride_t = stride;
    }
    for (int i = 0; i < count; ++i)
    {
      memusage.CalMemusage(msg);
      this->write(msg);
      boost::this_thread::sleep(boost::posix_time::seconds(stride_t));
    }
  }

  void Diskusage_start(const int& count,const int& stride,const std::string& mount_point)
  {
    Diskusage diskusage;
    SummaryInfo msg;
    int stride_t;
    if(stride <= 0)
    {
      stride_t = 1;
    }
    else
    {
      stride_t = stride;
    }
    for (int i = 0; i < count; ++i)
    {
      diskusage.CalDiskusage(mount_point,msg); 
      this->write(msg);
      boost::this_thread::sleep(boost::posix_time::seconds(stride_t));
    }
  }

  void Loadaverage_start(const int& count,const int& stride)
  {
    LoadAverage Loadaverage; 
    SummaryInfo msg;
    int stride_t;
    if(stride <= 0)
    {
      stride_t = 1;
    }
    else
    {
      stride_t = stride;
    }
    for (int i = 0; i < count; ++i)
    {
      Loadaverage.CalLoadAverage(msg);
      this->write(msg);
      boost::this_thread::sleep(boost::posix_time::seconds(stride_t));
    }
  }

 private:

  void handle_connect(const boost::system::error_code& error)
  {
    if (!error)
    {
      std::cout << "Connect Succeed!" << std::endl;
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
      msg_body_.Serialize(write_msgs_.front());
      boost::asio::async_write(socket_,
                               boost::asio::buffer(msg_body_.get_data(),
                                                   msg_body_.get_data_len()),
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
        msg_body_.Serialize( write_msgs_.front());
        boost::asio::async_write(socket_,
                               boost::asio::buffer(msg_body_.get_data(),
                                                   msg_body_.get_data_len()),
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
  argusnet::MsgBody msg_body_;
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

    boost::asio::io_service::work my_work(io_service);
    boost::thread main_thread(boost::bind(&boost::asio::io_service::run ,&io_service));

    boost::thread cpuusage_thread(boost::bind(&ArgusClient::CPUusage_start,&c,3,1));
    boost::thread memusage_thread(boost::bind(&ArgusClient::Memusage_start,&c,3,10));
    boost::thread diskusage_thread(boost::bind(&ArgusClient::Diskusage_start,&c,3,10,"/opt"));
    boost::thread loadaverage_thread(boost::bind(&ArgusClient::Loadaverage_start,&c,3,10));

    cpuusage_thread.join();
    memusage_thread.join();
    diskusage_thread.join();
    c.close();
    main_thread.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "";
  }

  return 0;
}
