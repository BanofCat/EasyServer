#ifndef __BAN_20190212_EASY_TRANSFORM_API_H__
#define __BAN_20190212_EASY_TRANSFORM_API_H__

#include "EasyPackage.h "

class EasyTransformAPI
{
    int sendPack(int fd, const EasyPackage& pack)
    {
        int ret = send(fd, (char *)&pack, sizeof(pack));
        if (ret < 0) {
            int err_no = errno;
            if (err_no == EINTR) {
                LOG_INFO_FMT("catch an %s, ignore it", strerror(err_no));
                return this->send(buf, buf_size);
            }
            LOG_ERROR_FMT("send failed, catch an error: %s", strerror(err_no));
        }
        return ret;
    }

    int recvHead(int fd, const EasyHeader& head)
    {
        int ret = recv(fd, head, sizeof(head));
        if (ret < 0) {
            int err_no = errno;
            if (err_no == EINTR) {
                LOG_INFO_FMT("catch an %s, ignore it", strerror(err_no));
                return this->send(buf, buf_size);
            }
            LOG_ERROR_FMT("recv failed, catch an error: %s", strerror(err_no));
        }
        return ret;
    }

    int recvBody(const EasyBody& body)
    {
        int ret = recv(fd, body, sizeof(body));
        if (ret < 0) {
            int err_no = errno;
            if (err_no == EINTR) {
                LOG_INFO_FMT("catch an %s, ignore it", strerror(err_no));
                return this->send(buf, buf_size);
            }
            LOG_ERROR_FMT("recv failed, catch an error: %s", strerror(err_no));
        }
        return ret;

    }

    int recvPack(const EasyPackage& pack)
    {
        int ret = recv(fd, pack, sizeof(pack));
        if (ret < 0) {
            int err_no = errno;
            if (err_no == EINTR) {
                LOG_INFO_FMT("catch an %s, ignore it", strerror(err_no));
                return this->send(buf, buf_size);
            }
            LOG_ERROR_FMT("recv failed, catch an error: %s", strerror(err_no));
        }
        return ret;
    }
};

#endif // !__BAN_20190212_EASY_TRANSFORM_API_H__