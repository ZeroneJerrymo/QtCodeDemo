#ifndef TESTUILIB_GLOBAL_H
#define TESTUILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TESTUILIB_LIBRARY)
#  define TESTUILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TESTUILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTUILIB_GLOBAL_H
