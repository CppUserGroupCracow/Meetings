#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

struct TestCaseListener
    : Catch::TestEventListenerBase {
    
    using TestEventListenerBase::TestEventListenerBase;
    
    virtual void testCaseStarting( Catch::TestCaseInfo const& testInfo ) override
    {
        // Perform some setup before a test case is run
    }
    
    virtual void testCaseEnded( Catch::TestCaseStats const& testCaseStats ) override
    {
        // Tear-down after a test case is run
    }
};

CATCH_REGISTER_LISTENER( TestCaseListener )
