#include "client.h"
#include <QDebug>
#include <string>
#include "json/json.h"

Client::Client(asio::io_service& io)
    :socket_(io), fp_(NULL), total_bytes_writen_(0)
{
}

Client::~Client()
{
    std::cout << "\n ~Client \n" << std::endl;
    if (fp_) fclose(fp_);
    clock_ = clock() - clock_;
    Size_type bytes_writen = total_bytes_writen_;
    if (clock_ == 0) clock_ = 1;
    double speed = bytes_writen * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / clock_ ;
    std::cout << "cost time: " << clock_ / (double) CLOCKS_PER_SEC << " s  "
              << "bytes_writen: " << bytes_writen << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";
}

void Client::connetct()
{
    std::string ip;
    int port;

    std::ifstream ifs;
    ifs.open("../configIpPort");
    if(ifs.is_open()){
        char buff[64];
        ifs.getline(buff, sizeof (buff));
        ip = buff;
        std::cout << buff << std::endl;
        ifs.getline(buff, sizeof(buff));
        std::string p = buff;
        port = atoi(p.c_str());
        std::cout << port << std::endl;
        socket_.connect(TCP::endpoint(asio::ip::address_v4::from_string(ip), port));
    } else {
        std::cout << "configIpPort 文件打开失败" << std::endl;
    }

}

void Client::message(const char *service)
{
    connetct();
    size_t message_size = strlen(service) + 1;

    std::cout << service << std::endl;
    //向服务器发送请求
    socket_.send(asio::buffer(service, message_max_size));
}


void Client::getOnlineSonglist()
{
    message("online");
    save_status = 1;
    socket_.async_receive(
                asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
                boost::bind(&Client::handle_header, shared_from_this(), asio::placeholders::error));


    //得到文件
}

void Client::getSonglist(std::string songlist)
{
    message("songlist");
    save_status = 2;
    socket_.send(asio::buffer(songlist.data(), download_path_max_size));

    std::cout << "songlist:" << songlist << std::endl;

    clock_ = clock();

    std::cout << "client: " << socket_.remote_endpoint().address() << "\n";

    socket_.async_receive(
                asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
                boost::bind(&Client::handle_header, shared_from_this(), asio::placeholders::error));

}

bool Client::registe(const char *id, const char *password)
{
    //向服务器发送registe请求
    message("registe");
    //    std::cout << "registe id: " << id << std::endl;
    //    std::cout << "registe password: " << password << std::endl;
    socket_.send(asio::buffer(id, id_max_size));
    socket_.send(asio::buffer(password, password_max_size));
    socket_.receive(asio::buffer(buffer_, result));
    //    std::cout << "receive registe" << buffer_ << std::endl;
    std::cout << buffer_ << std::endl;
    if(strcmp(buffer_, "true") == 0){
        std::cout << "registe true" << std::endl;
        return true;
    }
    std::cout << "registe false" << std::endl;
    return false;
}

bool Client::login(const char *id, const char *password)
{
    //向服务器发送login请求
    message("login");
    //    std::cout << "login id: " << id << std::endl;
    //    std::cout << "login password: " << password << std::endl;
    socket_.send(asio::buffer(id, id_max_size));
    socket_.send(asio::buffer(password, password_max_size));

    socket_.receive(asio::buffer(buffer_, result));
    //    std::cout << "receive login" << buffer_ << std::endl;
    if(strcmp(buffer_, "true") == 0){
        std::cout << "login true" << std::endl;
        return true;
    }
    std::cout << "login false" << std::endl;
    return false;
}

void Client::uploadFile(const char *filename)
{
    message("upload");
    sendFile(filename);
}

void Client::downloadFile(const char *filename)
{
    message("download");
    socket_.send(asio::buffer(filename, download_path_max_size));

    std::cout << filename << std::endl;

    clock_ = clock();

    std::cout << "client: " << socket_.remote_endpoint().address() << "\n";
    //接收头信息
    socket_.async_receive(
                asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
                boost::bind(&Client::handle_header, shared_from_this(), asio::placeholders::error));

}

void Client::handle_header(const Client::Error &error)
{
    //        std::cout << "\nhandle_header: \n " << std::endl;
    if (error) return print_asio_error(error);

    size_t filename_size = file_info_.filename_size;
    //    std::cout << "filename size" << filename_size << std::endl;
    //    std::cout << "file size" << file_info_.filesize << std::endl;
    if (filename_size > k_buffer_size) {
        std::cerr << "Path name is too long!\n";
        return;
    }

    asio::async_read(socket_, asio::buffer(buffer_, file_info_.filename_size),
                     boost::bind(&Client::handle_file, shared_from_this(), asio::placeholders::error));
}

