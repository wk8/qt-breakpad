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
`QtBreakpad::init`.

## Analyzing the dumps

See [here](https://github.com/JPNaude/dev_notes/wiki/Using-Google-Breakpad-with-Qt).
