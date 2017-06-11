#ifndef CURRENTPHOTOPOINTER_H
#define CURRENTPHOTOPOINTER_H

#include <QObject>
#include <QAbstractListModel>

class CurrentPoint
{
public:
    CurrentPoint(int track_id, double lat, double lon);

    int track_id() const;
    double lat() const;
    double lon() const;

    void track_id(int id);
    void lat(double lat);
    void lon(double lon);

private:
    int m_track_id;
    double m_lat;
    double m_lon;
};


class CurrentPhotoPointer : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PointRoles {
        IdRole = Qt::UserRole + 1,
        LatRole,
        LonRole
    };

    CurrentPhotoPointer(QObject *parent = 0);


    Q_INVOKABLE void addPointer(int track_id, double lat, double lon);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<CurrentPoint> m_points;
};




#endif // CURRENTPHOTOPOINTER_H
