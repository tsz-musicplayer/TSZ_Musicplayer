#include "session.h"
#include "mydb.h"
#include "myJson.h"

Session::Session(asio::io_service &io/*, MyDB* mydb*/)
    : socket_(io), fp_(NULL), total_bytes_writen_(0)/*, db_(mydb)*/
{
}
Session::~Session()
{
    std::cout << "\n ~session \n" << std::endl;
    if (fp_) fclose(fp_);
    clock_ = clock() - clock_;
    Size_type bytes_writen = total_bytes_writen_;
    if (clock_ == 0) clock_ = 1;
    //    double speed = bytes_writen * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / clock_ ;
    //    std::cout << "cost time: " << clock_ / (double) CLOCKS_PER_SEC << " s  "
    //              << "bytes_writen: " << bytes_writen << " bytes\n"
    //              << "speed: " <<  speed << " MB/s\n\n";
}

void Session::receive_service()
{
    size_t message_size;

    //接收请求
    asio::async_read(socket_, asio::buffer(buffer_, message_max_size), boost::bind(&Session::do_service, shared_from_this(), asio::placeholders::error));
}

void Session::do_service(const Error& error)
{
    std::cout << "message: " << buffer_ << std::endl;
    if(strcmp(buffer_, "login") == 0){
        login();
    } else if(strcmp(buffer_, "registe") == 0){
        registe();
    } else if ((strcmp(buffer_, "upload") == 0)) {
        receive();
    } else if ((strcmp(buffer_, "download") == 0)) {
        send();
    } else if(strcmp(buffer_, "online") == 0){
        //发送在线歌单list
        onlineSonglist();
    } else if(strcmp(buffer_, "songlist") == 0){
        //发送在线歌单
        sendSonglist();
    } else if(strcmp(buffer_, "custom") == 0){
        //接收用户自定义歌单
    }
    //std::cout << "do_service end" << std::endl;
    return;

//    receive_service();
}

void Session::login()
{
    socket_.receive(asio::buffer(buffer_, id_max_size));
    std::string id = buffer_;
    socket_.receive(asio::buffer(buffer_, password_max_size));
    std::string password = buffer_;

    std::cout << "login id: " << id << std::endl;
    std::cout << "login ps: " << password << std::endl;
    MyDB db;
    db.initDB();
    db.createPassworddbTable();

    db.queryUserInfo(id, password);
    if(db.queryUserInfo(id, password)){
        std::cout << "login true: " << id << std::endl;
        socket_.send(asio::buffer("true", result));
    } else {
        std::cout << "login false: " << id << std::endl;
        socket_.send(asio::buffer("false", result));
    }
    std::cout << buffer_ << std::endl;

    //return;
}

void Session::registe()
{
    socket_.receive(asio::buffer(buffer_, id_max_size));
    std::string id = buffer_;
    socket_.receive(asio::buffer(buffer_, id_max_size));
    std::string password = buffer_;

    std::cout << "registe id: " << id << std::endl;
    std::cout << "registe ps: " << password << std::endl;

    MyDB db;
    db.initDB();
    db.createPassworddbTable();
    if(db.saveUserInfo(id, password)){
        socket_.send(asio::buffer("true", result));
    } else {
        socket_.send(asio::buffer("false", result));
    }

}

void Session::receive()
{
    clock_ = clock();
    std::cout << "client: " << socket_.remote_endpoint().address() << "\n";
    //接收头信息
    socket_.async_receive(
                asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
                boost::bind(&Session::handle_header, shared_from_this(), asio::placeholders::error));
}

void Session::send()
{
    socket_.receive(asio::buffer(buffer_, download_path_max_size));
    std::string filename = buffer_;
    std::cout << "receive path: " << filename << std::endl;

    sendFile(filename.data());
}


void Session::handle_header(const Session::Error &error)
{
    //    std::cout << "\nhandle_header\n" << std::endl;
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
    //    std::cout << "\nhandle_file\n" << std::endl;
    if (error) return print_asio_error(error);
    //    std::cout << "file name: " << buffer_ << std::endl;

    //获得文件名
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

void Session::receive_file_content()
{
    socket_.async_receive(asio::buffer(buffer_, k_buffer_size),
                          boost::bind(&Session::handle_write, shared_from_this(), asio::placeholders::error,
                                      asio::placeholders::bytes_transferred));
}

void Session::handle_write(const Session::Error &error, size_t bytes_transferred)
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

void Session::onlineSonglist()
{
    std::string filename = getSonglistLab("Online");
    std::cout << filename << std::endl;
    sendFile(filename.data());
    //发送文件
}

void Session::sendSonglist()
{
    //接收歌单名
    socket_.receive(asio::buffer(buffer_, download_path_max_size));
    std::string filename = buffer_;
    std::cout << "receive path: " << buffer_ << std::endl;
    MyJson mjson;
    std::vector<stru_music> data;

    //获取data
    MyDB db;
    db.initDB();

    data = db.querysongList(filename);

    std::string path = mjson.packageSonglistJson(data, filename);
    //生成json
    std::cout << "path" << path << std::endl;
    //传输json
    sendFile(path.data());
}

std::string Session::getSonglistLab(std::string songlistName)
{
    std::vector<std::string> songlistLab;

    MyDB db;
    db.initDB();

    songlistLab = db.querysongListLab(songlistName);
    std::cout << "online size: " << songlistLab.size() << std::endl;
    for(auto &s: songlistLab){
        std::cout << s << std::endl;
    }
    MyJson mjson;
    std::string path = mjson.packageSonglistLabJson(songlistLab, songlistName);

    return path;
}

void Session::sendFile(const char *filename)
{
    std::cout <<"send file path: " << filename << std::endl;

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

    //memcpy(buffer_, filename, filename_size);

    //    std::cout << "filename: " << filename << std::endl;
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
