
#ifndef DEALER_HH
#define DEALER_HH

#include "Input.hh"
#include "Play.hh"
#include "Tick.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <stdlib.h>
#include <iterator>

class Capsule_Dealer : public UMLRTCapsule
{
public:
    Capsule_Dealer( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Input::Base input;
public:
    enum BorderPortId
    {
        borderport_input,
        borderport_playPort,
        borderport_tickIn,
        borderport_tickOut
    };
protected:
    UMLRTLogProtocol_baserole log;
    Play::Conj playPort;
    Tick::Conj tickIn;
    Tick::Base tickOut;
    UMLRTTimerProtocol_baserole timing;
public:
    enum InternalPortId
    {
        internalport_timing,
        internalport_log
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_input,
        port_log,
        port_playPort,
        port_tickIn,
        port_tickOut,
        port_timing
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
protected:
    int i;
public:
    int players;
protected:
    int k;
    int roundC;
    int r;
    int counter;
    int deck[52];
    int used[52];
    int temp;
    int hands[12];
    int flop[5];
    int seven[7];
public:
    bool hasPair;
    bool hasDubs;
    bool hasTrips;
    bool hasFull;
    bool hasStraight;
    bool hasFlush;
    bool hasQuads;
    bool hasStraightFlush;
    bool hasRoyalFlush;
protected:
    int rank[6];
    int highCount;
    int highestRank;
    int playersInTie[6];
    int tieCounter;
    int tempArr[7];
    int higherNumber;
    int secondHighestNumber;
public:
    int toDigit( char c );
    int random();
    int deal( int r );
    char defineCard( int c );
    char defineSuit( int c );
    bool checkIfUsed( int r );
    int * sort( int arr[7] );
    int * getUnique( int arr[7] );
    int * clearArray( int arr[5], int counter );
    bool checkStraight( int arr[7] );
    bool checkIfCardInArray( int arr[7], int cardToCheck );
    bool checkIfNutStraight( int arr[7] );
    void setUpRoundManually();
    int getHighest( int arr[12], int counter );
    void checkKicker( int playersInTie_new[3], int pt, int split, int higherNumber );
    //Declaring pointers at capsule level
    //Used for flush logic
    int * pTempArr; 
    //To store final hands of all players
    int * finalHands;
    //Used for deciding highest rank
    int* highest;
    

    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Check_Winner,
        Check_Winner__Tie,
        Deal_Cards,
        Deck_Gen,
        Open_Flop,
        Play,
        Play__Hand_Rank,
        Check_Winner__Check_Winner,
        Check_Winner__Declare_Winner,
        Check_Winner__Initial,
        Check_Winner__Tie__Initial,
        Check_Winner__Tie__Tie_on_Dubs,
        Check_Winner__Tie__Tie_on_Flush,
        Check_Winner__Tie__Tie_on_Full,
        Check_Winner__Tie__Tie_on_HighCard,
        Check_Winner__Tie__Tie_on_Pair,
        Check_Winner__Tie__Tie_on_Quads,
        Check_Winner__Tie__Tie_on_St__Flush,
        Check_Winner__Tie__Tie_on_Straight,
        Check_Winner__Tie__Tie_on_Trips,
        Check_Winner__Tie__boundary,
        Check_Winner__boundary,
        Deal_Cards__Continue,
        Deal_Cards__Deal_Card_1,
        Deal_Cards__Deal_Card_2,
        Deal_Cards__Dealing,
        Deal_Cards__Looping,
        Deal_Cards__boundary,
        Deck_Gen__Add_to_Deck,
        Deck_Gen__Initial,
        Deck_Gen__boundary,
        Finish,
        Open_Flop__Looping,
        Open_Flop__boundary,
        Play__Check_Flush,
        Play__Check_Straight,
        Play__Hand_Rank__Initial,
        Play__Hand_Rank__boundary,
        Play__Looping,
        Play__boundary,
        Start,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[43];
    State currentState;
    State history[7];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void update_state( State newState );
    void entryaction_____Deal_Cards__Looping( const UMLRTMessage * msg );
    void entryaction_____Deck_Gen__Initial( const UMLRTMessage * msg );
    void entryaction_____Open_Flop__Looping( const UMLRTMessage * msg );
    void entryaction_____Play__Looping( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Initial( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Next_round( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__No_Tie( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__Evaluate( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__Initial( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalDubs( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalFlush( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalFull( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalHC( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalPair( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalQuads( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalSt_( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalSt_Flush( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__evalTrips( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition10( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition14( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition15( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition18( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition19( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition3( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition6( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition7( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__Tie__transition8( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__decide_Winner( const UMLRTMessage * msg );
    void transitionaction_____Check_Winner__declare( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__deal1( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__deal2( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__transition0( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__transition2( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__transition3( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__transition4( const UMLRTMessage * msg );
    void transitionaction_____Deal_Cards__transition7( const UMLRTMessage * msg );
    void transitionaction_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg );
    void transitionaction_____Deck_Gen__Initial( const UMLRTMessage * msg );
    void transitionaction_____Deck_Gen__Next_Card( const UMLRTMessage * msg );
    void transitionaction_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____Open_Flop__Flop_done( const UMLRTMessage * msg );
    void transitionaction_____Open_Flop__Initial( const UMLRTMessage * msg );
    void transitionaction_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__Initial( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__dubs( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__flush( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__full_house( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__pair( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__straight( const UMLRTMessage * msg );
    void transitionaction_____Play__Hand_Rank__trips( const UMLRTMessage * msg );
    void transitionaction_____Play__Initial( const UMLRTMessage * msg );
    void transitionaction_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg );
    void transitionaction_____Play__flush_st_flush_royal_flush_( const UMLRTMessage * msg );
    void transitionaction_____Play__pair_dubs_trips_quads_fh_( const UMLRTMessage * msg );
    void transitionaction_____Play__straight_( const UMLRTMessage * msg );
    void transitionaction_____Rounds_Left( const UMLRTMessage * msg );
    void transitionaction_____Rounds_played( const UMLRTMessage * msg );
    void transitionaction_____transition1( const UMLRTMessage * msg );
    void transitionaction_____transition2( const UMLRTMessage * msg );
    bool guard_____Check_Winner__No_Tie( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition10( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition11( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition12( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition13( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition14( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition15( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition16( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition17( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition18( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition19( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition2( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition3( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition4( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition5( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition6( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition7( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition8( const UMLRTMessage * msg );
    bool guard_____Check_Winner__Tie__transition9( const UMLRTMessage * msg );
    bool guard_____Deal_Cards__transition3( const UMLRTMessage * msg );
    bool guard_____Deal_Cards__transition4( const UMLRTMessage * msg );
    bool guard_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg );
    bool guard_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg );
    bool guard_____Open_Flop__Flop_done( const UMLRTMessage * msg );
    bool guard_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg );
    bool guard_____Play__AllPlayersAreDone( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____4_of_a_kind( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____dubs( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____full_house( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____royal_flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____st__flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____straight( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank____trips( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__dubs( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__full_house( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__pair( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__straight( const UMLRTMessage * msg );
    bool guard_____Play__Hand_Rank__trips( const UMLRTMessage * msg );
    bool guard_____Play____AllPlayersAreDone( const UMLRTMessage * msg );
    bool guard_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg );
    bool guard_____Play__hasFull_or_hasQuads( const UMLRTMessage * msg );
    bool guard_____Rounds_Left( const UMLRTMessage * msg );
    bool guard_____Rounds_played( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Initial( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Next_round( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__No_Tie( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie_( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__Evaluate( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__Initial( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalDubs( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalFlush( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalFull( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalHC( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalPair( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalQuads( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalSt_( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalSt_Flush( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__evalTrips( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_40_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__new_transition_41_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition10( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition14( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition15( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition18( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition19( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition3( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition6( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition7( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__Tie__transition8( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__decide_Winner( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__declare( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__new_transition_28_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__new_transition_29_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Check_Winner__transition5( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__deal1( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__deal2( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_5( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_6_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__new_transition_7_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition0( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition2( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition3( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition4( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition5( const UMLRTMessage * msg );
    void actionchain_____Deal_Cards__transition7( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__Initial( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__Next_Card( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__Starting( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__new_transition_10_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__new_transition_11_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Deck_Gen__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__Flop_done( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__Initial( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__new_transition_13_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__new_transition_14_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Open_Flop__opening( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__Initial( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__checkRank( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__dubs( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__flush( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__full_house( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__new_transition_22_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__new_transition_23_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__pair( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__straight( const UMLRTMessage * msg );
    void actionchain_____Play__Hand_Rank__trips( const UMLRTMessage * msg );
    void actionchain_____Play__Initial( const UMLRTMessage * msg );
    void actionchain_____Play____AllPlayersAreDone( const UMLRTMessage * msg );
    void actionchain_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg );
    void actionchain_____Play__continue( const UMLRTMessage * msg );
    void actionchain_____Play__flush_st_flush_royal_flush_( const UMLRTMessage * msg );
    void actionchain_____Play__hasFull_or_hasQuads( const UMLRTMessage * msg );
    void actionchain_____Play__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Play__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Play__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Play__new_transition_19_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Play__new_transition_20_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Play__pair_dubs_trips_quads_fh_( const UMLRTMessage * msg );
    void actionchain_____Play__straight_( const UMLRTMessage * msg );
    void actionchain_____Rounds_Left( const UMLRTMessage * msg );
    void actionchain_____Rounds_played( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition6( const UMLRTMessage * msg );
    void actionchain_____transition7( const UMLRTMessage * msg );
    void actionchain_____transition8( const UMLRTMessage * msg );
    State junction_____Check_Winner__Tie__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Check_Winner__Tie__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Check_Winner__Tie__subvertex19( const UMLRTMessage * msg );
    State junction_____Check_Winner__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Check_Winner__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Check_Winner__subvertex4( const UMLRTMessage * msg );
    State junction_____Deal_Cards__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Deal_Cards__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Deck_Gen__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Deck_Gen__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Open_Flop__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Open_Flop__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Play__Hand_Rank__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Play__Hand_Rank__connectionPoint1( const UMLRTMessage * msg );
    State junction_____Play__Hand_Rank__subvertex1( const UMLRTMessage * msg );
    State junction_____Play__connectionPoint0( const UMLRTMessage * msg );
    State junction_____Play__connectionPoint1( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__deephistory( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex1( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex10( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex3( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex4( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex5( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex6( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex7( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex8( const UMLRTMessage * msg );
    State choice_____Check_Winner__Tie__subvertex9( const UMLRTMessage * msg );
    State choice_____Check_Winner__deephistory( const UMLRTMessage * msg );
    State choice_____Check_Winner__subvertex5( const UMLRTMessage * msg );
    State choice_____Deal_Cards__deephistory( const UMLRTMessage * msg );
    State choice_____Deal_Cards__subvertex3( const UMLRTMessage * msg );
    State choice_____Deck_Gen__deephistory( const UMLRTMessage * msg );
    State choice_____Deck_Gen__subvertex0( const UMLRTMessage * msg );
    State choice_____Open_Flop__deephistory( const UMLRTMessage * msg );
    State choice_____Open_Flop__subvertex1( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__deephistory( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex10( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex2( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex3( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex4( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex5( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex6( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex7( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex8( const UMLRTMessage * msg );
    State choice_____Play__Hand_Rank__subvertex9( const UMLRTMessage * msg );
    State choice_____Play__deephistory( const UMLRTMessage * msg );
    State choice_____Play__subvertex2( const UMLRTMessage * msg );
    State choice_____Play__subvertex5( const UMLRTMessage * msg );
    State choice_____subvertex4( const UMLRTMessage * msg );
    State state_____Check_Winner__Check_Winner( const UMLRTMessage * msg );
    State state_____Check_Winner__Declare_Winner( const UMLRTMessage * msg );
    State state_____Check_Winner__Initial( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Initial( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Dubs( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Flush( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Full( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_HighCard( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Pair( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Quads( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_St__Flush( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Straight( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__Tie_on_Trips( const UMLRTMessage * msg );
    State state_____Check_Winner__Tie__boundary( const UMLRTMessage * msg );
    State state_____Check_Winner__boundary( const UMLRTMessage * msg );
    State state_____Deal_Cards__Continue( const UMLRTMessage * msg );
    State state_____Deal_Cards__Deal_Card_1( const UMLRTMessage * msg );
    State state_____Deal_Cards__Deal_Card_2( const UMLRTMessage * msg );
    State state_____Deal_Cards__Dealing( const UMLRTMessage * msg );
    State state_____Deal_Cards__Looping( const UMLRTMessage * msg );
    State state_____Deal_Cards__boundary( const UMLRTMessage * msg );
    State state_____Deck_Gen__Add_to_Deck( const UMLRTMessage * msg );
    State state_____Deck_Gen__Initial( const UMLRTMessage * msg );
    State state_____Deck_Gen__boundary( const UMLRTMessage * msg );
    State state_____Finish( const UMLRTMessage * msg );
    State state_____Open_Flop__Looping( const UMLRTMessage * msg );
    State state_____Open_Flop__boundary( const UMLRTMessage * msg );
    State state_____Play__Check_Flush( const UMLRTMessage * msg );
    State state_____Play__Check_Straight( const UMLRTMessage * msg );
    State state_____Play__Hand_Rank__Initial( const UMLRTMessage * msg );
    State state_____Play__Hand_Rank__boundary( const UMLRTMessage * msg );
    State state_____Play__Looping( const UMLRTMessage * msg );
    State state_____Play__boundary( const UMLRTMessage * msg );
    State state_____Start( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Dealer;

#endif

