#ifndef ROBOTDBINTERFACE_H
#define ROBOTDBINTERFACE_H
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "name_id_list_model.h"
#include <sstream>
#include <eigen3/Eigen/Dense>

#include <QObject>
#include <QString>
class RobotDBInterface:public QObject
{
    Q_OBJECT
public:
    sql::Driver* driver;
    std::unique_ptr<sql::Connection> con;
    std::string error_msg;

public:
    RobotDBInterface();
    ~RobotDBInterface();
    Q_INVOKABLE bool establishSQLConn(QString adress_and_port, QString username, QString password, QString schema);
    Q_INVOKABLE QString getErrorMsg();
    bool establishSQLConnImpl(std::string adress_and_port, std::string username, std::string password, std::string schema);
    bool checkConnPrivileges();
    bool checkConnAlive();
};

#endif // ROBOTDBINTERFACE_H
