#include <son8/c.hxx>

using namespace son8;
// base -> c::byte
// byte -> c::memset
// char -> c::strlen
// exec -> c::exit
// file -> c::printf
// math -> c::abs
// util -> c::setlocale
// wide -> c::wprintf

namespace test {
    constexpr auto Password_Size = 8u;
    constexpr int Error_Arguments_Count_Mismatch = 0;
    constexpr int Error_Password_Length_Mismatch = -1;
    constexpr int Error_Password_Mismatch = -2;

    bool check_password( c::byte const password[] );
    void clear_password( c::byte password[] );
}

int main( int argc, char *argv[] )
{
    c::setlocale( LC_ALL, "" );
    auto error_index = test::Error_Arguments_Count_Mismatch;
    c::byte password[test::Password_Size]; // base.hxx
    if ( argc != 2 ) goto failed;
    error_index = test::Error_Password_Length_Mismatch;
    if ( c::strlen( argv[1] ) != test::Password_Size ) goto failed;
    error_index = test::Error_Password_Mismatch;
    for ( auto i = 0u; i < test::Password_Size; ++i ) password[i] = c::byte{ static_cast<c::byte>( argv[1][i] ) };
    if ( !test::check_password( password ) ) goto failed;
    test::clear_password( password );
    c::wprintf( L"テスト成功\n" );
    c::exit( EXIT_SUCCESS ); // exec.hxx
failed:
    error_index = c::abs( error_index );
    assert( error_index < 3 );
    char const *messages[] = {
        "Arguments count mismatch\n",
        "Password length mismatch\n",
        "Password mismatch\n",
    };
    c::fprintf( stderr, "%s\n", messages[error_index] ); // file.hxx
    test::clear_password( password );
    c::exit( EXIT_FAILURE );
} // main

namespace test {

    bool check_password( c::byte const password[] ) {
        constexpr auto Bytes_Size = 8;
        c::byte correct[Bytes_Size] = {
            c::byte{'p'}, c::byte{'a'}, c::byte{'s'}, c::byte{'s'},
            c::byte{'w'}, c::byte{'o'}, c::byte{'r'}, c::byte{'d'},
        };
        for ( auto i = 0u; i < Bytes_Size; ++i ) {
            if ( password[i] != correct[i] ) {
                clear_password( correct );
                return false;
            }
        }
        clear_password( correct );
        return true;
    }

    void clear_password( c::byte password[] ) {
        c::memset( password, 0, Password_Size );
        for ( c::uint8_t i = 0u; i < Password_Size; ++i ) {
            if ( password[i] != c::byte{ 0 } ) {
                c::fprintf( stderr, "Password clear failed\n" );
                c::exit( EXIT_FAILURE );
            }
        }
    }

} // namespace test
