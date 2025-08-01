#ifndef BUFFER_H
#define BUFFER_H
#include<iostream>
#include<string> //cstring
#include<unistd.h>
#include<winsock2.h> //windows用winsock2, linux用sys/uio.h
#include<vector>
#include<atomic>
#include<assert.h>
using namespace std;

class Buffer
{
    public:
    Buffer(int initBuffSize = 1024);
    ~Buffer() = default;

    size_t WritableBytes() const; //const作用：保证对象的变量状态不会被这个函数改变，适合只读操作。
    size_t ReadableBytes() const;
    size_t PrependableBytes() const;

    const char* Peel() const;
    void EnsureWritebale(size_t len);
    void HasWritten(size_t len);

    void Retrieve(size_t len);
    void RetrieveUntil(const char* end);

    void RetrieveAll();
    string RetrieveALLToStr();

    const char* BeginWriteConst() const;
    char* BeginWrite();

    void Append(const string& str);
    void Append(const char* str, size_t len);
    void Append(const void* data, size_t len);
    void Append(const Buffer& buff);

    ssize_t ReadFd(int fd, int* Errno);
    ssize_t WriteFd(int fd, int* Errno);

    private:
    char* BeginPtr_();
    const char* BeginPtr_() const;
    void MakeSpace_(size_t len);

    vector<char> buffer_;
    atomic<size_t> readPos_;
    atomic<size_t> writePos_;


};



#endif