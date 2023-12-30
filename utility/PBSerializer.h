#pragma once
#include "SrodError.pb.h"


template<class T>
class PBSerializer
{
public:
    static int ParseFromArray(T& msg, void* pBuf, int length)
    {
        if (pBuf == nullptr)
            return Srod::Error::SROD_ERR_INVALID_PARAM;
        int ret = Srod::Error::SROD_ERR_SUCCESS;
        bool ok = msg.ParseFromArray(pBuf, length);
        if (!ok)
            ret = Srod::Error::SROD_ERR_FAILED;
        return ret;
    }
    static int SerializeToArray(T& msg, void* pBuf, int* length)
    {
        if (pBuf == nullptr || length == nullptr)
            return Srod::Error::SROD_ERR_INVALID_PARAM;
        int ret = Srod::Error::SROD_ERR_SUCCESS;
        bool ok = true;
        int size = msg.ByteSizeLong();
        if (*length >= size)
        {
            ok = msg.SerializeToArray(pBuf, *length);
            if (!ok)
                ret = Srod::Error::SROD_ERR_FAILED;
        }
        else
            ret = Srod::Error::SROD_ERR_NOT_ENOUGH_BUF;
        *length = size;
        return ret;
    }

};

