#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "IDatabaseConnection.h"
#include "Employee.h"
#include "EmployeeManager.h"

/*Summary
Mocking Summary
Mocks can be used to isolate the test.
Mocked methods have empty implementations.
They can be used to control the behaviour of certain methods, like: returning a certain result, calling another method, throwing exceptions.
Mocks can be used for collaboration tests. That means you can test that method A called method B, with what parameters, and so on
Matchers can be used for matching parameters. Special matchers are "_" (anything) or the exact value ("Exactly").
Other matchers usually found: Gt( greater than), Ge(greater or equal), Lt(lower than), Le(lower or equal).
There are special matchers for strings.
Matchers can be used in assertions on vectors.
*/
/**
 * @brief The MockDatabaseConnection class
 * Mocking is replacing a "real" object with a fake one.
 * In our example we do not want to be in need of a real database connection.
 * Imagine you would always write and modificate our real database if we test the
 * write salary method
 * Thats were googleMock enables us to mock the real connection
 */
class MockDatabaseConnection : public IDatabaseConnection
{
public:
    MockDatabaseConnection(std::string serverAddress) : IDatabaseConnection(serverAddress)
    {

    }

    MockDatabaseConnection(std::string serverAddress, HelperClass* hc): IDatabaseConnection(serverAddress,hc)
    {

    }

    //MOCK_METHODn n=0
    //MOCK_METHOD(name, returnType(paramType1, paramType2));
    MOCK_METHOD0(connect, void());//MOCK_METHOD0 because we mock a method with 0 inputparameters
    MOCK_METHOD0(disconnect, void());

    //MOCK_CONST_METHOD(name, returnType(paramType1, paramType2));
    MOCK_CONST_METHOD1(getSalary, float(int));//MOCK_CONST_METHOD1 because we mock a const method with 1 input parameter
    MOCK_METHOD2(updateSalary, void(int, float) );

    MOCK_CONST_METHOD1(getSalariesRange, std::vector<Employee>(float));
    MOCK_CONST_METHOD2(getSalariesRange, std::vector<Employee>(float, float));

    //TestConnectionErrorInvoke
    //we give our MockDataBaseConnection class some extra functionality to mock a
    //connection error by defining an extra member function for it
    void someMemberMethod()
    {
        std::cout << "Some Member method which throws an runtime error"<<std::endl;
        throw std::runtime_error("Dummy Error");
    }
};

class MockHelper: public HelperClass
{
public:
    MOCK_METHOD(void, increaseConnectionCount,(), (override));

};

//Test with helper class for checking if the private method onConnect and the static method increaseConnectionCount() gets called
TEST(TestStaticMethod, BasicTest)
{
    MockHelper hc;

    EXPECT_CALL(hc, increaseConnectionCount()); // check if the static member function gets called
    MockDatabaseConnection db("dummyAdress",&hc);
}
/// Three ways how to simulate an event coming from the database (or in general the entity we want to mock)
// Variant 1 throw action in code
TEST(TestEmployeeManager, TestConnectionError)
{
    MockDatabaseConnection dbConnection("DummyAddresss");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Throw(std::runtime_error("Dummy Error")));

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
// Variant 2 define action seperately and invoke
ACTION(myThrow)
{
    std::cout << "Throwing an error!" <<std::endl;
    throw std::runtime_error("Dummy error");
}

TEST(TestEmployeeManager, TestConnectionErrorAction)
{
    MockDatabaseConnection dbConnection("DummyAddresss");
    EXPECT_CALL(dbConnection, connect()).WillOnce(myThrow());

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
// Variant 3 we have defined a member function in our mock class which
// simulates the connection error for us.
TEST(TestEmployeeManager, TestConnectionErrorInvoke)
{
    MockDatabaseConnection dbConnection("DummyAddresss");
    auto boundMehtod = std::bind(&MockDatabaseConnection::someMemberMethod, &dbConnection);
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::InvokeWithoutArgs(boundMehtod));

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
///
TEST(TestEmployeeManager, TestConnection)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());

    EmployeeManager employeeManager(&dbConnection);
}

TEST(TestEmployeeManager, TestUpdateSalary)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect()).Times(1);
    //if we do not care with which parameters a function gets called use placeHolder testing::_ ... we expect this function to get called with employee id 50 and an arbitrary salary
    EXPECT_CALL(dbConnection, updateSalary(50, testing::_)).Times(1);
    EmployeeManager employeeManager(&dbConnection);

    employeeManager.setSalary(50, 6000);
}

TEST(TestEmployeeManager, TestGetSalary)
{
    const int employeeId = 50;
    const float salary = 6100.0;
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalary(testing::_)).Times(1).WillOnce(testing::Return(salary));

    EmployeeManager employeeManager(&dbConnection);

    float returnedSalary = employeeManager.getSalary(employeeId);

    ASSERT_EQ(salary, returnedSalary);
}

TEST(TestEmployeeManager, TestGetSalaryInRange)
{
    const int low = 5000, high = 8000;
    std::vector<Employee> returnedVector{Employee{1, 5600, "John"},
                                         Employee{2, 7000, "Jane"},
                                         Employee{3, 6600, "Alex"}};

    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalariesRange(low, high)).WillOnce(testing::Return(returnedVector));

    EmployeeManager employeeManager(&dbConnection);

    std::map<std::string, float> returnedMap = employeeManager.getSalariesBetween(low, high);

    for(auto it=returnedMap.begin(); it!=returnedMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << '\n';
        ASSERT_THAT(it->second, testing::AnyOf(testing::Gt(low), testing::Lt(high - 3000)));
    }
}

//Demonstration of test matchers  here we want to have all of our returned values in a range
//between low and hight
TEST(TestEmployeeManager, TestGetSalaryInRangeMatchers)
{
    const int low = 5000, high = 8000;
    std::vector<Employee> returnedVector{Employee{1, 5600, "John"},
                                         Employee{2, 7000, "Jane"},
                                         Employee{3, 6600, "Alex"}};
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalariesRange(low, high)).WillOnce(testing::Return(returnedVector));

    EmployeeManager employeeManager(&dbConnection);
    std::map<std::string, float> returnedMap = employeeManager.getSalariesBetween(low, high);

    //we expect to have all of our returned values in a range between low and high
    for(auto it  = returnedMap.begin(); it != returnedMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
        ASSERT_THAT(it->second, testing::AllOf(testing::Gt(low), testing::Lt(high)));
    }
}

int main(int argc, char **argv)
{
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
