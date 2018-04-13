
#include "Top.hh"

#include "Dealer.hh"
#include "Player.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
, input( internalPorts[internalport_input] )
, d1( &slot->parts[part_d1] )
, p1( &slot->parts[part_p1] )
, p2( &slot->parts[part_p2] )
, p3( &slot->parts[part_p3] )
, p4( &slot->parts[part_p4] )
, p5( &slot->parts[part_p5] )
, p6( &slot->parts[part_p6] )
, twoDigitRounds( false )
{
    stateNames[State1] = "State1";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}

void Capsule_Top::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case State1:
        currentState = state_____State1( &message );
        break;
    default:
        break;
    }
}

void Capsule_Top::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = State1;
}

const char * Capsule_Top::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Top::update_state( Capsule_Top::State newState )
{
    currentState = newState;
}

void Capsule_Top::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Top transition subvertex0,State1 */
    log.log("[Top] starting");
    int argc = UMLRTMain::getArgCount();
    if (argc > 0) {
    const char * arg = UMLRTMain::getArg(0);
    log.log("[Top] command line argument is '%s'", arg);
    char * myArg = new char[strlen(arg)+1];
    strcpy(myArg, arg);
    if(isValid(myArg)){
    log.log("[Top] sending to 'inputPort'");
    input.inp(myArg, twoDigitRounds).send();
    }
    else{
    log.log("[Top] invalid command line argument");
    log.log("[Top] not starting!");
    }
    }
    else {
    log.log("[Top] no command line argument");
    log.log("[Top] sending default value to 'inputPort'");
    input.inp("5", twoDigitRounds).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Top::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( State1 );
}

Capsule_Top::State Capsule_Top::state_____State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}













void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        }
    else
        UMLRTFrameService::sendBoundUnbound( internalPorts, internalport_input, index, true );
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        }
    else
    {
        UMLRTFrameService::sendBoundUnbound( internalPorts, internalport_input, index, false );
        UMLRTFrameService::disconnectPort( internalPorts[internalport_input], index );
    }
}


bool Capsule_Top::isValid( char * arg )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Top operation isValid */
    if (!(strlen(arg)<3)) {
    return false;
    }
    else if(strlen(arg) == 2){
    twoDigitRounds = true;
    char c1 = arg[0]; 
    char c2 = arg[1];
    if(c1 - '0' >= 0 && c1 - '0' <= 9){
    if(c2 - '0' >= 0 && c2 - '0' <= 9){
    return true;
    }
    else{
    return false;
    }
    }
    else{
    return false;
    }
    }
    else{
    char c1 = arg[0]; 
    if(c1 - '0' >= 0 && c1 - '0' <= 9){
    return true;
    }
    else{
    return false;
    }
    }
    /* UMLRTGEN-USERREGION-END */
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "d1",
        &Dealer,
        1,
        1,
        false,
        false
    },
    {
        "p1",
        &Player,
        1,
        1,
        false,
        false
    },
    {
        "p2",
        &Player,
        1,
        1,
        false,
        false
    },
    {
        "p3",
        &Player,
        1,
        1,
        false,
        false
    },
    {
        "p4",
        &Player,
        1,
        1,
        false,
        false
    },
    {
        "p5",
        &Player,
        1,
        1,
        false,
        false
    },
    {
        "p6",
        &Player,
        1,
        1,
        false,
        false
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Top::port_input,
        "Input",
        "input",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Top::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Top );
    UMLRTFrameService::connectPorts( internalPorts[Capsule_Top::internalport_input], 0, &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_input], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 0, &slot->parts[Capsule_Top::part_p1].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 1, &slot->parts[Capsule_Top::part_p2].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 2, &slot->parts[Capsule_Top::part_p3].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 3, &slot->parts[Capsule_Top::part_p4].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 4, &slot->parts[Capsule_Top::part_p5].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_Dealer::borderport_playPort], 5, &slot->parts[Capsule_Top::part_p6].slots[0]->ports[Capsule_Player::borderport_playPort], 0 );
    Dealer.instantiate( NULL, slot->parts[Capsule_Top::part_d1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_d1].slots[0], Dealer.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p1].slots[0], Player.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p2].slots[0], Player.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p3].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p3].slots[0], Player.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p4].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p4].slots[0], Player.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p5].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p5].slots[0], Player.numPortRolesBorder ) );
    Player.instantiate( NULL, slot->parts[Capsule_Top::part_p6].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_p6].slots[0], Player.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    7,
    roles,
    0,
    NULL,
    2,
    portroles_internal
};

