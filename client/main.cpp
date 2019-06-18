#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/shared_ptr.hpp>
#include "file_info.h"

void sender(asio::io_service& io, const char* ip_address, unsigned port, const char* filename)
{
  typedef asio::ip::tcp TCP;

  //打开文件
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    std::cerr << "cannot open file\n" << filename;
    return;
  }

  //使用智能指针，防止程序出现异常时，fclose未被调用。
  boost::shared_ptr<FILE> file_ptr(fp, fclose);

  clock_t cost_time = clock();

  //一次传输的文件大小
  const size_t k_buffer_size = 32 * 1024;
  char buffer[k_buffer_size];

  //文件信息
  File_info file_info;

  //文件名大小
  int filename_size  = strlen(filename) + 1;
  //文件信息大小
  size_t file_info_size = sizeof(file_info);
  //文件总大小
  size_t total_size = file_info_size + filename_size;
  if (total_size > k_buffer_size) {
    std::cerr << "File name is too long";
    return;
  }

  file_info.filename_size = filename_size;

  //重定位流
  //fseek：是把文件指针指向文件的开头
  fseek(fp, 0, SEEK_END);
  file_info.filesize = ftell(fp);
  //使文件fp的位置指针指向文件开始
  rewind(fp);

  //由file_info所指内存区域复制file_info_size个字节到buffer所指内存区域。
  memcpy(buffer, &file_info, file_info_size);
  memcpy(buffer + file_info_size, filename, filename_size);

  //设置地址和端口
  TCP::socket socket(io);
  socket.connect(TCP::endpoint(asio::ip::address_v4::from_string(ip_address), port));

  std::cout << "Sending file : " << filename << "\n";
  size_t len = total_size;
  unsigned long long total_bytes_read = 0;

  //传输文件
  while (true) {
      //传输文件
    socket.send(asio::buffer(buffer, len), 0);
    if (feof(fp)) break;
    //将文件写入流中
    len = fread(buffer, 1, k_buffer_size, fp);
    total_bytes_read += len;
  }

  cost_time = clock() - cost_time;
  if (cost_time == 0) cost_time = 1;
  double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
  std::cout << "cost time: " << cost_time / (double) CLOCKS_PER_SEC  << " s "
    << "  transferred_bytes: " << total_bytes_read << " bytes\n"
    << "speed: " <<  speed << " MB/s\n\n";
}

int main(/*int args, char* argc[]*/)
{

  std::string addr, filename;
  addr = "127.0.0.1";
  filename = "/root/test.txt";

  asio::io_service io;

  try {
      sender(io, "127.0.0.1", 1345, "/root/test/最美.mp3");
  }
  catch (std::exception& err) {
    std::cerr << err.what() << "\n";
  }

}
