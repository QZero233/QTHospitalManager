#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <QString>

using namespace std;

class TimeUtils
{
public:
    TimeUtils();

    static QString formatTimeStamp(long time);

    static QString formatTimeFromStartOfDayByQT(long time);
};

#endif // TIMEUTILS_H
