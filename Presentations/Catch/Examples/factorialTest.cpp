#define CATCH_CONFIG_FAST_COMPILE

#include "catch.hpp"

constexpr unsigned long Factorial( unsigned long number )
{
    if ( number > 1 )
    {
        return Factorial( number - 1 ) * number;
    }
    else
    {
        return number;
    }
}

TEST_CASE( "First three numbers",                   // test name - must be unique - runtime check
           "[Factorial][positive][!hide]" )         // tags, i.e. "[widget],[gadget]"
{
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
}

TEST_CASE( "Second three numbers", "[Factorial][positive][!hide]" )
{
    REQUIRE( Factorial(4) == 24 );
    REQUIRE( Factorial(5) == 120 );
    REQUIRE( Factorial(6) == 720 );
}

TEST_CASE( "Random three numbers", "[Factorial][.]" )
{
    REQUIRE( Factorial(0) == 0 );
    REQUIRE( Factorial(7) == 5040 );
    REQUIRE( Factorial(15) == 1307674368000 );
}
