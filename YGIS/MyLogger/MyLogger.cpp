/********************************************
* ATTENTION：
* 若出现问题，必要时请将下面类的定义部分代码全部剪切至新的 cpp 源文件，
* 并包含该头文件，请勿将最末尾的头文件保护符删除： #endif // MYLOGGER_H
********************************************/

#include "MyLogger/MyLogger.h"

Logger::Logger()
    : cCategory(log4cpp::Category::getRoot().getInstance("logCat")) {
    ////创建 FileAppender 对象，用于将日志输出到文件 log_test.log
    //log4cpp::FileAppender* pfFileAppender = new log4cpp::FileAppender("FileAppender", "log_test.log");

    //获取当前日期和时间
    //std::time_t tNow = std::time(nullptr);
    //std::tm* tNowTm = std::localtime_s(&tNow);
    std::time_t tNow = std::time(nullptr);
    std::tm tNowTm;
    localtime_s(&tNowTm, &tNow);

    //创建 log 文件夹（如果不存在）
    if (_mkdir("log") != 0 && errno != EEXIST) {
        std::cerr << "Error creating log directory!" << std::endl;
    }

    //格式化日期和时间作为文件名
    std::ostringstream oStrStream;
    oStrStream << "log/log_" << std::put_time(&tNowTm, "%Y-%m-%d_%H-%M-%S") << ".log";
    std::string sFileName = oStrStream.str();

    //创建 FileAppender 对象，用于将日志输出到动态生成的文件
    log4cpp::FileAppender* pfFileAppender = new log4cpp::FileAppender("FileAppender", sFileName);

    //创建 PatternLayout 对象，用于定义日志的输出格式
    log4cpp::PatternLayout* pPatternLayout = new log4cpp::PatternLayout();
    pPatternLayout->setConversionPattern("%d: %p %c %x: %m%n");
    pfFileAppender->setLayout(pPatternLayout);

    //为日志类别 cCategory 添加 Appender
    cCategory.addAppender(pfFileAppender);
    //设置日志输出的最低优先级为 DEBUG
    cCategory.setPriority(log4cpp::Priority::DEBUG); //可修改，DEBUG为最低级别
}

//关闭日志系统
Logger::~Logger() {
    log4cpp::Category::shutdown();
}

//获取Logger类的单例实例
Logger& Logger::getInstance() {
    static Logger lInstance;
    return lInstance;
}

void Logger::debug(const std::string& sMessage) {
    Logger::getInstance().cCategory.debug(sMessage);
}

void Logger::info(const std::string& sMessage) {
    Logger::getInstance().cCategory.info(sMessage);
}

void Logger::notice(const std::string& sMessage) {
    Logger::getInstance().cCategory.notice(sMessage);
}

void Logger::warn(const std::string& sMessage) {
    Logger::getInstance().cCategory.warn(sMessage);
}

void Logger::error(const std::string& sMessage) {
    Logger::getInstance().cCategory.error(sMessage);
}

void Logger::crit(const std::string& sMessage) {
    Logger::getInstance().cCategory.crit(sMessage);
}

void Logger::alert(const std::string& sMessage) {
    Logger::getInstance().cCategory.alert(sMessage);
}

void Logger::fatal(const std::string& sMessage) {
    Logger::getInstance().cCategory.fatal(sMessage);
}

/********************************************
* ATTENTION：
* 以上代码为类的定义部分，必要时请剪切至源文件
********************************************/