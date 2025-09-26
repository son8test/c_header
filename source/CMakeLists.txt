set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

FetchContent_Declare(
    son8__${testrepo}
    GIT_REPOSITORY https://github.com/soneight/${testrepo}.git
    GIT_TAG        ${testhash}
)
FetchContent_MakeAvailable( son8__${testrepo} )
