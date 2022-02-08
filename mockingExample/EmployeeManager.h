#pragma once
#include "Employee.h"
#include "IDatabaseConnection.h"

#include <map>
#include <vector>
#include <string>

/**
 * @brief The EmployeeManager class
 * Representation of a manager account which
 * can read and write from a database
 */
class EmployeeManager
{
public:
  EmployeeManager(IDatabaseConnection *dbConnection);
  ~EmployeeManager();

  void setSalary(int employeeId, float newSalary);
  float getSalary(int employeeId) const;
  
  std::map<std::string,float> getSalariesGreater(float low) const;
  std::map<std::string,float> getSalariesBetween(float low, float high) const;
  
private:
  std::map<std::string, float> vectorToMap(std::vector<Employee> const& employees) const;

private:
  IDatabaseConnection  *dBConnection_;
};
