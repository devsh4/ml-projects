
#ifndef INPUT_HH
#define INPUT_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Input
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal inp() const;
    };
    enum SignalId
    {
        signal_inp = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal inp( char * rounds, bool twoDigitRounds ) const;
    };
};

#endif

