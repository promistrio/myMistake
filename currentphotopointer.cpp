#include "currentphotopointer.h"
#include <QDebug>


CurrentPoint::CurrentPoint(int track_id, double lat, double lon)
    : m_track_id(track_id), m_lat(lat), m_lon(lon)
{
}

int CurrentPoint::track_id() const
{
    return m_track_id;
}

double CurrentPoint::lat() const
{
    return m_lat;
}

double CurrentPoint::lon() const
{
    return m_lon;
}

void CurrentPoint::track_id(int id)
{
    this->m_track_id = id;
}

void CurrentPoint::lat(double lat)
{
    this->m_lat = lat;
}

void CurrentPoint::lon(double lon)
{
    this->m_lon = lon;
}

CurrentPhotoPointer::CurrentPhotoPointer(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CurrentPhotoPointer::addPointer(int track_id, double lat, double lon)
{
    CurrentPoint * pointer = new CurrentPoint(track_id, lat, lon);




    bool isChange = false;

    for (int i = 0; i< m_points.size(); i++)
    {
        bool isExist = m_points.at(i).track_id() == track_id;

        if (isExist)
        {
            m_points[i].track_id(track_id);
            m_points[i].lat(lat);
            m_points[i].lon(lon);
            isChange = true;
            emit dataChanged(index(0, 0), index(rowCount(), 0));
            qDebug() << rowCount();

            qDebug() << "Изменен указатель. Трек: " << track_id << " Широта: " << lat << " " << m_points.size();

            QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
            QModelIndex index2 = createIndex(rowCount(), 0, static_cast<void *>(0));

            emit dataChanged(index, index2);

            break;
        }

    }

    if(!isChange)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_points << *pointer;
        endInsertRows();
        qDebug() << "Новый указатель. Трек: " << track_id << " Широта: " << lat << " " << m_points.size();
    }
}

int CurrentPhotoPointer::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_points.count();
}

QVariant CurrentPhotoPointer::data(const QModelIndex & index, int role) const {

    qDebug() << index.row() << " " << index.column() << " " << role;

    if (index.row() < 0 || index.row() >= m_points.count())
        return QVariant();

    const CurrentPoint &point = m_points[index.row()];
    if (role == IdRole)
        return point.track_id();
    else if (role == LatRole)
        return point.lat();
    else if (role == LonRole)
        return point.lon();
    return QVariant();
}

QHash<int, QByteArray> CurrentPhotoPointer::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "track_id";
    roles[LatRole] = "lat";
    roles[LonRole] = "lon";
    return roles;
}

