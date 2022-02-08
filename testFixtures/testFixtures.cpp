#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CodeUnderTest.h"
#include <iostream>

/**
 * @brief The AccountTestFixture class
 * gtest fixtures enable us to set up a class once and use it every time
 * which prevents much repetive code.
 *
 * The worflow for fixtures is the following:
 * Fixture Constructor -> SetUp() -> TestBody() -> TearDown() -> Fixture Destructor
 */
class AccountTestFixture: public testing::Test
{
public:
    AccountTestFixture(); // gets called on creation of EACH test
    virtual ~AccountTestFixture(); // gets called on deletion of EACH test
    void SetUp() override; //gets called on creation of EACH test
    void TearDown() override; //gets called on deletion of EACH test
    static void SetUpTestCase();//gets called ONCE on creation of testCase
    static void TearDownTestCase();//gets called ONCE on deletion of testCase
protected:
    Account* account_;
};

AccountTestFixture::AccountTestFixture()
{
    std::cout<<"AccountTestFixture::AccountTestFixture()"<<std::endl;
}

AccountTestFixture::~AccountTestFixture()
{
    std::cout<<"AccountTestFixture::~AccountTestFixture()"<<std::endl;
}

/**
 * @brief AccountTestFixture::SetUp
 * set up the account class with a balance of 10.5
 * this method gets automatically  called on each test case
 * and works as ARRANGE and ACT
 */
void AccountTestFixture::SetUp()
{
    std::cout<<"AccountTestFixture::SetUp()"<<std::endl;
    account_ = new Account; //I am using new here to show for what we need the void AccountTestFixture::TearDown() method
    account_->deposit(10.5);
}

/**
 * @brief AccountTestFixture::TearDown
 * gets called on each end of a testcase to prevent
 * a memory leak in our case
 */
void AccountTestFixture::TearDown()
{
    std::cout<<"AccountTestFixture::TearDown()"<<std::endl;
    delete account_;
}

/**
 * @brief AccountTestFixture::SetUpTestCase
 * gets called once on the beginning of our tests
 */
void AccountTestFixture::SetUpTestCase()
{
    std::cout<<"AccountTestFixture::SetUpTestCase()"<<std::endl;
}

/**
 * @brief AccountTestFixture::TearDownTestCase
 * gets called once at the end of the last testcase
 */
void AccountTestFixture::TearDownTestCase()
{
    std::cout<<"AccountTestFixture::TearDownTestCase())"<<std::endl;
}

//the actual tests

TEST_F(AccountTestFixture, TestDeposit)
{
  std::cout << "Test body\n";
  ASSERT_EQ(10.5, account_->getBalance());
}

TEST_F(AccountTestFixture,  TestWithdrawOK)
{
  account_->withdrawal(3);

  ASSERT_EQ(7.5, account_->getBalance());
}

TEST_F(AccountTestFixture,  TestWithdrawInsufficientFunds)
{
  ASSERT_THROW(account_->withdrawal(300), std::runtime_error);
}

TEST_F(AccountTestFixture,  TestTransferOK)
{
  Account to;

  account_->transfer(to, 2);

  ASSERT_EQ(8.5, account_->getBalance());
  ASSERT_EQ(2, to.getBalance());
}


TEST_F(AccountTestFixture,  TestTransferInsufficientFunds)
{
  Account to;

  ASSERT_THROW(account_->transfer(to, 200), std::runtime_error);
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
