#include <Logger.h>

int main() {
    Logger& logger = Logger::getInstance();

    logger.notice("成功生成日志文件");
}