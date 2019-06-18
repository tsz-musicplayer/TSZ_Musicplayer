#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <cstdio>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "file_info.h"

class Session : public boost::enable_shared_from_this<Session> {
public:
  typedef asio::ip::tcp TCP;
  typedef asio::error_code Error;
  typedef boost::shared_ptr<Session> Pointer;
  typedef File_info::Size_type Size_type;

  static void print_asio_error(const Error& error) { std::cerr << error.message() << "\n";}

  static Pointer create(asio::io_service& io) { return Pointer(new Session(io));}

  TCP::socket& socket() { return socket_; }

  ~Session();

  void start();

private:
  Session(asio::io_service& io) : socket_(io), fp_(NULL), total_bytes_writen_(0) { }

  //处理头
  void handle_header(const Error& error);

  //处理文件
  void handle_file(const Error& error);

  //接收文件内容
  void receive_file_content();

  //将接收到的内容写入文件中
  void handle_write(const Error& error, size_t bytes_transferred);

  clock_t clock_;
  TCP::socket socket_; //套接字
  FILE *fp_; //文件
  File_info file_info_; //文件信息
  Size_type total_bytes_writen_; //文件总大小
  static const unsigned k_buffer_size = 1024 * 32; //最大传输
  char buffer_[k_buffer_size];
};

#endif // SESSION_H
