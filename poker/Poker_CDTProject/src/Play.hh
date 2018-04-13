
#ifndef PLAY_HH
#define PLAY_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Play
{
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal deal( int cards, int p ) const;
        UMLRTInSignal ack() const;
    };
    enum SignalId
    {
        signal_deal = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_ack
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal deal() const;
        UMLRTOutSignal ack( int c ) const;
    };
};

#endif

