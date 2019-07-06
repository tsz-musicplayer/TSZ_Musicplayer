#include "server.h"

Server::~Server()
{
}

void Server::start_accept()
{
  Session::Pointer session = Session::create(acceptor_.get_io_service());
  acceptor_.async_accept(session->socket(),
                         boost::bind(&Server::handle_accept, this, session, asio::placeholders::error));
}

void Server::handle_accept(Session::Pointer session, const Server::Error &error)
{
  if (error) return print_asio_error(error);
  session->receive_service();
  start_accept();
}
