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
 *     this is a log monitor master that receives
 *     critical logs from remote log monitor slaves
 *
 * Revision history:
 *     Sep., 2016, @imzhenyu (Zhenyu Guo), first version
 *     xxxx-xx-xx, author, fix bug about xxx
 */


# include <dsn/utility/module_init.cpp.h>
# include "../common/log_monitor.types.h"

namespace dsn
{
    namespace tools
    {
        class log_monitor_master : 
            public service_app,
            public serverlet<log_monitor_master>
        {
        public:
            log_monitor_master(dsn_gpid gpid)
                : service_app(gpid), serverlet<log_monitor_master>("log.monitor.master")
            {
            }

            virtual ~log_monitor_master(void) {}

            ::dsn::error_code start(int argc, char** argv) override
            {
                register_rpc_handler(
                    RPC_LOG_MONITOR_REPORT,
                    "rpc.log.monitor.report",
                    &log_monitor_master::on_log_entry
                );
                return ERR_OK;
            }

            ::dsn::error_code stop(bool cleanup = false) override
            {                
                unregister_rpc_handler(RPC_LOG_MONITOR_REPORT);
                return ERR_OK;
            }

            void on_log_entry(dsn_message_t req)
            {
                rpc_address from(dsn_msg_from_address(req));
                log_monitor_entry log;
                ::dsn::unmarshall(req, log);

                printf("[%c @ %s] %s (%s:%s:%d)\n",
                    log.level == LOG_LEVEL_WARNING ? 'w':'e',
                    from.to_string(),
                    log.log.c_str(),
                    log.file.c_str(),
                    log.func.c_str(),
                    log.line
                    );

                dinfo("[%c @ %s] %s (%s:%s:%d)",
                    log.level == LOG_LEVEL_WARNING ? 'w' : 'e',
                    from.to_string(),
                    log.log.c_str(),
                    log.file.c_str(),
                    log.func.c_str(),
                    log.line
                );
            }
        };
    }
}

MODULE_INIT_BEGIN(tools_explorer)
    ::dsn::register_app< dsn::tools::log_monitor_master>("log.monitor.master");
MODULE_INIT_END
