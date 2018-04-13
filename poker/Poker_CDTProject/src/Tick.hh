
#ifndef TICK_HH
#define TICK_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Tick
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal tick() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal tick() const;
    };
    enum SignalId
    {
        signal_tick = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
};

#endif

