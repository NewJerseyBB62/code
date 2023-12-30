#ifndef _USRPBJSON_H_
#define _USRPBJSON_H_

#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"

namespace usr
{
    static bool pbToJson(const ::google::protobuf::Message& p_msg, std::string& p_json)
    {
        ::google::protobuf::util::JsonOptions op;
        op.add_whitespace = true;
        op.always_print_primitive_fields = true;
        op.always_print_enums_as_ints = false;
        op.preserve_proto_field_names = true;

        return ::google::protobuf::util::MessageToJsonString(p_msg, &p_json, op).ok();
    }

    static bool jsonToPb(const std::string& p_json, ::google::protobuf::Message& p_msg)
    {
        return ::google::protobuf::util::JsonStringToMessage(p_json, &p_msg).ok();
    }
};

#endif //_USRPBJSON_H_