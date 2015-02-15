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

        //Insert the friend's name in the friend
        //list
        personName1 != m_myProfileName ?
                    m_friendList.append(personName1):
                    m_friendList.append(personName2);

        lineCount++;

        //Copy the related friends to
        //the friends relation file
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
    //Matrix's output  file
    QFile currentPersonMatrix("Matrix.txt");
    currentPersonMatrix.open(QIODevice::WriteOnly);
    if(!currentPersonMatrix.isOpen()) {
        qDebug().noquote() << "The file has not been opened";
    }

    //Indicator of matrix that need to me made
    bool matrixToBeMade[m_numberOfFriends];

    //Set indicator to true
    for(int i = 0; i < m_numberOfFriends; i++) {
        matrixToBeMade[i] = true;
    }

    //Matrix Representation that will
    //be written to a file
    QByteArray matrixRepresentation;

    m_friendsRelationListFile->open(QIODevice::ReadOnly);
    if(!m_friendsRelationListFile->isOpen()) {
        qDebug().noquote() << "The file has not been opened";
    }

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

        //Writing the adjacency matrix
        //to a file
        for(int i = 0; i < m_numberOfFriends; i++) {
            for(int j = 0; j < 3; j++) {
                matrixRepresentation.append(QString::number(tempMatrix[i][j]));
                if(j == 2) {
                    matrixRepresentation.append('\n');
                }
                else {
                    matrixRepresentation.append(' ');
                }
            }
        }
        currentPersonMatrix.write(matrixRepresentation);
        currentPersonMatrix.write("\n");
        matrixRepresentation.clear();
    }//End loop while
    
    for(int currentPerson = 1; currentPerson <= m_numberOfFriends; currentPerson++) {
        if(matrixToBeMade[currentPerson - 1]) {
            for(int relatedPerson = 1; relatedPerson <= m_numberOfFriends; relatedPerson++) {
                for(int k = 1; k <= 3; k++) {
                    if(k == 1) {
                        matrixRepresentation.append(QString::number(currentPerson));
                        matrixRepresentation.append(' ');
                    }
                    else if(k == 2) {
                        matrixRepresentation.append(QString::number(relatedPerson));
                        matrixRepresentation.append(' ');
                    }
                    else if(k == 3) {
                        if(currentPerson == relatedPerson) {
                            matrixRepresentation.append('1');
                            matrixRepresentation.append('\n');
                        }
                        else {
                            matrixRepresentation.append('0');
                            matrixRepresentation.append('\n');
                        }
                    }
                }//End loop for
            }//End loop for
            currentPersonMatrix.write(matrixRepresentation);
            currentPersonMatrix.write("\n");
            matrixRepresentation.clear();
            currentPersonMatrix.close();
        }//End condition if
    }//End loop for
    m_friendsRelationListFile->close();
}//End method createMatrix
