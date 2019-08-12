/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef _HOME_KORY_DEV_PROG_CPP_BUILD_IRODS_LIB_CORE_INCLUDE_SERVER_CONTROL_PLANE_COMMAND_HPP_136904038__H_
#define _HOME_KORY_DEV_PROG_CPP_BUILD_IRODS_LIB_CORE_INCLUDE_SERVER_CONTROL_PLANE_COMMAND_HPP_136904038__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace irods {
struct control_plane_command {
    std::string command;
    std::map<std::string, std::string > options;
    control_plane_command() :
        command(std::string()),
        options(std::map<std::string, std::string >())
        { }
};

}
namespace avro {
template<> struct codec_traits<irods::control_plane_command> {
    static void encode(Encoder& e, const irods::control_plane_command& v) {
        avro::encode(e, v.command);
        avro::encode(e, v.options);
    }
    static void decode(Decoder& d, irods::control_plane_command& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.command);
                    break;
                case 1:
                    avro::decode(d, v.options);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.command);
            avro::decode(d, v.options);
        }
    }
};

}
#endif
