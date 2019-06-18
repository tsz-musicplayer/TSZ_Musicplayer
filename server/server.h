#ifndef SERVER_H
#define SERVER_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "file_info.h"
#include "session.h"

class Server
{
public:
  typedef asio::ip::tcp TCP;
  typedef asio::error_code Error;

  Server(asio::io_service& io, unsigned port) :
      acceptor_(io, TCP::endpoint(TCP::v4(), port))
  {
    start_accept();
  }

  static void print_asio_error(const Error& error) { std::cerr << error.message() << "\n";}

private:
  void start_accept();

  //处理接收
  void handle_accept(Session::Pointer session, const Error& error);

  TCP::acceptor acceptor_;
};


#endif // SERVER_H
