#include "qt_breakpad.h"

QtBreakpad* QtBreakpad::_instance = NULL;

void QtBreakpad::init(const QString& reportPath,
                      google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
                      google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
                      void* callbackContext)
{
    QtBreakpad::replaceInstance(new QtBreakpad(reportPath, filterCallBack,
                                               minidumpCallback, callbackContext));
}

void QtBreakpad::init(const QString& reportPath,
                      QMinidumpCallback qMinidumpCallback,
                      void* callbackContext)
{
    QtBreakpad::replaceInstance(new QtBreakpad(reportPath, qMinidumpCallback, callbackContext));
}

QtBreakpad::QtBreakpad(const QString& reportPath,
                       google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
                       google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
                       void* callbackContext)
{
    this->buildBreakpadHandler(reportPath, filterCallBack, minidumpCallback, callbackContext);
}

void QtBreakpad::buildBreakpadHandler(const QString& reportPath,
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

QtBreakpad::QtBreakpad(const QString& reportPath,
           QMinidumpCallback qMinidumpCallback,
           void* callbackContext)
{
    this->_qMinidumpContextWrapper = new QtBreakpad::QMinidumpContextWrapper(qMinidumpCallback, callbackContext);

    this->buildBreakpadHandler(reportPath,
                               NULL, // filter callback
                               reinterpret_cast<google_breakpad::ExceptionHandler::MinidumpCallback>(&QtBreakpad::qMinidumpWrapper),
                               this->_qMinidumpContextWrapper);
}

#if defined(Q_OS_WIN32)
bool QtBreakpad::qMinidumpWrapper(const wchar_t* dump_path,
                                  const wchar_t* minidump_id,
                                  QMinidumpContextWrapper* contextWrapper,
                                  EXCEPTION_POINTERS* exinfo,
                                  MDRawAssertionInfo* assertion,
                                  bool succeeded)
{
    Q_UNUSED(exinfo);
    Q_UNUSED(assertion);
#elif defined(Q_OS_LINUX)
bool QtBreakpad::qMinidumpWrapper(const MinidumpDescriptor& descriptor,
                                  QMinidumpContextWrapper* contextWrapper,
                                  bool succeeded)
{
#endif
    // if there's no dump file, not much to do
    if (!succeeded) { return false; }

    QMinidumpCallback qMinicudmpCallback = contextWrapper->qMinicudmpCallback;
    void* context = contextWrapper->context;

    QString minidumpFileName;

#if defined(Q_OS_WIN32)
    QDir minidumpDir = QDir(QString::fromWCharArray(dump_path));
    minidumpFileName = minidumpDir.absoluteFilePath(QString::fromWCharArray(minidump_id) + ".dmp");
#elif defined(Q_OS_LINUX)
    minidumpFileName = descriptor.path();
#endif

    QFile minidumpFile(minidumpFileName);

    return qMinicudmpCallback(minidumpFile, context);
}

void QtBreakpad::replaceInstance(QtBreakpad* newInstance)
{
    // there can only be one handler
    delete QtBreakpad::_instance;

    QtBreakpad::_instance = newInstance;
}

QtBreakpad::~QtBreakpad()
{
    delete this->_breakpad_handler;
    delete this->_qMinidumpContextWrapper;
}
