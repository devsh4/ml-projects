
#include "Tick.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_tick[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_tick = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_tick
};

Tick::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Tick::Base::tick() const
{
    UMLRTOutSignal signal;
    signal.initialize( "tick", signal_tick, srcPort, &payload_tick );
    return signal;
}

Tick::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal Tick::Conj::tick() const
{
    UMLRTInSignal signal;
    signal.initialize( "tick", signal_tick, srcPort, &payload_tick );
    return signal;
}


