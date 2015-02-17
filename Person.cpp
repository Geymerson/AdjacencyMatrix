#include "Person.h"

Person::Person()
{
    m_name = "";
    m_verified = false;
}

Person::~Person()
{

}

void Person::setFriend(const int& friendID) {
    m_isFriendWith[friendID] = 1;
}

void Person::setPersonName(const QString& name) {
    m_name = name;
}

void Person::setPersonalID(const int& idNumber) {
    m_personalID = idNumber;
}

void Person::setVerification(const bool &state) {
    m_verified = state;
}

QString Person::name() const {
    return m_name;
}

int Person::personalID() const {
    return m_personalID;
}

bool Person::isVerified() const {
    return m_verified;
}

int Person::isFriendWith(const int& personNum) const
{
    return m_isFriendWith[personNum];
}

