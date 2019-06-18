#include "session.h"


Session::~Session()
{
  if (fp_) fclose(fp_);
  clock_ = clock() - clock_;
  Size_type bytes_writen = total_bytes_writen_;
  if (clock_ == 0) clock_ = 1;
  double speed = bytes_writen * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / clock_ ;
  std::cout << "cost time: " << clock_ / (double) CLOCKS_PER_SEC << " s  "
     << "bytes_writen: " << bytes_writen << " bytes\n"
     << "speed: " <<  speed << " MB/s\n\n";
}

void Session::start()
{
  clock_ = clock();
  std::cout << "client: " << socket_.remote_endpoint().address() << "\n";
  socket_.async_receive(
    asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
              boost::bind(&Session::handle_header, shared_from_this(), asio::placeholders::error));
}

void Session::handle_header(const Session::Error &error)
{
  if (error) return print_asio_error(error);
  size_t filename_size = file_info_.filename_size;
  if (filename_size > k_buffer_size) {
    std::cerr << "Path name is too long!\n";
    return;
  }
  //得用async_read, 不能用async_read_some，防止路径名超长时，一次接收不完
  asio::async_read(socket_, asio::buffer(buffer_, file_info_.filename_size),
                   boost::bind(&Session::handle_file, shared_from_this(), asio::placeholders::error));
}

void Session::handle_file(const Session::Error &error)
{
    {
      if (error) return print_asio_error(error);
      const char *basename = buffer_ + file_info_.filename_size - 1;
      while (basename >= buffer_ && (*basename != '\\' && *basename != '/')) --basename;
      ++basename;

      std::cout << "Open file: " << basename << " (" << buffer_ << ")\n";

      fp_ = fopen(basename, "w");
      if (fp_ == NULL) {
        std::cerr << "Failed to open file to write\n";
        return;
      }
      receive_file_content();
    }
}

void Session::receive_file_content()
{
    {
      socket_.async_receive(asio::buffer(buffer_, k_buffer_size),
        boost::bind(&Session::handle_write, shared_from_this(), asio::placeholders::error,
          asio::placeholders::bytes_transferred));
    }
}

void Session::handle_write(const Session::Error &error, size_t bytes_transferred)
{
  if (error) {
    if (error != asio::error::eof) return print_asio_error(error);
    Size_type filesize = file_info_.filesize;
    if (total_bytes_writen_ != filesize)
        std::cerr <<  "Filesize not matched! " << total_bytes_writen_
          << "/" << filesize << "\n";
    return;
  }
  total_bytes_writen_ += fwrite(buffer_, 1, bytes_transferred, fp_);
  receive_file_content();
}
