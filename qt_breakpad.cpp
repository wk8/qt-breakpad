#include "qt_breakpad.h"

QtBreakpad* QtBreakpad::_instance = NULL;

void QtBreakpad::init(const QString& reportPath,
                      google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
                      google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
                      void* callbackContext)
{
    // there can only be one handler
    delete QtBreakpad::_instance;

    QtBreakpad::_instance = new QtBreakpad(reportPath, filterCallBack,
                                               minidumpCallback, callbackContext);
}

QtBreakpad::QtBreakpad(const QString& reportPath,
                       google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
                       google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
                       void* callbackContext)
{
#if defined(Q_OS_WIN32)
    std::wstring pathAsStr = (const wchar_t*)reportPath.utf16();
    this->_breakpad_handler = new google_breakpad::ExceptionHandler(
        pathAsStr,
        filterCallBack,
        minidumpCallback,
        callbackContext,
        true
    );
#elif defined(Q_OS_LINUX)
    std::string pathAsStr = reportPath.toStdString();
    google_breakpad::MinidumpDescriptor md(reportPath);
    this->_breakpad_handler = new google_breakpad::ExceptionHandler(
        md,
        filterCallBack,
        minidumpCallback,
        callbackContext,
        true,
        -1
    );
#endif
}

QtBreakpad::~QtBreakpad()
{
    delete this->_breakpad_handler;
}
