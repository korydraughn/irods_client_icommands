#ifndef IRODS_ICOMMANDS_UTILITY_HPP
#define IRODS_ICOMMANDS_UTILITY_HPP

#include "rodsDef.h"
#include "rcConnect.h"
#include "client_properties.hpp"

#include <cstdlib>
#include <string_view>
#include <iostream>
#include <sstream>

namespace utils
{
    inline auto set_ips_display_name(const std::string_view _display_name) -> void
    {
        // Setting this environment variable is required so that "ips" can display
        // the command name alongside the connection information.
        if (setenv(SP_OPTION, _display_name.data(), /* overwrite */ 1)) {
            std::cout << "Warning: Could not set environment variable [spOption] for ips.";
        }
    } // set_ips_display_name

    inline auto store_server_version_in_client_properties(const RcComm& _comm) noexcept -> void
    {
        try {
            std::istringstream in{_comm.svrVersion->relVersion};

            irods::version version;
            in.ignore(4) >> version.major;
            in.ignore(1) >> version.minor;
            in.ignore(1) >> version.patch;

            irods::client_properties[irods::server_version] = version;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    } // store_server_version_in_client_properties
} // namespace utils

#endif // IRODS_ICOMMANDS_UTILITY_HPP

