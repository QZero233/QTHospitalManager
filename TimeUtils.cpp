#include "TimeUtils.h"
#include <ctime>

#include <QDateTime>

using namespace std;

TimeUtils::TimeUtils()
{

}

QString TimeUtils::formatTimeStamp(long t){
    QDateTime date=QDateTime::fromSecsSinceEpoch(t);
    return date.toString("yyyy-MM-dd HH:mm");
}

QString TimeUtils::formatTimeFromStartOfDayByQT(long time){
    return QTime::fromMSecsSinceStartOfDay(time).toString("HH:mm");
}
