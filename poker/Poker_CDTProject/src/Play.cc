
#include "Play.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
#include <cstddef>
struct UMLRTCommsPort;

struct params_deal
{
    int cards;
    int p;
};

static UMLRTObject_field fields_deal[] = 
{
    {
        "cards",
        &UMLRTType_int,
        offsetof( params_deal, cards ),
        1,
        0
    },
    {
        "p",
        &UMLRTType_int,
        offsetof( params_deal, p ),
        1,
        0
    }
};

static UMLRTObject payload_deal = 
{
    sizeof( params_deal ),
    2,
    fields_deal
};

static UMLRTObject_field fields_ack[] = 
{
    {
        "c",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ack = 
{
    sizeof( int ),
    1,
    fields_ack
};

Play::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Play::Conj::deal( int cards, int p ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "deal", signal_deal, srcPort, &payload_deal, &cards, &p );
    return signal;
}

UMLRTInSignal Play::Conj::ack() const
{
    UMLRTInSignal signal;
    signal.initialize( "ack", signal_ack, srcPort, &payload_ack );
    return signal;
}

Play::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal Play::Base::deal() const
{
    UMLRTInSignal signal;
    signal.initialize( "deal", signal_deal, srcPort, &payload_deal );
    return signal;
}

UMLRTOutSignal Play::Base::ack( int c ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ack", signal_ack, srcPort, &payload_ack, &c );
    return signal;
}


