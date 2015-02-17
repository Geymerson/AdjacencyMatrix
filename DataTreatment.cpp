#include "DataTreatment.h"

//Empty constructor
DataTreatment::DataTreatment() {
    m_myFileName = "";
    m_myProfileName = "";
    m_numberOfFriends = 0;
    m_peopleList = 0;
}//End class' empty constructor

//Class constructor
DataTreatment::DataTreatment(QString myFileName,
                             QString myProfileName,
                             int numberOfFriends)
{
    m_myFileName = myFileName;
    m_myProfileName = myProfileName;
    m_numberOfFriends = numberOfFriends;
    m_peopleList = new Person[m_numberOfFriends];
    readData();
}//End class' non-empty-constructor

DataTreatment::~DataTreatment() {
    delete m_friendsRelationListFile;
    delete [] m_peopleList;
}//End class' destructor

void DataTreatment::readData() {
    //Reading the entry file
    QFile dataEntry(m_myFileName);
    dataEntry.open(QIODevice::ReadOnly);

    //Checking if the file has been opened
    if(!dataEntry.isOpen()) {
        qDebug().quote() << dataEntry.fileName()
                         << "File Not Opened";
    }

    //Create friends relations file
    m_friendsRelationListFile = new QFile("FriendsRelations.txt");
    m_friendsRelationListFile->open(QIODevice::WriteOnly);

    QString line, personName1, personName2;

    int personAndLineCounter = 0;

    while(personAndLineCounter != m_numberOfFriends) {
        //Get file line
        line = dataEntry.readLine(1024);

        //Extract the first name in the string
        personName1 = line.section('"', 1, 1);

        //Extract the second name in the string
        personName2 = line.section('"', 3, 3);

        //Insert the friend's name in the friend
        //list
        personName1 != m_myProfileName ?
                    m_peopleList[personAndLineCounter].setPersonName(personName1):
                    m_peopleList[personAndLineCounter].setPersonName(personName2);
        m_peopleList[personAndLineCounter].setPersonalID(personAndLineCounter);

        personAndLineCounter++;

        //Copy the related friends to
        //the friends relation file
        if(personAndLineCounter == m_numberOfFriends) {
            while(!dataEntry.atEnd()) {
                QByteArray getData = dataEntry.read(8000);
                m_friendsRelationListFile->write(getData);
            }//End loop while
        }//End condition if
    }//End loop while
    m_friendsRelationListFile->close();
}//End method readData

void DataTreatment::setRelations() {
    //Open file
    m_friendsRelationListFile->open(QIODevice::ReadOnly);

    //Checking if the file was
    //Correctly opened
    if(!m_friendsRelationListFile->isOpen()) {
        qDebug().noquote() << m_friendsRelationListFile->fileName()
                           << "file has not been opened";
    }

    QString line, personName1, personName2, lastPersonChecked;
    int unknownPerson1, unknownPerson2;

    //Empty string
    lastPersonChecked = "";

    while(!m_friendsRelationListFile->atEnd()) {
        line = m_friendsRelationListFile->readLine(1024);
        personName1 = line.section('"', 1, 1);
        personName2 = line.section('"', 3, 3);

        //Condition to make sure that persons
        //with same name will not be
        //double checked
        if(lastPersonChecked != "") {
            if(lastPersonChecked != personName1) {
                for(int i = 0; i < m_numberOfFriends; i++) {
                    if(m_peopleList[i].name() == lastPersonChecked) {
                        m_peopleList[i].setVerification(true);
                    }//End condition if
                }//End loop for
            }//End condition if
        }//End condition if

        //Get current person being checked
        lastPersonChecked = personName1;

        //Get persons index
        for(int i = 0; i < m_numberOfFriends; i++) {
            //Person 1 index
            if(personName1 == m_peopleList[i].name()
                    && !m_peopleList[i].isVerified()) {
                unknownPerson1 = m_peopleList[i].personalID();
//                qDebug().noquote() << i;
            }

            //Person2 index
            if(personName2 == m_peopleList[i].name()) {
                unknownPerson2 = m_peopleList[i].personalID();
//                qDebug().noquote() << i;
            }//End condition if
        }//End loop for

        //Person1 is related with person2
        m_peopleList[unknownPerson1].setFriend(unknownPerson2);
        m_peopleList[unknownPerson2].setFriend(unknownPerson1);
    }//End loop while
}//End method setRelations

void DataTreatment::toMatrix() {
    QFile matrixFile("FaceBookMatrix.txt");
    matrixFile.open(QIODevice::WriteOnly);

    if(!matrixFile.isOpen()) {
        qDebug().noquote() << matrixFile.fileName()
                           << "file has not been opened";
    }//End condition if

    int currentPerson = 1;
    QByteArray matrixRepresentation;

    while(currentPerson <= m_numberOfFriends) {
        for(int relatedPerson = 1; relatedPerson <= m_numberOfFriends; relatedPerson++) {
            for(int column = 1; column <= 3; column++) {
                if(column == 1) {
                    matrixRepresentation.append(QString::number(currentPerson));
                    matrixRepresentation.append(' ');
                }
                else if(column == 2) {
                    matrixRepresentation.append(QString::number(relatedPerson));
                    matrixRepresentation.append(' ');
                }
                else if(column == 3) {
                    if(currentPerson == relatedPerson) {
                        matrixRepresentation.append('1');
                        matrixRepresentation.append("\n");
                    }
                    else if(m_peopleList[currentPerson - 1].isFriendWith(relatedPerson - 1)) {
                        matrixRepresentation.append('1');
                        matrixRepresentation.append("\n");
                    }
                    else {
                        matrixRepresentation.append('0');
                        matrixRepresentation.append("\n");
                    }
                }//End condition else
            }//End loop column
        }//End loop relatedPerson
        matrixFile.write(matrixRepresentation);
        matrixFile.write("\n");
        matrixRepresentation.clear();
        currentPerson++;
    }//End loop currentPerson
    matrixFile.close();
}//End method toMatrix
