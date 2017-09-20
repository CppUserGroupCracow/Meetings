#define CATCH_CONFIG_FAST_COMPILE

#include "catch.hpp"
#include <vector>
#include <string>
#include <algorithm>

TEST_CASE( "List of animals", "[Animals][NoBDD]" )
{
    std::vector< std::string > animals { "cat", "dog", "horse", "elephant", "lion", "monkey" };
    constexpr auto wantedAnimal = "dog";
    
    SECTION( "Not sorted list" )
    {
        SECTION( "Making sure the list is not sorted" )
        {
            REQUIRE( std::is_sorted( std::begin(animals), std::end(animals) ) == false );
        }
        
        SECTION( "Checking if \"" + std::string{wantedAnimal} + "\" is in the list in linear time" )
        {
            REQUIRE( std::find( std::begin(animals), std::end(animals), wantedAnimal ) != std::end(animals) );
        }
    }
    
    SECTION( "Sorted list" )
    {
        std::sort( std::begin(animals), std::end(animals) );
        
        SECTION( "Making sure the list is sorted" )
        {
            REQUIRE( std::is_sorted( std::begin(animals), std::end(animals) ) == true );
        }
       
        SECTION( "Checking uniqueness of the list" )
        {
            const auto sortedAnimals = animals;
            
            std::unique( std::begin(animals), std::end(animals) );
            
            REQUIRE( sortedAnimals == animals );
        }
        
        SECTION( "Checking if \"" + std::string{wantedAnimal} + "\" is in the list in logarithmic time" )
        {
            REQUIRE( std::binary_search( std::begin(animals), std::end(animals), wantedAnimal ) );
        }
    }
}

// BDD style

SCENARIO( "Operations on the list of animals", "[Animals][BDD]" )
{
    GIVEN( "The list of animals" )
    {
        std::vector< std::string > animals { "cat", "dog", "horse", "elephant", "lion", "monkey" };
        constexpr auto wantedAnimal = "dog";
        
        WHEN( "List is not sorted" )
        {
            THEN( "Make sure it's not sorted" )
            {
                REQUIRE( std::is_sorted( std::begin(animals), std::end(animals) ) == false );
            }
            
            THEN( "Check if \"" + std::string{wantedAnimal} + "\" is in the list in linear time" )
            {
                REQUIRE( std::find( std::begin(animals), std::end(animals), wantedAnimal ) != std::end(animals) );
            }
        }
        
        WHEN( "List is sorted" )
        {
            std::sort( std::begin(animals), std::end(animals) );
            
            THEN( "Make sure it's sorted" )
            {
                REQUIRE( std::is_sorted( std::begin(animals), std::end(animals) ) == true );
            }
            
            THEN( "Check if elements of the list are unique" )
            {
                const auto sortedAnimals = animals;
                
                std::unique( std::begin(animals), std::end(animals) );
                
                REQUIRE( sortedAnimals == animals );
            }
            
            THEN( "Check if \"" + std::string{wantedAnimal} + "\" is in the list in logarithmic time" )
            {
                REQUIRE( std::binary_search( std::begin(animals), std::end(animals), wantedAnimal ) );
                
                // using vector matchers
                //
                // REQUIRE_THAT(animals, Catch::VectorContains(std::string(wantedAnimal)));
            }
        }
    }
}
