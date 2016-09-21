#pragma once
#include <dsn/service_api_cpp.h>
#include <dsn/cpp/serialization.h>


#include "log_monitor_types.h"


namespace dsn { namespace tools { 
    GENERATED_TYPE_SERIALIZATION(log_monitor_entry, THRIFT)

    DEFINE_TASK_CODE_RPC(RPC_LOG_MONITOR_REPORT, TASK_PRIORITY_HIGH, THREAD_POOL_DEFAULT)

} } 