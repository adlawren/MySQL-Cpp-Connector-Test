#include <iostream>
#include <stdexcept>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

static const std::string url = "tcp://127.0.0.1:3306";
static const std::string user = "root";
static const std::string password = "PASSWORD";

int main(int argc, char* argv[])
{
  sql::Driver *driver;
  sql::Connection *conn;
  sql::Statement *stmt;
  sql::ResultSet *rs;
  sql::PreparedStatement *prep_stmt;

  try
  {
    driver = get_driver_instance();

    conn = driver->connect(url, user, password);

    conn->setSchema("provinces");

    // Statement example
    stmt = conn->createStatement();

    rs = stmt->executeQuery("SELECT * FROM provinces");

    std::cout << "Retreived row count: " << rs->rowsCount() << std::endl;

    for (size_t i = 0; i < rs->rowsCount(); ++i) {
      rs->next();
      std::cout << "Next string: " <<  rs->getString("province") <<  std::endl;
    }

    // Prepared statement example
    prep_stmt = conn->prepareStatement("INSERT INTO provinces (province, population) VALUES (?, ?)");

    prep_stmt->setString(1, "test province");
    prep_stmt->setString(2, "3");

    int update_count = prep_stmt->executeUpdate();

    std::cout << "Updated row count: " << update_count << std::endl;

    delete rs;
    delete stmt;
    delete prep_stmt;
    conn->close();
    delete conn;
  }
  catch (sql::SQLException &e)
  {
    std::cout << "Error during processing.." << std::endl;
  }

  return 0;
}
