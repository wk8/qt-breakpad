HEADERS += $$PWD/qt_breakpad.h
SOURCES += $$PWD/qt_breakpad.cpp

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/vendor/breakpad/src

# Windows
win32:HEADERS += $$PWD/vendor/breakpad/src/common/windows/string_utils-inl.h
win32:HEADERS += $$PWD/vendor/breakpad/src/common/windows/guid_string.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/handler/exception_handler.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/common/ipc_protocol.h
win32:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h
win32:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/crash_generation/crash_generation_client.h
win32:HEADERS += $$PWD/vendor/breakpad/src/common/scoped_ptr.h
win32:SOURCES += $$PWD/vendor/breakpad/src/client/windows/handler/exception_handler.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/common/windows/string_utils.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/common/windows/guid_string.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/client/windows/crash_generation/crash_generation_client.cc

# Linux
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/cpu_set.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/proc_cpuinfo_reader.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/handler/exception_handler.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/crash_generation/crash_generation_client.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/handler/minidump_descriptor.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/minidump_writer.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/line_reader.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_dumper.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/directory_reader.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/linux/log/log.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/minidump_file_writer-inl.h
unix:HEADERS += $$PWD/vendor/breakpad/src/client/minidump_file_writer.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/linux_libc_support.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/eintr_wrapper.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/ignore_ret.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/file_id.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/memory_mapped_file.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/safe_readlink.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/guid_creator.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/elfutils.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/elfutils-inl.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/linux/elf_gnu_compat.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/using_std_string.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/memory.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/basictypes.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/memory_range.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/string_conversion.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/convert_UTF.h
unix:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h
unix:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_size.h
unix:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h
unix:HEADERS += $$PWD/vendor/breakpad/src/common/scoped_ptr.h
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/crash_generation/crash_generation_client.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/handler/exception_handler.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/handler/minidump_descriptor.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/minidump_writer.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_dumper.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/linux/log/log.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/client/minidump_file_writer.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/linux_libc_support.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/file_id.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/memory_mapped_file.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/safe_readlink.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/guid_creator.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/linux/elfutils.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/string_conversion.cc
unix:SOURCES += $$PWD/vendor/breakpad/src/common/convert_UTF.c

## breakpad needs debug info inside binaries

win32-msvc* {
    # generate the symbol file
    QMAKE_LFLAGS_RELEASE += /MAP /debug /opt:ref
    QMAKE_CFLAGS_RELEASE += -Zi
    QMAKE_CXXFLAGS_RELEASE += -Zi
}

unix:QMAKE_CFLAGS += -g
unix:QMAKE_CXXFLAGS += -g

# prevent undue optimization, which ruins breakpad's backtrace
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
