#pragma once

#include <string>
#include <vector>

#include "Employee.h"
/**
 * @brief The HelperClass class
 * gets used for being able to test the static methods
 */
class HelperClass
{
private:
    virtual void increaseConnectionCount();
    friend class IDatabaseConnection;
};

/**
 * @brief The IDatabaseConnection class
 * interface class for establishing the connection to a database.
 * interface because we want to be able to mock it and to subclass it (maybe)
 * example: IOracleDatabaseConnectionManager, ISQLDatabaseConnectionManager
 */
class IDatabaseConnection
{
public:
  IDatabaseConnection(std::string serverAddress);
  IDatabaseConnection(std::string serverAddress, HelperClass* hc);
  
  virtual float getSalary(int id) const = 0; // SELECT * FROM employees WHERE id=...
  virtual void updateSalary(int id, float newSalary) = 0;

  virtual std::vector<Employee> getSalariesRange(float low) const = 0; //just greater than low
  virtual std::vector<Employee> getSalariesRange(float low, float high) const = 0;

  virtual void connect();
  virtual void disconnect();

private:
  static unsigned connectionCount_;
  static void increaseConnectionCount();
  HelperClass *helperClass_;//for testing the static methods
protected:
  std::string serverAdress_;
  friend class HelperClass;
};
