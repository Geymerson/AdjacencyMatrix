#include "DataTreatment.h"

//Empty constructor
DataTreatment::DataTreatment() {
    m_myFileName = "";
    m_myProfileName = "";
    m_numberOfFriends = 0;
}//End class' empty constructor

//Class constructor
DataTreatment::DataTreatment(QString myFileName,
                             QString myProfileName,
                             int numberOfFriends)
{
    m_myFileName = myFileName;
    m_myProfileName = myProfileName;
    m_numberOfFriends = numberOfFriends;
}//End class' non-empty-constructor

DataTreatment::~DataTreatment() {

}//End class' destructor

void DataTreatment::readData() {
    //Reading the entry file
    QFile dataEntry(m_myFileName);
    dataEntry.open(QIODevice::ReadOnly);

    //Checking if the filed has been openned
    if(!dataEntry.isOpen()) {
        qDebug() << "File Not Opened";
    }

    QString line, personName1, personName2;

    while(!dataEntry.atEnd()) {
        line = dataEntry.readLine(1024);
        //Extract the first name in the string
        personName1 = line.section('"', 1, 1);

        //Extract the second name in the string
        personName2 = line.section('"', 3, 3);

        //Insert the friend's name in the friend
        //list
        personName1 != m_myProfileName ?
                    m_friendList.append(personName1):
                    m_friendList.append(personName2);
    }//End loop while
}//End method readData

//Method to generate the matrix
void DataTreatment::createMatrix(){
    int currentProfile = 1;

    while(currentProfile != m_friendList.length()) {
        //Creating the matrix
        int temp[m_friendList.length()][3];

        //Fill rows 0 and 1
        for(int i = 1; i <= m_friendList.length(); i++) {
            temp[i - 1][0] = currentProfile;
            temp[i - 1][1] = i;
        }//End loop for

        //Every user is related to himself
        temp[currentProfile][2] = 1;
        currentProfile++;
    }//End loop while
}//End method createMatrix

