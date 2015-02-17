#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDebug>

class Person
{
private:
    //Person name
    QString m_name;

    //Array representing person's friends
    int m_isFriendWith[1000] = {0};

    //Person's ID
    int m_personalID;

    //Person's verification state
    bool m_verified;

public:
    //Empty class constructor
    Person();

    //Empty class destructor
    ~Person();

    //Set the friend at "friendID" position to 1
    void setFriend(const int& friendID);

    //Set person name
    void setPersonName(const QString& name);

    //Set the person ID to idNum
    void setPersonalID(const int& idNum);

    //Set the person verification state to "state"
    void setVerification(const bool& state);

    //Get person ID number
    int personalID() const;

    //Get person name
    QString name() const;

    //Check the current person state
    bool isVerified() const;

    //Return 1 if the person is friend of friendNum
    //and 0 otherwise
    int isFriendWith(const int& friendNum) const;
};

#endif // PERSON_H
