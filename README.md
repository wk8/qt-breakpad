Credit goes to [JPNaude](https://github.com/JPNaude/dev_notes/wiki/Using-Google-Breakpad-with-Qt)

# Qt Breakpad

A little wrapper around [Google's
Breakpad](https://chromium.googlesource.com/breakpad/breakpad/) to
be used in [Qt5](http://www.qt.io/) projects, to make it platform-independent.

For now, only supports Linux and Windows (please open an issue, or even better,
a pull request, to support other OSes).

## Usage

Checkout this repo in your app's folder, e.g. (but not
necessarily) as a submodule (and the path is up to you, too):

```bash
git submodule add git@github.com:wk8/qt-breakpad.git qt-breakpad
git submodule update --init --recursive
```

In your Qt project's `*.pro` file, include `qt-breakpad`'s `pri` file:
```
include(qt-breakpad/qt-breakpad.pri)
```

In your application's `main`, before doing anything else, initialize the handler:

```cpp
#include "qt_breakpad.h"

int main(int argc, char *argv[]) {
    QString reportPath = QDir::current().absolutePath(); // or whatever else you want, but it must exist
    QtBreakpad::init(reportPath);

    // ... your app's code starts here

    return 0;
}
```

Now if your app crashes, a `dmp` file will be generated in the given path.

If you want to send the said dump to some server, you can do
that by passing a
`google_breakpad::ExceptionHandler::MinidumpCallback` to
`QtBreakpad::init`; or keep reading!

## Real-life example

We also provide a wrapper around
`google_breakpad::ExceptionHandler::MinidumpCallback`s in the
usual case where you simply want to access the minidump file to
send it; that's
```cpp
typedef bool (*QMinidumpCallback)(QFile& minidumpFile, void* context);
```
that can be passed a second argument to `QtBreakpad::init`.

It should return `true` if and only if it has successfully done
its job (in which case no further Breakpad handlers that might
have been defined will be called).

A more complicated example than above, that uses context object,
and retrieves the contents of the minidump file and encodes it to
base 64:

```cpp
#include "qt_breakpad.h"

class MyContext
{
  public:
    QDateTime appStartedAt;
}

bool myQtBreakpadCallback(QFile &minidumpFile, void* context)
{
  MyContext* myContext = (MyContext*) context;

  QFileInfo fileInfo(minidumpFile);

  qDebug("From myQtBreakpadCallback; minidump file at " + fileInfo.absoluteFilePath());
  qDebug("My app had started at " + myContext->appStartedAt.toString());

  minidumpFile.open(QIODevice::ReadOnly);
  QByteArray rawMinidumpContent = minidumpFile.readAll();
  QString minidumpContent = rawMinidumpContent.toBase64();

  // ... actually upload it somewhere

  return true;
}

int main(int argc, char *argv[]) {
    QString reportPath = QDir::current().absolutePath(); // or whatever else you want, but it must exist

    MyContext myContext;
    myContext.appStartedAt = QDateTime::currentDateTimeUtc();

    QtBreakpad::init(reportPath, myQtBreakpadCallback, &myContext);

    // ... your app's code starts here

    return 0;
}
```

## Analyzing the dumps

See [here](https://github.com/JPNaude/dev_notes/wiki/Using-Google-Breakpad-with-Qt).
