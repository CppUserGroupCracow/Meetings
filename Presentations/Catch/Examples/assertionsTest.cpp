#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

TEST_CASE( "Assertions test" )
{
    SECTION( "Require just throws" )
    {
        REQUIRE_THROWS([]()
                          {
                              throw std::runtime_error{"Oh my God!"};
                              
                          }());
    }
    
    SECTION( "Require throws as" )
    {
        REQUIRE_THROWS_AS([]()
                        {
                            throw std::runtime_error{"Oh my God!"};
                            
                        }(),
                          std::exception);
    }
    
    SECTION( "Require throws with" )
    {
        REQUIRE_THROWS_WITH([]()
                          {
                              throw std::runtime_error{"Oh my God!"};
                              
                          }(),
                          "Oh my God!");
        
        REQUIRE_THROWS_WITH([]()
                            {
                                throw std::runtime_error{"Oh my God!"};
                                
                            }(),
                            Catch::Matchers::Contains("God"));
    }
}
