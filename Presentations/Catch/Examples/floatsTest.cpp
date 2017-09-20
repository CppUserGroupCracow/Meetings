#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

TEST_CASE( "Floats test" )
{
    const auto number = 123.1f;
    
    SECTION("Epsilon")
    {
        REQUIRE( number == Approx( 123.2f ).epsilon(0.001) );
        REQUIRE( number != Approx( 123.2f ).epsilon(0.0001) );
    }
    
    SECTION("Margin")
    {
        REQUIRE( number == Approx( 123.2f ).margin(0.1) );
        REQUIRE( number != Approx( 123.2f ).margin(0.01) );
    }

    SECTION( "Scale")
    {
        REQUIRE( number == Approx( 123.2f ).epsilon(0.001).scale(1.0) );
        
        // Thanks to Richard Harris for his help refining this formula
        
        //bool relativeOK = std::fabs( lhs - rhs.m_value ) < rhs.m_epsilon * (rhs.m_scale + (std::max)( std::fabs(lhs), std::fabs(rhs.m_value) ) );
        
        //if (relativeOK) {
        //    return true;
        //}
        //return std::fabs(lhs - rhs.m_value) < rhs.m_margin;
    }

    
}
