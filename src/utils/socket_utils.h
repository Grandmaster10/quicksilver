#pragma once
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

namespace utils {
    inline bool non_blocking(int fd) {
        int flag = fcntl(fd, F_GETFL, 0);
        if (flag == -1) return false;
        return fcntl(fd, F_SETFL, flag | O_NONBLOCK) != -1;
    }

    inline bool dis_nagle(int fd) {
        int flag = 1;
        return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) == 0;
    } 
}