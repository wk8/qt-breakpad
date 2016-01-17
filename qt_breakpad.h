#ifndef QT_BREAKPAD_H
#define QT_BREAKPAD_H

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QString>

#if defined(Q_OS_WIN32)
// breakpad includes windows.h, so we must include QT's qt_windows.h beforehand
// to avoid breaking other QT headers
#include <qt_windows.h>

#include "vendor/breakpad/src/client/windows/handler/exception_handler.h"

#elif defined(Q_OS_LINUX)
#include "vendor/breakpad/src/client/linux/handler/exception_handler.h"

#endif // OS-specific includes

class QtBreakpad
{
public:
    static void init(const QString& reportPath,
                     google_breakpad::ExceptionHandler::FilterCallback filterCallBack = NULL,
                     google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback = NULL,
                     void* callbackContext = NULL);

private:
    Q_DISABLE_COPY(QtBreakpad)
    static QtBreakpad* _instance;

    QtBreakpad(const QString& reportPath,
               google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
               google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
               void* callbackContext);
    ~QtBreakpad();

    google_breakpad::ExceptionHandler* _breakpad_handler;
};

#endif // QT_BREAKPAD_H
