#include <iostream>
#include <cstdio>

#include "server.h"

int main()
{
  std::cout << "Auto receive files and save then in current directory.\n";
  asio::io_service io;
  Server receiver(io, 1345);
  io.run();
}
