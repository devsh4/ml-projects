
#include "Player.hh"

#include "Play.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Player::Capsule_Player( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, playPort( borderPorts[borderport_playPort] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Got_Card_1] = "Got_Card_1";
    stateNames[Ready] = "Ready";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_Player::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_playPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_playPort, index, true );
            break;
        }
}

void Capsule_Player::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_playPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_playPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_playPort], index );
            break;
        }
}






char Capsule_Player::defineCard( int c )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Player operation defineCard */
    //Assign cards
    if(c == 1 || c == 14 || c == 27 || c == 40 ){
    return 'A';
    }
    else if(c == 2 || c == 15 || c == 28 || c == 41){
    return '2';
    }
    else if(c == 3 || c == 16 || c == 29 || c == 42){
    return '3';
    }
    else if(c == 4 || c == 17 || c == 30 || c == 43){
    return '4';
    }
    else if(c == 5 || c == 18 || c == 31 || c == 44){
    return '5';
    }
    else if(c == 6 || c == 19 || c == 32 || c == 45){
    return '6';
    }
    else if(c == 7 || c == 20 || c == 33 || c == 46){
    return '7';
    }
    else if(c == 8 || c == 21 || c == 34 || c == 47){
    return '8';
    }
    else if(c == 9 || c == 22 || c == 35 || c == 48){
    return '9';
    }
    else if(c == 10 || c == 23 || c == 36 || c == 49){
    return 'T';
    }
    else if(c == 11 || c == 24 || c == 37 || c == 50){
    return 'J';
    }
    else if(c == 12 || c == 25 || c == 38 || c == 51){
    return 'Q';
    }
    else if(c == 13 || c == 26 || c == 39 || c == 52){
    return 'K';
    }
    else{
    log.log("card is %d", c);
    log.log("Error!!");
    }
    /* UMLRTGEN-USERREGION-END */
}

char Capsule_Player::defineSuit( int c )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Player operation defineSuit */
    //The ASCII codes for clubs, diamonds, hearts, spades are now '\5', '\4', '\3', '\6' respectively.
    if(c > 0 && c <= 13){
    //spades
    return 's';
    }
    else if(c > 13 && c <= 26){
    //hearts
    return 'h';
    }
    else if(c > 26 && c <= 39){
    //diamonds
    return 'd';
    }
    else{
    //clubs
    return 'c';
    }
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Player::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case Ready:
        currentState = state_____Ready( &message );
        break;
    case Got_Card_1:
        currentState = state_____Got_Card_1( &message );
        break;
    default:
        break;
    }
}

void Capsule_Player::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Ready;
}

const char * Capsule_Player::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Player::update_state( Capsule_Player::State newState )
{
    currentState = newState;
}

void Capsule_Player::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Player transition subvertex0,Ready */
    log.log("[Player] ready");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Player::transitionaction_____Receiving_Card_1( const UMLRTMessage * msg )
{
    #define cards ( *(int *)msg->getParam( 0 ) )
    #define p ( *(int *)msg->getParam( 1 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Player transition Ready,Got Card 1,deal:playPort */
    //Store  first dealt card
    i = cards;
    //Call operation to define card and suit for display
    card1[0] = defineCard(i);
    card1[1] = defineSuit(i);
    //Send ack that cards are received
    playPort.ack(i).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef p
    #undef cards
}

void Capsule_Player::transitionaction_____Receiving_Card_2( const UMLRTMessage * msg )
{
    #define cards ( *(int *)msg->getParam( 0 ) )
    #define p ( *(int *)msg->getParam( 1 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Player transition Got Card 1,Ready,deal:playPort */
    //Receive cards
    j = cards;
    player = p;
    //Call operation to define card and suit for display
    card2[0] = defineCard(j);
    card2[1] = defineSuit(j);
    //Send ack that cards are received and log
    log.log("[Player %d] My Cards are %c %c, %c %c", player, card1[0], card1[1], card2[0], card2[1]);
    playPort.ack(j).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef p
    #undef cards
}

void Capsule_Player::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( Ready );
}

void Capsule_Player::actionchain_____Receiving_Card_1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Receiving_Card_1( msg );
    update_state( Got_Card_1 );
}

void Capsule_Player::actionchain_____Receiving_Card_2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Receiving_Card_2( msg );
    update_state( Ready );
}

Capsule_Player::State Capsule_Player::state_____Got_Card_1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_playPort:
        switch( msg->getSignalId() )
        {
        case Play::signal_deal:
            actionchain_____Receiving_Card_2( msg );
            return Ready;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Player::State Capsule_Player::state_____Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_playPort:
        switch( msg->getSignalId() )
        {
        case Play::signal_deal:
            actionchain_____Receiving_Card_1( msg );
            return Got_Card_1;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Player::port_playPort,
        "Play",
        "playPort",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Player::port_log,
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

static void instantiate_Player( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Player );
    slot->capsule = new Capsule_Player( &Player, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Player = 
{
    "Player",
    NULL,
    instantiate_Player,
    0,
    NULL,
    1,
    portroles_border,
    1,
    portroles_internal
};

