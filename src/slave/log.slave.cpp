/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Microsoft Corporation
 * 
 * -=- Robust Distributed System Nucleus (rDSN) -=- 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Description:
 *     the tracer toollets traces all the asynchonous execution flow
 *     in the system through the join-point mechanism
 *
 * Revision history:
 *     May, 2016, @imzhenyu (Zhenyu Guo), first version
 *     xxxx-xx-xx, author, fix bug about xxx
 */


# include "log.slave.h"
# include <dsn/utility/ports.h>
# include <dsn/service_api_cpp.h>
# include "../common/log_monitor.types.h"

namespace dsn 
{
    namespace tools 
    {
        log_monitor_slave::log_monitor_slave(const char* dir, logging_provider* inner)
            : logging_provider(dir, inner), _inner(inner)
        {
            _master.set_invalid();

            std::string master = dsn_config_get_value_string(
                "tools.log.monitor",
                "master",
                "",
                "address of log monitor master, can be host:port, ip:port or service url"
            );
            
            _master = url_host_address(master.c_str());
        
            dassert(!_master.is_invalid(),
                "invalid log monitor master address '%s'",
                master.c_str()
            );

            dinfo("setup log monitor master to '%s'", master.c_str());
        }

        __thread bool s_log_monitor_run = false;
        void log_monitor_slave::dsn_logv(const char *file, const char *function, const int line, dsn_log_level_t log_level, const char* title, const char* fmt, va_list args)
        {
            if (s_log_monitor_run)
                return;

            s_log_monitor_run = true;

            // redirect
            if (log_level >= LOG_LEVEL_WARNING 
                && ::dsn::task::get_current_rpc()
                )
            {
                log_monitor_entry entry;
                entry.file = file;
                entry.line = line;
                entry.func = function;
                entry.level = log_level;
                
                va_list args2;
                va_copy(args2, args);

                char buffer[1024]; 
                
                int c = std::vsnprintf(buffer, sizeof(buffer) / sizeof(char),
                    fmt, args2
                );

                if (c < 0) c = 0;
                else if (c >= 1023) c = 1023;
                buffer[c] = '\0';

                entry.log = buffer;

                rpc::call_one_way_typed(_master, RPC_LOG_MONITOR_REPORT, entry);
            }

            _inner->dsn_logv(file, function, line, log_level, title, fmt, args);

            s_log_monitor_run = false;
        }

    }
}