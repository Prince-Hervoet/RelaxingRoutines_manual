#include "util.hpp"

long long getNowTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    long long ll_timestamp = static_cast<long long>(timestamp);
    return timestamp;
}