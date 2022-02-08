#include "EmployeeManager.h"
#include <map>

EmployeeManager::EmployeeManager(IDatabaseConnection *dbConnection): dBConnection_{dbConnection}
{
  dBConnection_->connect();
}

EmployeeManager::~EmployeeManager()
{
  dBConnection_->disconnect();
}

float EmployeeManager::getSalary(int employeeId) const
{
 return dBConnection_->getSalary(employeeId);
}
  
void EmployeeManager::setSalary(int employeeId, float newSalary)
{
  dBConnection_->updateSalary(employeeId, newSalary);
}
  
std::map<std::string, float> EmployeeManager::vectorToMap(std::vector<Employee> const& employees) const
{
  std::map<std::string, float> result;
  for(Employee const& employee : employees)
  {
      result[employee.name] = employee.salary;
  }
  return result;
}

std::map<std::string,float> EmployeeManager::getSalariesGreater(float low) const
{
  return vectorToMap(dBConnection_->getSalariesRange(low));
}
std::map<std::string,float> EmployeeManager::getSalariesBetween(float low, float high) const
{
  return vectorToMap(dBConnection_->getSalariesRange(low, high));
}
