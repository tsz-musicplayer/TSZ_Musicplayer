#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <cstdio>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "file_info.h"
#include "mydb.h"

class Session : public boost::enable_shared_from_this<Session> {
public:
  typedef asio::ip::tcp TCP;
  typedef asio::error_code Error;
  typedef boost::shared_ptr<Session> Pointer;
  typedef File_info::Size_type Size_type;

   size_t message_max_size = 10;
   size_t id_max_size = 20;
   size_t password_max_size = 20;
   size_t result = 6;
   size_t download_path_max_size = 100;

  static void print_asio_error(const Error& error) { std::cerr << "error: " << error.message() << "\n";}

  static Pointer create(asio::io_service& io) { return Pointer(new Session(io));}

  TCP::socket& socket() { return socket_; }

  ~Session();

  //接收客户端的请求
  void receive_service();

private:
  Session(asio::io_service& io);

  //提供相关服务
  void do_service(const Error& error);

  //发送文件给客户端
  void send();

  //从客户端接收文件
  void receive();

  //执行登录
  void login();

  //执行注册
  void registe();

  //输出文件
  void sendFile(const char * filename);

  //处理请求，提供相应的服务
  void handle_request(const Error& error);

  //处理头（文件信息）
  void handle_header(const Error& error);

  //处理文件
  void handle_file(const Error& error);

  //接收文件内容
  void receive_file_content();

  //将接收到的内容写入文件中
  void handle_write(const Error& error, size_t bytes_transferred);

  //发送在线歌单list
  void onlineSonglist();

  //发送歌单list
  void sendSonglist();

  //得到歌单的json文件
  std::string getSonglistLab(std::string songlistName);

  //接收用户自定义歌单
  void customSonglist();

  clock_t clock_;
  TCP::socket socket_; //套接字
  FILE *fp_; //文件
  File_info file_info_; //文件信息
  Size_type total_bytes_writen_; //文件总大小
  static const unsigned k_buffer_size = 1024 * 32; //最大传输
  char buffer_[k_buffer_size];

};

#endif // SESSION_H
