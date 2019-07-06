#ifndef CLIENT_H
#define CLIENT_H

//周敏 客户端数据传输

#include <iostream>
#include <cstdio>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <fstream>

#include "file_info.h"

class Client : public boost::enable_shared_from_this<Client>
{
public:
    typedef asio::error_code Error;
    typedef asio::ip::tcp TCP;
    typedef boost::shared_ptr<Client> Pointer;
    typedef File_info::Size_type Size_type;

    static Pointer create(asio::io_service& io) {
        return Pointer(new Client(io));
    }
    ~Client();

    static void print_asio_error(const Error& error) { std::cerr << "error: " << error.message() << "\n";}

    TCP::socket& socket() { return socket_; }

    size_t message_max_size = 10;
    size_t id_max_size = 20;
    size_t password_max_size = 20;
    size_t result = 6;
    size_t download_path_max_size = 100;

    //获取在线歌单list
    void getOnlineSonglist();

    //得到所有歌单
    void getAllMusic();

    //获取歌单
    void getSonglist(std::string songlist);

    //上传文件
    void downloadFile(const char * filePath);

    //下载文件
    void uploadFile(const char * filePath);

    //登录
    bool login(const char *id, const char *password);

    //注册
    bool registe(const char *id, const char *password);

private:
    Client(asio::io_service& io);

    void connetct(const char* ip_address, unsigned port);

    //上传用户自定义歌单
    void customSonglist();

    //发送文件
    void sendFile(const char *filename);

    //发送服务器服务请求
    void message(const char* sevice);

    void handle_json(const Error& error);

    //处理头（文件信息）
    void handle_header(const Error& error);

    //处理文件
    void handle_file(const Error& error);

    //接收文件内容
    void receive_file_content();

    //将接收到的内容写入文件中
    void handle_write(const Error& error, size_t bytes_transferred);


    TCP::socket socket_; //套接字

    clock_t clock_;
    FILE *fp_;  //文件
    File_info file_info_; //文件信息
    Size_type total_bytes_writen_; //文件总大小
    static const unsigned k_buffer_size = 1024 * 32; //最大传输
    char buffer_[k_buffer_size];
    int save_status = 0; // 传输文件的类型 0：默认 1：歌单池的json 2：歌单的json

    std::vector<std::string> m_songlistLab;
    std::vector<stru_music> m_songlist;

    std::ofstream m_fs;
};

#endif // CLIENT_H
