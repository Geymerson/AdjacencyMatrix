#ifndef DATATREATMENT_H
#define DATATREATMENT_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <Person.h>

class DataTreatment
{
private:
    //Data containning the list of
    //the profile owner's friends and
    //the relation between it's friends
    QString m_myFileName;

    //Name of the Profile owner
    QString m_myProfileName;

    //Total number of friends of the
    //profile owner
    int m_numberOfFriends;

    //List of profile owner's friends
    //and their respective friends
    Person *m_peopleList;

    //File that contain the relation
    //between friends
    QFile *m_friendsRelationListFile;

public:
    //Class empty constructor
    DataTreatment();

    //Class 3 arguments constructor
    DataTreatment(QString myFileName, QString myProfileName, int num);

    //Class empty destructor
    ~DataTreatment();

    //Read and create the
    //friend's relation file
    void readData();

    //Get the friendship
    //between the user's friends
    void setRelations();

    //Write all the friendship matrix
    //to a .txt file
    void toMatrix();
};

#endif // DATATREATMENT_H
