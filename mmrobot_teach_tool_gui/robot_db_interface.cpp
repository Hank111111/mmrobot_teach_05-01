#include "robot_db_interface.h"

RobotDBInterface::RobotDBInterface()
{

}
RobotDBInterface::~RobotDBInterface()
{
}

bool RobotDBInterface::establishSQLConnImpl(std::string adress_and_port, std::string username, std::string password, std::string schema){
    try{
        //std::cout<<"adress and port: "<<adress_and_port <<" username: "<< username << " password: "<< password<< " schema: "<<schema<<std::endl;
        driver = get_driver_instance();
        con.reset(driver->connect(adress_and_port, username, password));
        con->setSchema(schema);
        if(!con->isValid()){
            std::cout<<"Connect to mysql is invalid !"<<std::endl;
            return false;
        }
        std::cout<<"sql connected"<<std::endl;
        return  true;
    }
    catch(sql::SQLException &e)
    { 
        error_msg = e.what();
        std::cerr << error_msg << '\n';
        return false;
    }
}
bool RobotDBInterface::checkConnPrivileges(){
    std::cout<<"right now, no priviledge is checked."<<std::endl;
    return true;
}

bool RobotDBInterface::checkConnAlive(){
    if(con == nullptr){
        std::cout<<"con is a nullptr"<<std::endl;
        return false;
    }
    return con->isValid();
}


bool RobotDBInterface::establishSQLConn(QString adress_and_port, QString username, QString password, QString schema){
    return establishSQLConnImpl(adress_and_port.toStdString(), username.toStdString(), password.toStdString(), schema.toStdString());
}
QString RobotDBInterface::getErrorMsg(){
    return QString::fromStdString(error_msg);
}