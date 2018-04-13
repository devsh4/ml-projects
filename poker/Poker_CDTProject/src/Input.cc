
#include "Input.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
#include <cstddef>
struct UMLRTCommsPort;

struct params_inp
{
    char * rounds;
    bool twoDigitRounds;
};

static UMLRTObject_field fields_inp[] = 
{
    {
        "rounds",
        &UMLRTType_charptr,
        offsetof( params_inp, rounds ),
        1,
        0
    },
    {
        "twoDigitRounds",
        &UMLRTType_bool,
        offsetof( params_inp, twoDigitRounds ),
        1,
        0
    }
};

static UMLRTObject payload_inp = 
{
    sizeof( params_inp ),
    2,
    fields_inp
};

Input::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal Input::Base::inp() const
{
    UMLRTInSignal signal;
    signal.initialize( "inp", signal_inp, srcPort, &payload_inp );
    return signal;
}

Input::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Input::Conj::inp( char * rounds, bool twoDigitRounds ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "inp", signal_inp, srcPort, &payload_inp, &rounds, &twoDigitRounds );
    return signal;
}


