/********************************************
* FileName: MyLogger.h
* Author: 覃光垚
* Version: 3.2
* Date: 2024-08-10
* Description: 调用log4cpp库，定义Logger类，进行日志撰写并输出文件操作，日志信息包括记录时间、事件类型和具体情况，
*     如需调用，无需在代码前部进行类的实例化，直接在写入日志的地方添加语句 Logger::notice("###");
*     其中 Logger为类名，notice可替换为其他事件类型，###为事件的具体情况，
*     可修改最低日志信息记录级别。会在根目录自动生成一个 log 文件夹存放每次运行程序的单独日志文件，
*     格式为 log_年-月-日_时-分-秒.log 
*     注意：若出现问题，请尝试将类的定义部分单独新建一个 cpp 源文件，并包含该头文件。
* Function List：
* 1. static Logger& getInstance();
*     用于获取Logger类的单例实例，确保整个程序生命周期中只有一个实例
* 2. static void warn(const std::string& sMessage);等
*     通过调用该函数可以在日志中记录相应级别的信息，此处为warn，其余见具体函数示例
* History:
* 覃光垚 24/06/27 1.0 创建该类 Logger，可将所有信息写入同一日志文件 log_test.log
* 覃光垚 24/06/28 2.0 增加 按照程序运行时的时间生成对应名称日志文件的功能，每次程序运行生成单独日志文件
* 覃光垚 24/08/03 2.1 日志文件将被指定存放于根目录的 log 文件夹内，同时优化了部分注释
* 覃光垚 24/08/03 3.0 使用静态成员函数访问单例实例，而不是定义全局变量，无需在代码前进行类的实例化，
*                    包含头文件后直接通过 Logger::debug("Messages") 即可直接使用日志功能。
*                    (依然支持旧的日志方法，即在使用前实例化类，但不推荐使用，会出现重复定义的问题)
* 覃光垚 24/08/03 3.1 使用 _mkdir 语句，若根目录不存在 log 文件夹则会创建一个
* 覃光垚 24/08/10 3.2 删除了不安全的 localtime 语句，使用 localtime_s 替代
********************************************/
#ifndef MYLOGGER_H
#define MYLOGGER_H

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <string>
#include <iomanip>
#include <direct.h> // _mkdir

class Logger {
public:
    //获取Logger类的单例实例
    static Logger& getInstance();
    
    //按级别排序
    static void debug(const std::string& sMessage);
    static void info(const std::string& sMessage);
    static void notice(const std::string& sMessage);
    static void warn(const std::string& sMessage);
    static void error(const std::string& sMessage);
    static void crit(const std::string& sMessage);
    static void alert(const std::string& sMessage);
    static void fatal(const std::string& sMessage);

private:
    Logger();   //构造函数，设置日志记录格式
    ~Logger();  //析构函数，关闭日志系统
    //删除类的拷贝构造函数和赋值运算符,防止类的实例被复制或赋值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    log4cpp::Category& cCategory;
};



#endif // MYLOGGER_H
