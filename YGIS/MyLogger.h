#ifndef LOGGER_H
#define LOGGER_H

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <string>

class Logger {
public:
    static Logger& getInstance();

    void debug(const std::string& sMessage);
    void info(const std::string& sMessage);
    void notice(const std::string& sMessage);
    void warn(const std::string& sMessage);
    void error(const std::string& sMessage);
    void crit(const std::string& sMessage);
    void alert(const std::string& sMessage);
    void fatal(const std::string& sMessage);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    log4cpp::Category& category;
};

Logger::Logger()
    : category(log4cpp::Category::getRoot().getInstance("logCat")) {
    //创建FileAppender对象，用于将日志输出到文件log_test.log
    log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("FileAppender", "log_test.log");

    //创建PatternLayout对象，用于定义日志的输出格式
    log4cpp::PatternLayout* patternLayout = new log4cpp::PatternLayout();
    patternLayout->setConversionPattern("%d: %p %c %x: %m%n");
    fileAppender->setLayout(patternLayout);

    //为日志类别category添加Appender
    category.addAppender(fileAppender);
    //设置日志输出的最低优先级为DEBUG
    category.setPriority(log4cpp::Priority::DEBUG);
}

//Logger类的析构函数，关闭日志系统
Logger::~Logger() {
    log4cpp::Category::shutdown();
}

//获取Logger类的单例实例
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}


void Logger::debug(const std::string& sMessage) {
    category.debug(sMessage);
}

void Logger::info(const std::string& sMessage) {
    category.info(sMessage);
}

void Logger::notice(const std::string& sMessage) {
    category.notice(sMessage);
}

void Logger::warn(const std::string& sMessage) {
    category.warn(sMessage);
}

void Logger::error(const std::string& sMessage) {
    category.error(sMessage);
}

void Logger::crit(const std::string& sMessage) {
    category.crit(sMessage);
}

void Logger::alert(const std::string& sMessage) {
    category.alert(sMessage);
}

void Logger::fatal(const std::string& sMessage) {
    category.fatal(sMessage);
}

#endif // LOGGER_H
