#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

template<typename T>
class NumericRange
    : public Catch::MatcherBase<T>
{
    typename std::enable_if< std::is_integral<T>::value, T >::type m_begin, m_end;
    
public:
    NumericRange( T begin, T end )
    : m_begin{ begin }
    , m_end{ end }
    {}
    bool match( T const& i ) const override
    {
        return i >= m_begin && i <= m_end;
    }
    std::string describe() const override
    {
        return std::string{"is between " + std::to_string(m_begin) + " and " + std::to_string(m_end)};
    }
};

template<typename T>
auto IsBetween(T begin, T end)
{
    return NumericRange<T>( begin, end );
}

TEST_CASE( "Matchers test" )
{
    SECTION( "Inside range" )
    {
        CHECK_THAT( 12, IsBetween( std::numeric_limits<short>::min(), std::numeric_limits<short>::max() ) );
        CHECK_THAT( 'u', IsBetween( 'g', 'z' ) );
    }
    
    SECTION( "Out of range" )
    {
        CHECK_THAT( std::numeric_limits<int>::min(),
                   !IsBetween( static_cast<int>(std::numeric_limits<short>::min())
                              ,static_cast<int>(std::numeric_limits<short>::max())) );
    }
}
