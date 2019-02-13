#ifndef __BAN_20190202_DATA_PACKAGE_EASY_HEADER_H__
#define __BAN_20190202_DATA_PACKAGE_EASY_HEADER_H__

enum PackageType {
    LOGIN_PACK,
    LOGOUT_PACK,
    EXIT_PACK,
    TYPE_LEN
}

class EasyHeader
{

public:
    PackageType body_type;
    unsigned int body_size;

public:
    static unsigned int headerSize()
    {
        return sizeof(EasyHeader);
    }
};


class EasyBody
{
public:
    std::string txt_content;

public:
    int size()
    {
        this->txt_content.size();
    }
};


class EasyPackage
{

public:
    EasyHeader header;
    EasyBody body;

};

#endif