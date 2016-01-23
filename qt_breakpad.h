#ifndef QT_BREAKPAD_H
#define QT_BREAKPAD_H

#include <QCoreApplication>
#include <QDir>
#include <QFile>
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

    typedef bool (*QMinidumpCallback)(QFile& minidumpFile, void* context);

    static void init(const QString& reportPath,
                     QMinidumpCallback qMinidumpCallback,
                     void* callbackContext = NULL);

private:
    Q_DISABLE_COPY(QtBreakpad)
    static QtBreakpad* _instance;
    static void replaceInstance(QtBreakpad* newInstance);

    class QMinidumpContextWrapper
    {
        public:
            QMinidumpContextWrapper(QMinidumpCallback qMinicudmpCallback, void* context)
            {
                this->qMinicudmpCallback = qMinicudmpCallback;
                this->context = context;
            }

            ~QMinidumpContextWrapper() { }

            QMinidumpCallback qMinicudmpCallback;
            void* context;
    };

    QtBreakpad(const QString& reportPath,
               google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
               google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
               void* callbackContext);
    QtBreakpad(const QString& reportPath,
               QMinidumpCallback qMinidumpCallback,
               void* callbackContext);
    ~QtBreakpad();

    google_breakpad::ExceptionHandler* _breakpad_handler;
    void buildBreakpadHandler(const QString& reportPath,
                              google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
                              google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
                              void* callbackContext);

    QMinidumpContextWrapper* _qMinidumpContextWrapper;
#if defined(Q_OS_WIN32)
    static bool qMinidumpWrapper(const wchar_t* dump_path,
                                 const wchar_t* minidump_id,
                                 QMinidumpContextWrapper* context,
                                 EXCEPTION_POINTERS* exinfo,
                                 MDRawAssertionInfo* assertion,
                                 bool succeeded);
#elif defined(Q_OS_LINUX)
    static bool qMinidumpWrapper(const MinidumpDescriptor& descriptor,
                                 QMinidumpContextWrapper* context,
                                 bool succeeded);
#endif
};

#endif // QT_BREAKPAD_H
