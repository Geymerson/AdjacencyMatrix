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
    readData();
}//End class' non-empty-constructor

DataTreatment::~DataTreatment() {
    delete m_friendsRelationListFile;
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

    int lineCount = -1;

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

        lineCount++;

        if(lineCount == m_numberOfFriends) {
            m_friendsRelationListFile = new QFile("FriendsRelation.txt");
            m_friendsRelationListFile->open(QIODevice::WriteOnly);
            QDataStream out(m_friendsRelationListFile);

            while (!dataEntry.atEnd()) {
                QString tempLine = dataEntry.read(8000);
                out << tempLine;
            }
        }
        m_friendsRelationListFile->close();
    }//End loop while
}//End method readData

//Method to generate the matrix
void DataTreatment::createMatrix(){
    bool matrixToBeMade[1000] = {true};
    m_friendsRelationListFile->open(QIODevice::ReadOnly);

    while(!m_friendsRelationListFile->atEnd()) {
        QString line = m_friendsRelationListFile->readLine(1024);

        //Names from the current line
        QString personName1, personName2;

        //Creating the matrix
        int tempMatrix[m_numberOfFriends][3];

        //Get the names from the current line
        personName1 = line.section('"', 1, 1);
        personName2 = line.section('"', 3, 3);

        //Get the index of the current person
        int currentProfile = m_friendList.indexOf(personName1);

        //Every user is related to himself
        tempMatrix[currentProfile][2] = 1;

        //Output file
        QFile currentUserMatrix("Matrix " + currentProfile);
        currentUserMatrix.open(QIODevice::WriteOnly);

        //Fill column 1
        for(int i = 1; i <= m_friendList.length(); i++) {
            tempMatrix[i - 1][0] = currentProfile;
            tempMatrix[i - 1][1] = i;
        }//End loop for


        //Writing the adjacency matrix
        //to a file
        QDataStream outputMatrix(&currentUserMatrix);
        outputMatrix << tempMatrix;
    }//End loop while
}//End method createMatrix
