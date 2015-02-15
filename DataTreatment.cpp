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

    //Checking if the file has been opened
    if(!dataEntry.isOpen()) {
        qDebug().quote() << "File Not Opened";
    }

    m_friendsRelationListFile = new QFile("FriendsRelations.txt");
    m_friendsRelationListFile->open(QIODevice::WriteOnly);

    QString line, personName1, personName2;

    int lineCount = 0;

    while(lineCount != m_numberOfFriends) {
        line = dataEntry.readLine(1024);

        //Extract the first name in the string
        personName1 = line.section('"', 1, 1);

        //Extract the second name in the string
        personName2 = line.section('"', 3, 3);

//        qDebug().noquote() << personName1 << ", "
//                           << personName2;

        //Insert the friend's name in the friend
        //list
        personName1 != m_myProfileName ?
                    m_friendList.append(personName1):
                    m_friendList.append(personName2);

        lineCount++;
        if(lineCount == m_numberOfFriends) {
            while(!dataEntry.atEnd()) {
                QByteArray getData = dataEntry.read(8000);
                m_friendsRelationListFile->write(getData);
            }
        }//End condition if
    }//End loop while
    m_friendsRelationListFile->close();
}//End method readData

//Method to generate the matrix
void DataTreatment::createMatrix(){
    //Indicator of matrix that need to me made
    bool matrixToBeMade[1000] = {true};

    //Matrix Representation that will
    //be written to a file
    QByteArray matrixRepresentation;
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
        int currentProfile = m_friendList.indexOf(personName1) + 1;

        //Fill matrix
        for(int i = 1; i <= m_numberOfFriends; i++) {
            tempMatrix[i - 1][0] = currentProfile;
            tempMatrix[i - 1][1] = i;
            tempMatrix[i - 1][2] = 0;
        }//End loop for

        //Every person is related to itself
        tempMatrix[currentProfile - 1][2] = 1;

        //Person1 is related with person2
        tempMatrix[m_friendList.indexOf(personName2)][2] = 1;

        //The current person's matrix
        //Does not require to be
        //Created
        matrixToBeMade[m_friendList.indexOf(personName1)] = false;

        //Matrix's output  file
        QFile currentUserMatrix("Matrix " + currentProfile);
        currentUserMatrix.open(QIODevice::WriteOnly);

        //Writing the adjacency matrix
        //to a file
        for(int i = 0; i < m_numberOfFriends; i++) {
            for(int j = 0; j < 3; j++) {
                matrixRepresentation.append(tempMatrix[i][j]);
                if(j == 2) {
                    matrixRepresentation.append('\n');
                }
                else {
                    matrixRepresentation.append(' ');
                }
            }
        }
        currentUserMatrix.write(matrixRepresentation);
        matrixRepresentation.clear();
        currentUserMatrix.close();
    }//End loop while
    
    for(int i = 0; i < 1000; i++) {
        if(matrixToBeMade[i]) {
            int tempMatrix[m_numberOfFriends][3];
            for(int j = 1; j <= m_numberOfFriends; i++) {
                tempMatrix[j - 1][0] = i + 1;
                tempMatrix[j - 1][1] = j;
                tempMatrix[j - 1][2] = 0;
            }//End loop for
        }
    }
    m_friendsRelationListFile->close();
}//End method createMatrix
