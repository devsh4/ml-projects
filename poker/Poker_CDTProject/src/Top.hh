
#ifndef TOP_HH
#define TOP_HH

#include "Input.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "umlrtmain.hh"

class Capsule_Top : public UMLRTCapsule
{
public:
    Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        State1,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[3];
    State currentState;
    void update_state( State newState );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    State state_____State1( const UMLRTMessage * msg );
protected:
    Input::Conj input;
public:
    enum InternalPortId
    {
        internalport_input,
        internalport_log
    };
protected:
    UMLRTLogProtocol_baserole log;
public:
    enum PartId
    {
        part_d1,
        part_p1,
        part_p2,
        part_p3,
        part_p4,
        part_p5,
        part_p6
    };
protected:
    const UMLRTCapsulePart * const d1;
    const UMLRTCapsulePart * const p1;
    const UMLRTCapsulePart * const p2;
    const UMLRTCapsulePart * const p3;
    const UMLRTCapsulePart * const p4;
    const UMLRTCapsulePart * const p5;
    const UMLRTCapsulePart * const p6;
public:
    enum PortId
    {
        port_input,
        port_log
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    bool twoDigitRounds;
    bool isValid( char * arg );
};
extern const UMLRTCapsuleClass Top;

#endif

