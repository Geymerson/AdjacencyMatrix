#ifndef DATATREATMENT_H
#define DATATREATMENT_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QStringList>

class DataTreatment
{
private:
    //Data containning the list of
    //Friends relations
    QString m_myFileName;

    //Name of the Profile
    //the profile owner
    QString m_myProfileName;

    //Total number of friends of the
    //profile owner
    int m_numberOfFriends;

    //List of Friends
    QStringList m_friendList;

public:
    DataTreatment();
    DataTreatment(QString myFileName, QString myProfileName, int num);
    ~DataTreatment();
    void readData();
    void createMatrix();
};

#endif // DATATREATMENT_H
