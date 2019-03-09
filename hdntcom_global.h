#ifndef HDNTCOM_GLOBAL_H
#define HDNTCOM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HDNTCOM_LIBRARY)
#  define HDNTCOMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HDNTCOMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HDNTCOM_GLOBAL_H