void Client::handle_file(const Client::Error &error)
{
    //    std::cout << "\nhandle_file\n" << std::endl;
    if (error) return print_asio_error(error);
    std::cout << "file path: " << buffer_ << std::endl;

    //获得文件名

    const char *basename = buffer_ + file_info_.filename_size - 1;
    while (basename >= buffer_ && (*basename != '\\' && *basename != '/')) --basename;
    ++basename;

    std::cout << "Open file: " << basename << " (" << buffer_ << ")\n" << std::endl;

    if(save_status == 0){
        fp_ = fopen(basename, "w");
        if (fp_ == NULL) {
            std::cerr << "Failed to open file to write\n";
            return;
        }
    }
    else{
        m_fs.open(basename);
    }
    receive_file_content();
}


void Client::receive_file_content()
{
    std::cout << "receive_file_content()" << std::endl;
    if(save_status == 0){
        socket_.async_receive(asio::buffer(buffer_, k_buffer_size),
                              boost::bind(&Client::handle_write, shared_from_this(), asio::placeholders::error,
                                          asio::placeholders::bytes_transferred));
    }
    else {
        socket_.async_receive(asio::buffer(buffer_, k_buffer_size),
                              boost::bind(&Client::handle_json, shared_from_this(), asio::placeholders::error));
    }
}

void Client::handle_json(const Client::Error &error)
{
    Json::Reader readerinfo;
    Json::Value value;
    Json::Value arrayObj;
    Json::Value new_item;
    if(save_status == 1){
        if (readerinfo.parse(buffer_, value)) {
            if (value.isArray()) {
                int nArraySize = value.size();
                for (int i=0; i<nArraySize; i++) {
                    new_item.clear();
                    new_item["songlist"] = value[i]["songlist"].asString();
                    arrayObj.append(new_item);
                }
            }
        }
        save_status = 0;
    }
    if(save_status == 2){
        if (readerinfo.parse(buffer_, value)) {
            if (value.isArray()) {
                int nArraySize = value.size();
                for (int i=0; i<nArraySize; i++) {
                    new_item.clear();
                    new_item["name"]= value[i]["name"].asString();
                    new_item["singer"] = value[i]["singer"].asString();
                    new_item["album"] = value[i]["album"].asString();
                    new_item["duration"] = value[i]["duration"].asString();
                    new_item["size"] = value[i]["size"].asString();
                    new_item["source"]= value[i]["source"].asString();
                    new_item["lyric"] = value[i]["lyric"].asString();
                    arrayObj.append(new_item);
                }
            }
        }
        save_status = 0;
    }
    m_fs << arrayObj.toStyledString();
    m_fs.close();
}


void Client::handle_write(const Client::Error &error, size_t bytes_transferred)
{
    if (error) {
        if (error != asio::error::eof){
            return print_asio_error(error);
        }
        Size_type filesize = file_info_.filesize;
        if (total_bytes_writen_ != filesize)
            std::cerr <<  "Filesize not matched! " << total_bytes_writen_
                       << "/" << filesize << "\n";
        if(error == asio::error::eof)
            std::cout << "file end" << std::endl;
        return;
    }

    total_bytes_writen_ += fwrite(buffer_, 1, bytes_transferred, fp_);

    receive_file_content();
}

void Client::sendFile(const char *filename)
{
    //打开文件
    fp_ = fopen(filename, "r");
    if (fp_ == NULL) {
        std::cerr << "cannot open file\n" << filename;
        return;
    }

    //使用智能指针，防止程序出现异常时，fclose未被调用。
    boost::shared_ptr<FILE> file_ptr(fp_, fclose);

    clock_t cost_time = clock();

    //文件名大小
    int filename_size  = strlen(filename) + 1;
    //文件信息大小
    size_t file_info_size = sizeof(file_info_);
    //文件总大小
    size_t total_size = file_info_size + filename_size;
    if (total_size > k_buffer_size) {
        std::cerr << "File name is too long";
        return;
    }

    file_info_.filename_size = filename_size;

    //重定位流
    //fseek：是把文件指针指向文件的开头
    fseek(fp_, 0, SEEK_END);
    //ftell函数用于得到文件位置指针当前位置相对于文件首的偏移字节数
    //得到文件大小
    file_info_.filesize = ftell(fp_);
    //使文件fp的位置指针指向文件开始
    rewind(fp_);

    //由file_info所指内存区域复制file_info_size个字节到buffer所指内存区域。
    memcpy(buffer_, &file_info_, file_info_size);
    memcpy(buffer_ + file_info_size, filename, filename_size);

    char *fn = buffer_ + file_info_size;
    std::cout << "Sending file : " << fn << "\n";
    size_t len = total_size;
    unsigned long long total_bytes_read = 0;

    //传输文件
    while (true) {
        //传输文件
        socket_.send(asio::buffer(buffer_, len), 0);
        if (feof(fp_)) break;
        //将文件写入流中
        len = fread(buffer_, 1, k_buffer_size, fp_);
        total_bytes_read += len;
    }

    std::cout << "send finish" << std::endl;

    cost_time = clock() - cost_time;
    if (cost_time == 0) cost_time = 1;
    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
    std::cout << "cost time: " << cost_time / (double) CLOCKS_PER_SEC  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";

}
