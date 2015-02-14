#include "DataTreatment.h"

//Empty constructor
DataTreatment::DataTreatment() {
    m_myFileName = "";
    m_myProfileName = "";
    m_numberOfFriends = 0;
}

//Class constructor
DataTreatment::DataTreatment(QString myFileName,
                             QString myProfileName,
                             int numberOfFriends)
{
    m_myFileName = myFileName;
    m_myProfileName = myProfileName;
    m_numberOfFriends = numberOfFriends;
}

DataTreatment::~DataTreatment() {

}

void DataTreatment::readData() {
    //Reading the entry file
    QFile dataEntry(m_myFileName);
    dataEntry.open(QIODevice::ReadOnly);

    //Checking if the filed has been openned
    if(!dataEntry.isOpen()) {
        qDebug() << "File Not Opened";
    }

    //A better name is needed to this variables.
    QString s, t, u;

    while(!dataEntry.atEnd()) {
        s = dataEntry.readLine(1024);
        t = s.section('"', 1, 1);
        u = s.section('"', 3, 3);
        t != m_myProfileName ? m_friendList.append(t):
                               m_friendList.append(u);
    }
}

//Method to generate the matrix
void DataTreatment::createMatrix(){
    int aux = 1;

    while(aux != m_friendList.length()) {
        //Creating the matrix
        int temp[m_friendList.length()][3];

        //Fill rows 0 and 1
        for(int i = 1; i <= m_friendList.length(); i++) {
            temp[i - 1][0] = aux;
            temp[i - 1][1] = i;

            //Every user is related to himself
            if(i == aux) {
                temp[i][aux] = 1;
            }
        }
        aux++;
    }
}

