#ifndef MSGSERIAL
#define MSGSERIAL

#include <iostream>
#include "Summary.h"
#include <stdint.h>
#include <string.h>

//typedef struct {
  //uint16_t body_len;
  //uint16_t code;
//}SumHeader;

namespace argusnet
{
const uint16_t MSG_DATA_MAX_LENGTH = 0x80; //传输数据最大为128字节
const uint16_t DATA_TOTAL_LENGTH = MSG_DATA_MAX_LENGTH + 4*4 +4;


class MsgBody
{
public:
  MsgBody ():
      msg_body_len_(0),
      msg_data_(NULL)
  {
    data_ = new char[DATA_TOTAL_LENGTH];
    msg_data_ = data_ + 4 * 4 + 4;
  }
  virtual ~MsgBody ()
  {
    delete[] data_;
  }
  
  int get_data_len()
  {
    if(msg_body_len_ != 0)
    {
      return msg_body_len_ + 4*4 +4;
    }
    else
    {
      return DATA_TOTAL_LENGTH;
    }
  }

  int get_msg_body_len()
  {
    return msg_body_len_;
  }
  void set_msg_body_len(const uint32_t body_len)
  {
    msg_body_len_ = body_len;
  }

  const char* get_data()
  {
    return data_;
  }

  void set_data(char* data,uint32_t data_length)
  {
    memcpy(data_,data,data_length);
  }
  const char* get_msg_data()
  {
    return msg_data_;
  }


  int GetDataFromSummary(char* buffer,const SummaryInfo& suminfo);
  int GetSummaryFromData(const char* buffer, SummaryInfo& suminfo);

  int Serialize(const SummaryInfo& suminfo);
  int Deserialize(SummaryInfo& suminfo);
private:
  uint32_t msg_body_len_;
  uint32_t length_[4];
  char* msg_data_;
  char* data_;
};

}//namespace argusnet
#endif
