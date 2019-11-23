#ifndef GET_TIME_STAMP_HPP
#define GET_TIME_STAMP_HPP
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

std::string getTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(localtime(&now_c), "%Y%m%d_%H%M%S");
    return ss.str();
}

//----------出力例----------
//20171231_145030

//2017年12月31日 14時50分30秒のこと
#endif