#ifndef FILE_INFO_H
#define FILE_INFO_H

#if USE_ASIO_ALONE
    #include <asio.hpp>
  #else
    #include <boost/asio.hpp>
    namespace asio {
      using namespace boost::asio;
      using boost::system::error_code;
    }
  #endif

  struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
  };
  struct stru_music{
      std::string name;
      std::string singer;
      std::string album;
      std::string duration;
      std::string size;
      std::string source;
      std::string lyric;
  };

#endif // FILE_INFO_H
