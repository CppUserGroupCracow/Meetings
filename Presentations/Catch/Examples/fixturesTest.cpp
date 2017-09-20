#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

namespace db_engine
{
    struct db_handler {};
    db_handler connect_database(const std::string& dbName, const std::string& userName, const std::string& password)
    {
        return db_handler{};
    }
    void disconnect_database(db_handler handler)
    {}
    bool query(db_handler handler, const std::string& sql)
    {
        return true;
    }
}

class IDBConnection
{
public:
    virtual ~IDBConnection() = default;
    virtual bool ExectueSQL(const std::string& sql) = 0;
};

class DBConnection
: public IDBConnection
{
    db_engine::db_handler dbHandler;
    
public:
    DBConnection(const std::string& dbName, const std::string& userName, const std::string& password)
    {
        dbHandler = db_engine::connect_database(dbName, userName, password);
    }
    ~DBConnection()
    {
        db_engine::disconnect_database(dbHandler);
    }
    bool ExectueSQL(const std::string& sql) override
    {
        return query( dbHandler, sql );
    }
};

class LogicFixture
{
protected:
    std::unique_ptr< IDBConnection > dbConnection;
    
public:
    LogicFixture()
    : dbConnection{ std::make_unique< DBConnection >("test.db","admin","admin") }
    {}
    
};

TEST_CASE_METHOD( LogicFixture, "Query to look at table STATION in undefined order", "[Fixture]" )
{
    REQUIRE( dbConnection->ExectueSQL("SELECT * FROM STATION") );
}

TEST_CASE_METHOD( LogicFixture, "Query to select only ID, CITY, and STATE columns from STATION table", "[Fixture]" )
{
    REQUIRE( dbConnection->ExectueSQL("SELECT ID, CITY, STATE FROM STATION") );
}


