/********************************************
* ATTENTION��
* ���������⣬��Ҫʱ�뽫������Ķ��岿�ִ���ȫ���������µ� cpp Դ�ļ���
* ��������ͷ�ļ���������ĩβ��ͷ�ļ�������ɾ���� #endif // MYLOGGER_H
********************************************/

#include "MyLogger/MyLogger.h"

Logger::Logger()
    : cCategory(log4cpp::Category::getRoot().getInstance("logCat")) {
    ////���� FileAppender �������ڽ���־������ļ� log_test.log
    //log4cpp::FileAppender* pfFileAppender = new log4cpp::FileAppender("FileAppender", "log_test.log");

    //��ȡ��ǰ���ں�ʱ��
    //std::time_t tNow = std::time(nullptr);
    //std::tm* tNowTm = std::localtime_s(&tNow);
    std::time_t tNow = std::time(nullptr);
    std::tm tNowTm;
    localtime_s(&tNowTm, &tNow);

    //���� log �ļ��У���������ڣ�
    if (_mkdir("log") != 0 && errno != EEXIST) {
        std::cerr << "Error creating log directory!" << std::endl;
    }

    //��ʽ�����ں�ʱ����Ϊ�ļ���
    std::ostringstream oStrStream;
    oStrStream << "log/log_" << std::put_time(&tNowTm, "%Y-%m-%d_%H-%M-%S") << ".log";
    std::string sFileName = oStrStream.str();

    //���� FileAppender �������ڽ���־�������̬���ɵ��ļ�
    log4cpp::FileAppender* pfFileAppender = new log4cpp::FileAppender("FileAppender", sFileName);

    //���� PatternLayout �������ڶ�����־�������ʽ
    log4cpp::PatternLayout* pPatternLayout = new log4cpp::PatternLayout();
    pPatternLayout->setConversionPattern("%d: %p %c %x: %m%n");
    pfFileAppender->setLayout(pPatternLayout);

    //Ϊ��־��� cCategory ��� Appender
    cCategory.addAppender(pfFileAppender);
    //������־�����������ȼ�Ϊ DEBUG
    cCategory.setPriority(log4cpp::Priority::DEBUG); //���޸ģ�DEBUGΪ��ͼ���
}

//�ر���־ϵͳ
Logger::~Logger() {
    log4cpp::Category::shutdown();
}

//��ȡLogger��ĵ���ʵ��
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
* ATTENTION��
* ���ϴ���Ϊ��Ķ��岿�֣���Ҫʱ�������Դ�ļ�
********************************************/