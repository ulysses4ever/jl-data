using PortNumbers
using FactCheck


facts( "Port Numbers" ) do
    p = PortNumber{UserPort}( 1234 )
    @fact Int( p ) --> 1234
    @fact string( p ) --> "1234"
    @fact ASCIIString( p ) --> "1234"
    @fact typeof( make_port_number( 22 )) --> PortNumber{EstablishedPort}
    @fact typeof( make_port_number( 512 )) --> PortNumber{RootPort}
    @fact typeof( make_port_number( 1234 )) --> PortNumber{UserPort}
    
end
