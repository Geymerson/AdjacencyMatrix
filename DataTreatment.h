#ifndef DATATREATMENT_H
#define DATATREATMENT_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <QDataStream>
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

    //File that contain the relation
    //between friends
    QFile *m_friendsRelationListFile;

public:
    DataTreatment();
    DataTreatment(QString myFileName, QString myProfileName, int num);
    ~DataTreatment();
    void readData();
    void createMatrix();
    void setFriendRelationListFile();
};

#endif // DATATREATMENT_H
