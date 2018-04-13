
#ifndef PLAYER_HH
#define PLAYER_HH

#include "Play.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Player : public UMLRTCapsule
{
public:
    Capsule_Player( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    UMLRTLogProtocol_baserole log;
    Play::Base playPort;
public:
    enum BorderPortId
    {
        borderport_playPort
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_log,
        port_playPort
    };
    enum InternalPortId
    {
        internalport_log
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
protected:
    int player;
    char card1[2];
    char card2[2];
    int i;
    int j;
public:
    char defineCard( int c );
    char defineSuit( int c );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Got_Card_1,
        Ready,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[4];
    State currentState;
    void update_state( State newState );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____Receiving_Card_1( const UMLRTMessage * msg );
    void transitionaction_____Receiving_Card_2( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____Receiving_Card_1( const UMLRTMessage * msg );
    void actionchain_____Receiving_Card_2( const UMLRTMessage * msg );
    State state_____Got_Card_1( const UMLRTMessage * msg );
    State state_____Ready( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Player;

#endif

