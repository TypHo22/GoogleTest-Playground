#include "IDatabaseConnection.h"
#include <iostream>

unsigned IDatabaseConnection::connectionCount_ = 0;

IDatabaseConnection::IDatabaseConnection(std::string serverAddress) : serverAdress_{serverAddress}
{

}

IDatabaseConnection::IDatabaseConnection(std::string serverAddress,HelperClass* hc) : serverAdress_{serverAddress}, helperClass_{hc}
{
    helperClass_->increaseConnectionCount();
}

void IDatabaseConnection::connect()
{

  std::cout << "Connecting to database server " << serverAdress_ << "\n";
  //initialize real DB connection
}

void IDatabaseConnection::disconnect()
{
 std::cout << "Disconnecting from database\n";
 //close the real connection
}

void IDatabaseConnection::increaseConnectionCount()
{
    connectionCount_++;
    std::cout<< "Connection count = " << connectionCount_ <<std::endl;
}

void HelperClass::increaseConnectionCount()
{
    IDatabaseConnection::increaseConnectionCount();
}
