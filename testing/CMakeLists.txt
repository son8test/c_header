set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Add tests ⮟ HERE ⮟ that should NOT use extra warning flags

if ( MSVC )
    add_compile_options( /W4 )
else( )
    add_compile_options( -Wall -Wextra -Wpedantic )
endif( )

# Add tests ⮟ HERE ⮟ that SHOULD use extra warning flags
