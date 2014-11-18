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
//const uint16_t MSG_FLAG = 0x2323;
//const uint16_t MSG_HEADER_LENGTH = 64;
//class MsgHeader
//{
//public:
  //MsgHeader ():
      //msg_flag_(MSG_FLAG),
      //msg_header_len_(MSG_HEADER_LENGTH),
      //msg_body_len_(0),
      //msg_code_(0){}
  //MsgHeader (uint16_t body_len,uint16_t code):
      //msg_flag_(MSG_FLAG),
      //msg_header_len_(MSG_HEADER_LENGTH),
      //msg_body_len_(body_len),
      //msg_code_(code){}
  //virtual ~MsgHeader ();

  //int Serialize(char* buffer,uint32_t buf_len);
  //int Deserialize(const char* buffer,uint32_t buf_len);

  //void  SetDataFromSumHeader(SumHeader sumheader)
  //{
    //msg_body_len_ = sumheader.body_len;
    //msg_code_ = sumheader.code;
  //}

  //int get_msg_header_len()
  //{
    //return msg_header_len_;
  //}

  //int get_msg_body_len()
  //{
    //return msg_body_len_;
  //}

  //void set_msg_body_len(const uint16_t body_len)
  //{
    //msg_body_len_=body_len;
  //}
//private:
  //uint16_t msg_flag_;
  //uint16_t msg_header_len_;
  //uint16_t msg_body_len_;
  //uint16_t msg_code_;
//};

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

//namespace nettools
//{
//int Encode_16 ( char* buffer, uint16_t data );
//int Decode_16 ( const char* buffer, uint16_t& data );
//int Encode_32 ( char* buffer, uint32_t data );
//int Decode_32 ( const char* buffer, uint32_t& data );
//}//namespace nettools
}//namespace argusnet
#endif
