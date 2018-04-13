
#include "Dealer.hh"

#include "Input.hh"
#include "Play.hh"
#include "Tick.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Dealer::Capsule_Dealer( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, input( borderPorts[borderport_input] )
, playPort( borderPorts[borderport_playPort] )
, tickIn( borderPorts[borderport_tickIn] )
, tickOut( borderPorts[borderport_tickOut] )
, timing( internalPorts[internalport_timing] )
, players( 6 )
, counter( 0 )
, hasPair( false )
, hasDubs( false )
, hasTrips( false )
, hasFull( false )
, hasStraight( false )
, hasFlush( false )
, hasQuads( false )
, hasStraightFlush( false )
, hasRoyalFlush( false )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Check_Winner] = "Check_Winner";
    stateNames[Check_Winner__Tie] = "Check_Winner__Tie";
    stateNames[Deal_Cards] = "Deal_Cards";
    stateNames[Deck_Gen] = "Deck_Gen";
    stateNames[Open_Flop] = "Open_Flop";
    stateNames[Play] = "Play";
    stateNames[Play__Hand_Rank] = "Play__Hand_Rank";
    stateNames[Check_Winner__Check_Winner] = "Check_Winner__Check_Winner";
    stateNames[Check_Winner__Declare_Winner] = "Check_Winner__Declare_Winner";
    stateNames[Check_Winner__Initial] = "Check_Winner__Initial";
    stateNames[Check_Winner__Tie__Initial] = "Check_Winner__Tie__Initial";
    stateNames[Check_Winner__Tie__Tie_on_Dubs] = "Check_Winner__Tie__Tie_on_Dubs";
    stateNames[Check_Winner__Tie__Tie_on_Flush] = "Check_Winner__Tie__Tie_on_Flush";
    stateNames[Check_Winner__Tie__Tie_on_Full] = "Check_Winner__Tie__Tie_on_Full";
    stateNames[Check_Winner__Tie__Tie_on_HighCard] = "Check_Winner__Tie__Tie_on_HighCard";
    stateNames[Check_Winner__Tie__Tie_on_Pair] = "Check_Winner__Tie__Tie_on_Pair";
    stateNames[Check_Winner__Tie__Tie_on_Quads] = "Check_Winner__Tie__Tie_on_Quads";
    stateNames[Check_Winner__Tie__Tie_on_St__Flush] = "Check_Winner__Tie__Tie_on_St__Flush";
    stateNames[Check_Winner__Tie__Tie_on_Straight] = "Check_Winner__Tie__Tie_on_Straight";
    stateNames[Check_Winner__Tie__Tie_on_Trips] = "Check_Winner__Tie__Tie_on_Trips";
    stateNames[Check_Winner__Tie__boundary] = "Check_Winner__Tie__boundary";
    stateNames[Check_Winner__boundary] = "Check_Winner__boundary";
    stateNames[Deal_Cards__Continue] = "Deal_Cards__Continue";
    stateNames[Deal_Cards__Deal_Card_1] = "Deal_Cards__Deal_Card_1";
    stateNames[Deal_Cards__Deal_Card_2] = "Deal_Cards__Deal_Card_2";
    stateNames[Deal_Cards__Dealing] = "Deal_Cards__Dealing";
    stateNames[Deal_Cards__Looping] = "Deal_Cards__Looping";
    stateNames[Deal_Cards__boundary] = "Deal_Cards__boundary";
    stateNames[Deck_Gen__Add_to_Deck] = "Deck_Gen__Add_to_Deck";
    stateNames[Deck_Gen__Initial] = "Deck_Gen__Initial";
    stateNames[Deck_Gen__boundary] = "Deck_Gen__boundary";
    stateNames[Finish] = "Finish";
    stateNames[Open_Flop__Looping] = "Open_Flop__Looping";
    stateNames[Open_Flop__boundary] = "Open_Flop__boundary";
    stateNames[Play__Check_Flush] = "Play__Check_Flush";
    stateNames[Play__Check_Straight] = "Play__Check_Straight";
    stateNames[Play__Hand_Rank__Initial] = "Play__Hand_Rank__Initial";
    stateNames[Play__Hand_Rank__boundary] = "Play__Hand_Rank__boundary";
    stateNames[Play__Looping] = "Play__Looping";
    stateNames[Play__boundary] = "Play__boundary";
    stateNames[Start] = "Start";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 7 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}











void Capsule_Dealer::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_input:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_input, index, true );
            break;
        case borderport_playPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_playPort, index, true );
            break;
        case borderport_tickIn:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_tickIn, index, true );
            break;
        case borderport_tickOut:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_tickOut, index, true );
            break;
        }
}

void Capsule_Dealer::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_input:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_input, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_input], index );
            break;
        case borderport_playPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_playPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_playPort], index );
            break;
        case borderport_tickIn:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_tickIn, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_tickIn], index );
            break;
        case borderport_tickOut:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_tickOut, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_tickOut], index );
            break;
        }
}






























int Capsule_Dealer::toDigit( char c )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation toDigit */
    return (c - '0');
    /* UMLRTGEN-USERREGION-END */
}

int Capsule_Dealer::random()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation random */
    return (rand() % 52)+ 1;
    /* UMLRTGEN-USERREGION-END */
}

int Capsule_Dealer::deal( int r )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation deal */
    //To check for used cards before dealing
    while(checkIfUsed(r)) {
    //log.log("Already used card %d", r);
    r = random();
    //log.log("New card %d", r);
    }
    return r;
    /* UMLRTGEN-USERREGION-END */
}

char Capsule_Dealer::defineCard( int c )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation defineCard */
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
    log.log("Error!!");
    }
    /* UMLRTGEN-USERREGION-END */
}

char Capsule_Dealer::defineSuit( int c )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation defineSuit */
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

bool Capsule_Dealer::checkIfUsed( int r )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation checkIfUsed */
    for(int q=0; q<=k; q++)
    {
    if(r == used[q]) 
    {	
    return true;
    }
    }
    return false;
    /* UMLRTGEN-USERREGION-END */
}

int * Capsule_Dealer::sort( int arr[7] )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation sort */
    //bubble sort
    int n = 7;
    for(int x=0; x<n-1; x++)
    {
    for(int y=0; y<n-x-1; y++)
    {
    if (arr[y] > arr[y+1])
    {	
    //swap(&tempArr[y], &tempArr[y+1]);
    int temp = arr[y];
    arr[y] = arr[y+1];
    arr[y+1] = temp;
    }
    }
    }
    return arr;
    /* UMLRTGEN-USERREGION-END */
}

int * Capsule_Dealer::getUnique( int arr[7] )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation getUnique */
    int prevElement = arr[0];
    for(int i = 1 ; i <= 6 ; i++){
    if(arr[i] == prevElement)
    arr[i] = 100;
    else
    prevElement = arr[i];	
    }
    return arr; 
    /* UMLRTGEN-USERREGION-END */
}

int * Capsule_Dealer::clearArray( int arr[5], int counter )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation clearArray */
    for(int i = 0 ; i < counter; i++){
    arr[i] = -1;
    }
    return arr;
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Dealer::checkStraight( int arr[7] )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation checkStraight */
    int diff = -1;
    int straightCount = 0;
    int index = 0;
    while(index < 6 && straightCount < 4){
    diff = arr[index+1] - arr[index];
    index += 1;
    if(diff == 1)
    straightCount += 1;	
    else
    straightCount = 0;	
    }
    if(checkIfNutStraight(arr))
    {
    for(int i = 0 ; i < 7 ; i++){
    if(arr[i] != 1 && arr[i] != 10 && arr[i] != 11 && arr[i] != 12 && arr[i] != 13 )
    arr[i] = 100;
    }
    sort(arr);
    return true;
    }
    if(straightCount >= 4)
    {	
    int tmpCounter =0;
    for(int index = 0 ; index < 6 ; index++){
    if((arr[index+1] - arr[index] > 1) && arr[index+1] != 100 && tmpCounter < 4){
    arr[index] = 100;
    /*** Modified Code *****/
    //Resets temp counter to 0 as straight is broken
    //and sets all cards before to 100
    if(tmpCounter >  0){
    for(tmpCounter; tmpCounter > 0; tmpCounter--){
    arr[index-tmpCounter] =100;
    }
    }
    /***** Modified code ends ****/
    tmpCounter = 0;
    }
    else if(((arr[index+1] - arr[index] > 1) && arr[index+1] != 100 && tmpCounter >= 4) || (tmpCounter >= 4 && arr[index] == 100)){
    arr[index+1] = 100;
    }
    else if(arr[index+1] - arr[index] == 1){
    tmpCounter++;
    }
    }
    sort(arr);
    return true;
    }
    return false;
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Dealer::checkIfCardInArray( int arr[7], int cardToCheck )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation checkIfCardInArray */
    bool isPresent = false;
    for(int index =0 ; index < 7 ; index++){
    if(arr[index] == cardToCheck){
    isPresent = true;
    break;
    }
    }
    return isPresent;
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Dealer::checkIfNutStraight( int arr[7] )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation checkIfNutStraight */
    //Check if Ace present for NUT STRAIGHT
    if(checkIfCardInArray(arr,1) && checkIfCardInArray(arr,10) && checkIfCardInArray(arr,11) && checkIfCardInArray(arr,12) && checkIfCardInArray(arr,13))
    {
    return true;
    }
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Dealer::setUpRoundManually()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation setUpRoundManually */
    //Player 1 cards in 1-52 range
    hands[0] = 1;
    hands[1] = 52;
    //Player 2 cards 
    hands[2] = 32;
    hands[3] = 13;
    //Player 3 cards 
    hands[4] = 11;
    hands[5] = 15;
    //Player 4 cards 
    hands[6] = 29;
    hands[7] = 45;
    //Player 5 cards 
    hands[8] = 26;
    hands[9] = 37;
    //Player 6 cards 
    hands[10] = 5;
    hands[11] = 29;
    //Flop cards 
    flop[0] = 8; //flop[0] = 14;
    flop[1] = 21; //flop[1] = 17;
    flop[2] = 10; //flop[2] = 18;
    flop[3] = 23; //flop[3] = 23;
    flop[4] = 4; //flop[4] = 24;
    log.log("Manually set new Cards are : ");

    for(int index = 0 ; index < 12; index = index+2){

    char a= hands[index];
    char b= hands[index+1];
    char a1 = defineCard(a);
    char a2 = defineSuit(a);
    char b1 = defineCard(b);
    char b2 = defineSuit(b);
    log.log("%c %c, %c %c ", a1, a2, b1, b2);
    }
    log.log("Manually set new flop is: ");

    for(int index = 0 ; index < 5; index++)
    {
    char a = defineCard(flop[index]);
    char b = defineSuit(flop[index]);
    log.log("%c %c",a,b);
    }
    /* UMLRTGEN-USERREGION-END */
}

int Capsule_Dealer::getHighest( int arr[12], int counter )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation getHighest */
    //To get the highest number
    int x = 0;
    //Find highest number
    for(int i=0; i < counter;i++)
    {
    if(arr[i] > x && arr[i] < 15)
    {	
    x = arr[i];	
    }
    }
    return x;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Dealer::checkKicker( int playersInTie_new[3], int pt, int split, int higherNumber )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer operation checkKicker */
    int split_new = 0;
    int flag = 0;
    int temp1[tieCounter];
    int tempC = 0;
    int b = 0;
    //Case: If one player only has the highest pair
    if(split == 1)
    {	
    //Higher pair winner
    if(hasPair){
    log.log("[Dealer] || Player %d wins the round with higher pair! ||", playersInTie_new[0]);
    }else if(hasTrips){
    log.log("[Dealer] || Player %d wins the round with higher trips! ||", playersInTie_new[0]);	
    }
    else if(hasDubs)
    {
    log.log("[Dealer] || Player %d wins the round with higher dubs! ||", playersInTie_new[0]);
    }

    }
    //else for same highest pair but kicker case
    else if(split > 1)
    {				
    if(hasPair){
    log.log("[Dealer] Same Pair, check kicker?");
    }else if(hasTrips){
    log.log("[Dealer] Same Trips, check kicker?");	
    }else if(hasDubs)
    {
    log.log("[Dealer] Same Dubs, check kicker?");
    }

    for(int x=0; x < pt; x++)
    {
    //To get players who have same highest pair
    int a = playersInTie_new[x]; 
    a = a*2;

    hands[a-1] = hands[a-1] % 13;
    hands[a-2] = hands[a-2] % 13;
    int c1= (hands[a-1] == 0) ? 13 : ((hands[a-1] == 1) ? 14 : hands[a-1]);
    int c2= (hands[a-2] == 0) ? 13 : ((hands[a-2] == 1) ? 14 : hands[a-2]);

    //Check kicker and store in temp
    if(c1 == higherNumber)
    {
    temp1[tempC] = c2;

    }else if(c2 == higherNumber){
    temp1[tempC] = c1;
    }	
    else{
    if(c1 >= c2){
    temp1[tempC] = c1;
    }
    else{
    temp1[tempC] = c2;
    }
    }
    tempC++;
    }	

    tieCounter = split;	

    //Get highest kicker
    int hkicker = getHighest(temp1, tieCounter);
    //log.log("[Dealer] Higher kicker is %d", hkicker);


    //Check which player has highest kicker
    for(int x=0; x < pt; x++)
    {
    if(temp1[x] == hkicker)
    {
    split_new++;
    b = playersInTie_new[x];

    //Further check if kicker is greater than one of the flop cards
    for(int fl=0; fl<5;fl++)
    {
    //Mod to convert to 1-13
    flop[fl] = flop[fl] % 13;
    flop[fl] = (flop[fl] == 0) ? 13 : ((flop[fl] == 1) ? 14 : flop[fl]);
    if(flop[fl] != higherNumber)
    {
    if(flop[fl] != secondHighestNumber)
    {
    if(temp1[x] < flop[fl])
    {
    //log.log("kicker %d < flop card %d", temp1[x], flop[fl]);
    flag++;
    }
    }
    }
    }

    }

    }

    //Print winner
    //Check common kicker or not?
    if(hasPair)
    {
    if(flag >= 3 || split_new > 1)
    {
    log.log("[Dealer] || Split POT! ||");
    }	
    else{
    log.log("[Dealer] || Player %d wins the round with kicker! ||", b);
    }

    }
    else if(hasTrips)
    {
    if(flag >= 2 || split_new > 1)
    {
    log.log("[Dealer] || Split POT! ||");
    }	
    else{
    log.log("[Dealer] || Player %d wins the round with kicker! ||", b);
    }

    }
    else if(hasDubs){
    if(flag >= 1 || split_new > 1)
    {
    log.log("[Dealer] || Split POT! ||");
    }	
    else{
    log.log("[Dealer] || Player %d wins the round with kicker! ||", b);
    }

    }
    }/* UMLRTGEN-USERREGION-END */
}


void Capsule_Dealer::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case Finish:
        currentState = state_____Finish( &message );
        break;
    case Start:
        currentState = state_____Start( &message );
        break;
    case Deal_Cards__Deal_Card_1:
        currentState = state_____Deal_Cards__Deal_Card_1( &message );
        break;
    case Deal_Cards__Looping:
        currentState = state_____Deal_Cards__Looping( &message );
        break;
    case Deal_Cards__Dealing:
        currentState = state_____Deal_Cards__Dealing( &message );
        break;
    case Deal_Cards__Continue:
        currentState = state_____Deal_Cards__Continue( &message );
        break;
    case Deal_Cards__Deal_Card_2:
        currentState = state_____Deal_Cards__Deal_Card_2( &message );
        break;
    case Deal_Cards__boundary:
        currentState = state_____Deal_Cards__boundary( &message );
        break;
    case Deck_Gen__Initial:
        currentState = state_____Deck_Gen__Initial( &message );
        break;
    case Deck_Gen__Add_to_Deck:
        currentState = state_____Deck_Gen__Add_to_Deck( &message );
        break;
    case Deck_Gen__boundary:
        currentState = state_____Deck_Gen__boundary( &message );
        break;
    case Open_Flop__Looping:
        currentState = state_____Open_Flop__Looping( &message );
        break;
    case Open_Flop__boundary:
        currentState = state_____Open_Flop__boundary( &message );
        break;
    case Play__Looping:
        currentState = state_____Play__Looping( &message );
        break;
    case Play__Check_Straight:
        currentState = state_____Play__Check_Straight( &message );
        break;
    case Play__Check_Flush:
        currentState = state_____Play__Check_Flush( &message );
        break;
    case Play__boundary:
        currentState = state_____Play__boundary( &message );
        break;
    case Play__Hand_Rank__Initial:
        currentState = state_____Play__Hand_Rank__Initial( &message );
        break;
    case Play__Hand_Rank__boundary:
        currentState = state_____Play__Hand_Rank__boundary( &message );
        break;
    case Check_Winner__Initial:
        currentState = state_____Check_Winner__Initial( &message );
        break;
    case Check_Winner__Check_Winner:
        currentState = state_____Check_Winner__Check_Winner( &message );
        break;
    case Check_Winner__Declare_Winner:
        currentState = state_____Check_Winner__Declare_Winner( &message );
        break;
    case Check_Winner__boundary:
        currentState = state_____Check_Winner__boundary( &message );
        break;
    case Check_Winner__Tie__Initial:
        currentState = state_____Check_Winner__Tie__Initial( &message );
        break;
    case Check_Winner__Tie__Tie_on_HighCard:
        currentState = state_____Check_Winner__Tie__Tie_on_HighCard( &message );
        break;
    case Check_Winner__Tie__Tie_on_Pair:
        currentState = state_____Check_Winner__Tie__Tie_on_Pair( &message );
        break;
    case Check_Winner__Tie__Tie_on_Trips:
        currentState = state_____Check_Winner__Tie__Tie_on_Trips( &message );
        break;
    case Check_Winner__Tie__Tie_on_Flush:
        currentState = state_____Check_Winner__Tie__Tie_on_Flush( &message );
        break;
    case Check_Winner__Tie__Tie_on_Straight:
        currentState = state_____Check_Winner__Tie__Tie_on_Straight( &message );
        break;
    case Check_Winner__Tie__Tie_on_Dubs:
        currentState = state_____Check_Winner__Tie__Tie_on_Dubs( &message );
        break;
    case Check_Winner__Tie__Tie_on_Full:
        currentState = state_____Check_Winner__Tie__Tie_on_Full( &message );
        break;
    case Check_Winner__Tie__Tie_on_Quads:
        currentState = state_____Check_Winner__Tie__Tie_on_Quads( &message );
        break;
    case Check_Winner__Tie__Tie_on_St__Flush:
        currentState = state_____Check_Winner__Tie__Tie_on_St__Flush( &message );
        break;
    case Check_Winner__Tie__boundary:
        currentState = state_____Check_Winner__Tie__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Dealer::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Start;
}

const char * Capsule_Dealer::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Dealer::save_history( Capsule_Dealer::State compositeState, Capsule_Dealer::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Dealer::check_history( Capsule_Dealer::State compositeState, Capsule_Dealer::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Dealer::update_state( Capsule_Dealer::State newState )
{
    currentState = newState;
}

void Capsule_Dealer::entryaction_____Deal_Cards__Looping( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards::Looping entry  */
    //Self commmunication
    tickOut.tick().send();
    //Incrementing counter for number of players to whom the cards have been dealt 
    temp++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::entryaction_____Deck_Gen__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen::Initial entry  */
    i++;
    //Self communication
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::entryaction_____Open_Flop__Looping( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop::Looping entry  */
    //Self communication
    tickOut.tick().send();
    //Increment counter
    counter++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::entryaction_____Play__Looping( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Looping entry  */
    //Increment Player counter
    i++;
    //Increment hands counter 
    temp= temp+2;
    //Self communicate
    tickOut.tick().send();
    //Set all boolean hand attributes to false
    hasPair = false;
    hasDubs = false;
    hasTrips = false;
    hasQuads = false;
    hasStraight = false;
    hasFlush = false;
    hasFull = false;
    hasStraightFlush = false;
    hasRoyalFlush = false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner transition Check Winner::connectionPoint0,Check Winner::Initial */
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Next_round( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner transition Check Winner::subvertex4,Check Winner::connectionPoint1 */
    log.log("[Dealer] --- Round %d Over ---", r);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__No_Tie( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner transition Check Winner::subvertex5,Check Winner::Declare Winner */
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__Evaluate( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Initial,Check Winner::Tie::subvertex1,tick:tickIn */
    //To determine which players on Tie
    tieCounter = 0;
    for(int x=0; x < players; x++){
    if(rank[x]==highestRank)
    {	
    playersInTie[tieCounter] = x+1; 
    tieCounter++;
    log.log("[Dealer] Player %d is in a tie", x+1);
    }
    }

    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::connectionPoint0,Check Winner::Tie::Initial */
    log.log("[Dealer] It is a Tie!");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalDubs( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Dubs,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int c = 0;
    int newC = tieCounter*2;
    int temp[newC];
    int split = 0;
    int checking = 0;
    int playersInTie_new[3];

    hasTrips = false;
    hasPair = false;
    hasDubs = true;
    int pt = 0;
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];
    t = (t-1) * 7;
    //Store double pair number, i.e. one number for each pair
    if(finalHands[t] == 1)
    {	
    temp[c] = (finalHands[t+4] == 100) ? (finalHands[t+2]): (finalHands[t+4]); 
    temp[c+1] = 14;
    }
    else{
    if(finalHands[t+4] == 100){
    temp[c] = finalHands[t]; 
    temp[c+1] = finalHands[t+2];
    }
    else{
    temp[c] = finalHands[t+2]; 
    temp[c+1] = finalHands[t+4];
    }
    }
    c = c+2;
    log.log("[Dealer]  Player %d: %d %d %d",  playersInTie[x], finalHands[t], finalHands[t+2], finalHands[t+4]);
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, newC);
    log.log("[Dealer] Higher pair is: %d", higherNumber);


    //To check higher lower pair out of the dubs
    for(int x=0; x< newC; x++)
    {
    if(temp[x] == higherNumber)
    {	
    checking++;
    //Meaning higher pair on the flop out of the dubs 

    }
    }

    if(checking > 1)
    {	
    log.log("[Dealer] Checking second highest pair...");
    //Replace highest number with zero to recalculate second highest number
    for(int j=1;j < newC; j=j+2)
    {
    if(temp[j] == higherNumber)
    {
    temp[j] = 0;
    }
    else{
    temp[j] = 0;
    temp[j-1] = 0;
    }
    }
    secondHighestNumber = getHighest(temp, newC);
    log.log("[Dealer] Second highest pair is: %d", secondHighestNumber);

    //Print winners
    for(int x=1; x <= newC; x++){

    if(temp[x-1] == secondHighestNumber)
    {	
    //To check if number is odd or even and then chose player ID based on it.
    if(x % 2 == 0)
    {	
    split++;
    //If else for kicker case
    int y = x/2;
    playersInTie_new[pt] = playersInTie[y-1];
    pt++;
    }
    else{
    split++;
    int y = x+1;
    y = y/2;
    playersInTie_new[pt] = playersInTie[y-1];
    pt++;
    }
    }	

    }

    }
    else{
    //Print winners
    for(int x=1; x <= newC; x++){

    if(temp[x-1] == higherNumber)
    {	
    //To check if number is odd or even and then chose player ID based on it.
    if(x % 2 == 0)
    {	
    split++;
    //If else for kicker case
    int y = x/2;
    playersInTie_new[pt] = playersInTie[y-1];
    pt++;
    }
    else{
    split++;
    int y = x+1;
    y = y/2;
    playersInTie_new[pt] = playersInTie[y-1];
    pt++;
    }
    }	

    }
    }

    //Split pot? Call function
    checkKicker(playersInTie_new, pt, split, higherNumber);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalFlush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Flush,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int h = 0;
    int c = 0;
    int c1 = 0;
    int temp[tieCounter];
    int split = 0;
    int counter = 0;
    int topFlop=0;
    //Store tied players hands
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];

    //For hands array
    h = (t-1) * 2;
    //For finalhands array
    t = (t-1) * 7;

    //Compare flop with hand array and replace with 100 if same
    for(int p = 0; p < 5; p++)
    {
    for(int q = t; q < (t+7); q++)
    {

    //compare hands with flop array for weeding out common flush cards
    flop[p] = ((flop[p] % 13) == 0) ? 13 : (flop[p] % 13);
    hands[h] = ((hands[h] % 13) == 0) ? 13 : (hands[h] % 13);  
    hands[h+1] = ((hands[h+1] % 13) == 0) ? 13 : (hands[h+1] % 13);  

    if(finalHands[q] == flop[p])
    {	  
    //log.log("replacing %d by 100", finalHands[q]);
    finalHands[q] = 100;  
    }
    }
    }
    for(int i=t;i<t+7;i++)
    {
    finalHands[i] = (finalHands[i] == 1) ? 14 : finalHands[i]; 
    if(finalHands[i] != 100)
    {
    temp[c] = (finalHands[i] == 1) ? 14 : finalHands[i];

    if(temp[c]==14){
    i++;
    }
    log.log("[Dealer]  Player %d: %d", playersInTie[x], temp[c]);
    c1++;
    }
    else{
    counter++;
    }
    }
    c++;
    if(counter > 6){
    log.log("[Dealer] Top flop!");
    topFlop++;
    }

    counter = 0;

    }

    //Call function to get the highest number
    if(c1 > 0)
    {
    higherNumber = getHighest(temp, c);
    log.log("[Dealer] Higher flush card is: %d", higherNumber); 
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    split++;
    log.log("[Dealer] Player %d wins the round with higher flush!", playersInTie[x]);
    }
    }
    }
    if(topFlop == tieCounter)
    {
    log.log("[Dealer] Flop flush, Split POT!");
    }
    else if(split>1)
    {
    log.log("[Dealer] Split POT!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalFull( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Full,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int tc = 0;
    int pc = 0;
    int trips[tieCounter];
    int pair[tieCounter];
    //Store tied players hands
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];	
    t = (t-1) * 7;

    //Three ways the finalHandsArray can have full house combinations 
    if(finalHands[t] == finalHands[t+1] && finalHands[t+1] == finalHands[t+2]){
    trips[tc] = (finalHands[t] == 1) ? 14 : finalHands[t];
    pair[pc] = (finalHands[t+5] == 100) ? ((finalHands[t+3] == 1) ? 14 : finalHands[t+3]) : finalHands[t+5];
    log.log("[Dealer]  Player %d: %d %d", playersInTie[x], trips[tc], pair[tc]); 
    tc++;
    pc++;
    }
    else if(finalHands[t] == finalHands[t+1] && finalHands[t+2] == finalHands[t+3] && finalHands[t+2] != finalHands[t+4]){
    pair[pc] = (finalHands[t+2] == 1) ? 14 : finalHands[t+2];
    trips[tc] = (finalHands[t+4] == 1) ? 14 : finalHands[t+4];
    log.log("[Dealer]  Player %d: %d %d", playersInTie[x], trips[tc], pair[tc]);
    tc++;
    pc++;
    }
    else{
    pair[pc] = (finalHands[t+5] == 100) ? ((finalHands[t] == 1) ? 14 : finalHands[t]) : finalHands[t+5];
    trips[tc] = (finalHands[t+2] == 1) ? 14 : finalHands[t+2];
    log.log("[Dealer]  Player %d: %d %d", playersInTie[x], trips[tc], pair[tc]);
    tc++;
    pc++;
    }

    }
    //Call function to get the highest number
    int higherTrips = getHighest(trips, tieCounter);
    int higherPair = getHighest(pair, tieCounter);
    log.log("[Dealer] Higher trips is: %d", higherTrips);
    log.log("[Dealer] Higher pair is: %d", higherPair);
    int hasTrips = 0;
    int hasPair = 0;
    int tripsWinner = 0;
    int pairWinner = 0;
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(trips[x] == higherTrips)
    {		 
    hasTrips++;
    tripsWinner = playersInTie[x];
    }
    if(pair[x] == higherPair)
    {
    hasPair++;
    pairWinner = playersInTie[x];
    }

    }
    if(hasTrips == 1)
    {
    log.log("[Dealer] || Player %d wins the round with higher full house! ||", tripsWinner);
    }
    else if(hasTrips > 1 && hasPair == 1){
    log.log("[Dealer] || Player %d wins the round with higher full house! ||", pairWinner);
    }
    else{
    log.log("[Dealer] || SPLIT POT! ||");
    }

    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalHC( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on HighCard,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int c = 0;
    int newC = tieCounter*2;
    int temp[newC];
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];
    t = t*2;

    //Store all hands of tied players in a temp array
    temp[c] = ((hands[t-2] % 13) == 0) ? 13 : ((hands[t-2] % 13) == 1) ? 14 : (hands[t-2] % 13); 
    temp[c+1] = ((hands[t-1] % 13) == 0) ? 13 : ((hands[t-1] % 13) == 1) ? 14 : (hands[t-1] % 13); 

    log.log("[Dealer]  Player %d: %d, %d",playersInTie[x], temp[c], temp[c+1]);
    c = c+2;	
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, newC);
    log.log("[Dealer] Higher high card is: %d", higherNumber); 
    int split = 0;
    //Print winners
    for(int x=1; x <= newC; x++){
    if(temp[x-1] == higherNumber)
    {	
    //To check if number is odd or even and then chose player ID based on it.
    if(x % 2 == 0)
    {
    int y = x/2; 
    log.log("[Dealer] || Player %d wins this round with the high card %d! ||", playersInTie[y-1], higherNumber);
    split++;
    }
    else{
    int y = x+1;
    y = y/2;
    log.log("[Dealer] || Player %d win this round with the higher card! %d ||", playersInTie[y-1], higherNumber);
    split++;
    }
    }
    }
    //Split pot?
    if(split > 1)
    {
    log.log("[Dealer] SPLIT POT!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalPair( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Pair,Check Winner::Tie::subvertex19,tick:tickIn */
    //Counter for finalHands Array
    int t = 0;
    //Counter for temp array
    int c = 0;
    int temp[tieCounter];
    int playersInTie_new[3];
    //To count split pot scenario
    int split=0;
    //New tieCounter based on players having exactly same pair
    int pt=0;
    hasTrips = false;
    hasDubs = false;
    hasPair = true;
    //Store player hands from finalHands array to temp array
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x]; 

    //Setting counter to access global hand array
    t = (t-1) * 7;

    //Store pair number, handle case for ACE
    temp[c] = (finalHands[t] == 1) ? 14 : (finalHands[t]); 
    c++;
    log.log("[Dealer]  Player %d: %d", playersInTie[x], finalHands[t]);
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, tieCounter);
    log.log("[Dealer] Higher pair is: %d", higherNumber); 
    //Check highest pair
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    split++;
    playersInTie_new[pt] = playersInTie[x];
    pt++;
    }
    }
    //Call function to declare winner if sole high pair winner else same pair higher kicker winner
    checkKicker(playersInTie_new, pt, split, higherNumber);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalQuads( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Quads,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int c = 0;
    int temp[tieCounter];
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];
    t = (t-1) * 7;

    //Store quads number and handle case for ACE
    if(finalHands[t] == finalHands[t+2]){

    temp[c] = (finalHands[t] == 1) ? 14 : finalHands[t];

    }
    else{
    temp[c] = finalHands[t+2];
    }

    c++;
    log.log("[Dealer]  Player %d: %d", playersInTie[x], finalHands[t+2]);
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, tieCounter);
    log.log("[Dealer] Higher quads is: %d", higherNumber); 
    int split = 0;
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    split++;
    log.log("[Dealer] || Player %d wins the round with higher quads! ||", playersInTie[x]);
    }
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalSt_( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Straight,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int c = 0;
    int temp[tieCounter];
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];	
    t = (t-1) * 7;

    //Handle ace
    if(finalHands[t] == 1 && finalHands[t+1] != 2){
    finalHands[t] = 14;	
    temp[c] = finalHands[t];

    }else{	
    //Store last card of straight
    temp[c] = (finalHands[t+6] == 100) ? ((finalHands[t+5] == 100) ? finalHands[t+4] : finalHands[t+5]) : (finalHands[t+6]);
    } 

    log.log("[Dealer]  Player %d: %d", playersInTie[x], temp[c]);	
    c++;
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, tieCounter);
    log.log("[Dealer] Higher straight with: %d", higherNumber); 
    int split = 0;
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    split++;
    log.log("[Dealer] || Player %d wins the round with higher straight! ||", playersInTie[x]);
    }
    }
    //Split pot?
    if(split > 1)
    {
    log.log("[Dealer] SPLIT POT!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalSt_Flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on St. Flush,Check Winner::Tie::subvertex19,tick:tickIn */
    int t = 0;
    int c = 0;
    int temp[tieCounter];
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];
    t = (t-1) * 7;

    //Handle ace
    if(finalHands[t] == 1 && finalHands[t+1] != 2){
    finalHands[t] = 14;	
    temp[c] = finalHands[t];

    }else{	
    //Store last card of straight
    temp[c] = (finalHands[t+6] == 100) ? ((finalHands[t+5] == 100) ? finalHands[t+4] : finalHands[t+5]) : (finalHands[t+6]);
    } 
    log.log("[Dealer]  Player %d: %d", playersInTie[x] ,temp[c]);	
    c++;
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, tieCounter);
    log.log("[Dealer] Higher straight flush with: %d", higherNumber); 
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    log.log("[Dealer] || Player %d wins the round with higher straight flush! ||", playersInTie[x]);
    }
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__evalTrips( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::Tie on Trips,Check Winner::Tie::subvertex19,tick:tickIn */
    //Counter for finalHands Array
    int t = 0;
    //Counter for temp array
    int c = 0;
    int temp[tieCounter];
    int playersInTie_new[3];
    //To count split pot scenario
    int split=0;
    //New tieCounter based on players having exactly same pair
    int pt=0;
    hasPair = false;
    hasDubs = false;
    hasTrips = true;
    for(int x=0; x < tieCounter;x++)
    {
    //Access hands of players based on their ID from playersInTie array
    t = playersInTie[x];
    t = (t-1) * 7;

    //Store trips number and handle case for ACE
    temp[c] = (finalHands[t] == 1) ? 14 : (finalHands[t]); 
    c++;
    log.log("[Dealer]  Player %d: %d", playersInTie[x], finalHands[t]);
    }
    //Call function to get the highest number
    higherNumber = getHighest(temp, tieCounter);
    log.log("[Dealer] Higher trips is: %d", higherNumber); 
    //Print winners
    for(int x=0; x < tieCounter; x++){
    if(temp[x] == higherNumber)
    {		 
    split++;
    playersInTie_new[pt] = playersInTie[x];
    pt++;
    }
    }
    //Call function to declare winner if sole high pair winner else same pair higher kicker winner
    checkKicker(playersInTie_new, pt, split, higherNumber);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex6,Check Winner::Tie::Tie on Straight */
    log.log("[Dealer] Tie on Straight");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition14( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex5,Check Winner::Tie::Tie on Flush */
    log.log("[Dealer] Tie on Flush");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition15( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex4,Check Winner::Tie::Tie on Full */
    log.log("[Dealer] Tie on Full House");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition18( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex9,Check Winner::Tie::Tie on Quads */
    log.log("[Dealer] Tie on Four of a Kind");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition19( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex10,Check Winner::Tie::Tie on St. Flush */
    log.log("[Dealer] Tie on Straight Flush");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex1,Check Winner::Tie::Tie on HighCard */
    log.log("[Dealer] Tie on High Card");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex3,Check Winner::Tie::Tie on Pair */
    log.log("[Dealer] Tie on a Pair");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex8,Check Winner::Tie::Tie on Dubs */
    log.log("[Dealer] Tie on Dubs");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__Tie__transition8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie transition Check Winner::Tie::subvertex7,Check Winner::Tie::Tie on Trips */
    log.log("[Dealer] Tie on Trips");
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__decide_Winner( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner transition Check Winner::Initial,Check Winner::Check Winner,tick:tickIn */
    //Array to compare players based on rank
    highest = new int[players];
    //Variables
    highestRank = 0;
    highCount = 0;
    int highestTempIndex = 0;
    //Call clear array operation
    highest = clearArray(highest, players);
    for(int i=0; i< players; i++)
    {
    //Finding highest rank
    if(rank[i] > highestRank){

    highestRank = rank[i];
    highestTempIndex = 0;
    //highest = clearArray(highest);
    highest[highestTempIndex] = i;
    highCount = 1;
    highestTempIndex++;	
    }
    else if(rank[i] == highestRank){
    highCount++;
    highest[highestTempIndex] = i;
    highestTempIndex++;
    }
    }
    //Uncomment below code to print finalHand array
    /*log.log("Global Final Hand Array: ");
    for(int index = 0 ; index < (players * 7) ; index++)
    {
    log.log("%d",finalHands[index]);
    }
    */
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Check_Winner__declare( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner transition Check Winner::Declare Winner,Check Winner::subvertex4,tick:tickIn */
    log.log("[Dealer] || Player %d wins the round! ||", highest[0]+1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__deal1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::Dealing,Deal Cards::Deal Card 1,tick:tickIn */
    int randomCard = random();
    //Call operation
    randomCard = deal(randomCard);
    //Used array to keep count of cards already distributed
    used[k] = randomCard;
    k++;
    //log.log("first card sent to Player %d", deck[randomCard]);
    //Deal
    playPort.deal(deck[randomCard], temp).sendAt(temp-1);
    log.log("[Dealer] dealing first card to Player %d", temp);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__deal2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::Continue,Deal Cards::Deal Card 2,tick:tickIn */
    int randomCard  = random();
    //Call operation
    randomCard  = deal(randomCard);
    //Used deck
    used[k] = randomCard;
    k++;
    //Deal
    playPort.deal(deck[randomCard], temp).sendAt(temp-1);
    log.log("[Dealer] dealing second card to Player %d", temp);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__transition0( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::connectionPoint0,Deal Cards::Looping */
    //Initialize counter for no. of players 
    temp = 0;
    //Initialize counter for used deck array 
    k = 0;
    //Hands array counter
    i = 0;
    //Initializing global array to store final hands
    finalHands = new int[players*7];
    //Empty 'used cards' array
    for(int x=0; x<52;x++)
    {
    used[x] = -1;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__transition2( const UMLRTMessage * msg )
{
    #define c ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::Deal Card 1,Deal Cards::Continue,ack:playPort */
    //Received acknowledge from player and storing player hand in 'hands' array
    hands[i] = c;
    //Self commmunication
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef c
}

void Capsule_Dealer::transitionaction_____Deal_Cards__transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::subvertex3,Deal Cards::connectionPoint1 */
    log.log("[Dealer] Dealt cards");
    int playerCount = 1;
    for(int i=0; i < (players * 2); i=i+2)
    {
    char card = defineCard(hands[i]);
    char suit = defineSuit(hands[i]);
    char card1 = defineCard(hands[i+1]);
    char suit1 = defineSuit(hands[i+1]);
    log.log("Player %d: %c %c, %c %c", playerCount, card, suit, card1, suit1);
    playerCount++;
    }
    //Print used array
    /*for(int x=0; x<=52;x++)
    {
    if(!(used[x] == -1))
    log.log("%d", used[x]);
    }*/
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::subvertex3,Deal Cards::Dealing */
    //Self communication
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deal_Cards__transition7( const UMLRTMessage * msg )
{
    #define c ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards transition Deal Cards::Deal Card 2,Deal Cards::Looping,ack:playPort */
    //Received acknowledge from player and storing player hand in 'hands' array
    hands[i+1] = c;
    //Incrementing counter by 2 for 'hands' array
    i=i+2;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef c
}

void Capsule_Dealer::transitionaction_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen transition Deck Gen::subvertex0,Deck Gen::connectionPoint1 */
    log.log("[Dealer] Deck Ready");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deck_Gen__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen transition Deck Gen::connectionPoint0,Deck Gen::Initial */
    i = 0;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deck_Gen__Next_Card( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen transition Deck Gen::Add to Deck,Deck Gen::Initial,tick:tickIn */
    //Store card in deck
    deck[i-1] = i;	
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen transition Deck Gen::subvertex0,Deck Gen::Add to Deck */
    //Self communication
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer transition subvertex0,Start */
    log.log("[Dealer] Starting Game!");
    //Initialize seed
    srand(time(0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Open_Flop__Flop_done( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop transition Open Flop::subvertex1,Open Flop::connectionPoint1 */
    log.log("[Dealer] Flop opened");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Open_Flop__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop transition Open Flop::connectionPoint0,Open Flop::Looping */
    log.log("[Dealer] Time to open the flop!");
    //Counter for opening flop
    counter = 0;
    //Counter for 'flop' array
    i=0;
    log.log("[Dealer] Flop:");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop transition Open Flop::subvertex1,Open Flop::Looping */
    //Call random number generator
    int randomCard = random();
    //Call operation to check used array in order to draw out unique cards
    randomCard = deal(randomCard);
    //Used array to keep count of cards already distributed
    used[k] = randomCard;
    k++;
    //Card on flop
    randomCard = deck[randomCard];
    //Call operation to define card and suit for display
    char card = defineCard(randomCard);
    char suit = defineSuit(randomCard);
    log.log("[Dealer] %c %c", card, suit);
    //Store
    flop[i] = randomCard;
    i++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex4,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 8;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::connectionPoint0,Play::Hand Rank::Initial */
    //Self communicate
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__dubs( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex9,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 3;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex6,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 6;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__full_house( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex5,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 7;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex10,Play::Hand Rank::connectionPoint1 */
    //Set rank
    rank[i-1] = 1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__pair( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex10,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 2;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex2,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 10;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex3,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 9;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__straight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex8,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 5;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Hand_Rank__trips( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank transition Play::Hand Rank::subvertex7,Play::Hand Rank::subvertex1 */
    //Set rank
    rank[i-1] = 4;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play transition Play::connectionPoint0,Play::Looping */
    //Uncomment below line to manually set a round for testing rare hands or cases
    //setUpRoundManually();
    //Player counter
    i=0;
    //'hands' array counter
    temp=-2;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play transition Play::subvertex5,Play::Check Straight */
    //Self message
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__flush_st_flush_royal_flush_( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play transition Play::Check Flush,Play::Hand Rank::connectionPoint0,tick:tickIn */
    //Array declaration for each suit
    int* s =new int[7];
    int* h =new int[7]; 
    int* d =new int[7]; 
    int* c =new int[7];

    //Counter for each suit
    int spades = 0;
    int hearts = 0;
    int diamonds = 0;
    int clubs = 0;
    int counter = 0;
    int flushCount = 5;
    int flushSuit = -1;
    //Store flop in tempArr
    for(int z = 0; z<=6; z++)
    {
    tempArr[z] = seven[z];	
    //initialize to avoid dealing with garbage values
    s[z] = 100;
    h[z] = 100;
    d[z] = 100; 
    c[z] = 100;
    }
    //Condition for flush
    for(int j=0; j<=6; j++)
    {
    char temp = defineSuit(tempArr[j]);
    if(temp == 's')
    {		
    spades++;
    s[counter] = tempArr[j];
    if(spades >= flushCount)
    {	
    flushSuit = 0;
    }
    }
    else if(temp == 'h')
    {	
    hearts++;
    h[counter] = tempArr[j];
    if(hearts >= flushCount)
    {	
    flushSuit = 1;
    }
    }
    else if(temp == 'd')
    {
    diamonds++;
    d[counter] = tempArr[j];
    if(diamonds >= flushCount)
    {		
    flushSuit = 2;
    }
    }
    else
    {
    clubs++;
    c[counter] = tempArr[j];
    if(clubs >= flushCount)
    {	
    flushSuit = 3;
    }
    }
    counter++;
    }

    sort(s);
    sort(h);
    sort(d);
    sort(c);
    //Check if flush
    if(flushSuit >= 0)
    {
    int* tmpFlushCards = new int[7];
    log.log("[Dealer] Player %d has a flush", i);
    hasFlush = true;
    //Check flush suit?
    if(flushSuit == 0)
    {
    tmpFlushCards=s;
    //log.log("Spades Flush!");
    }
    else if(flushSuit == 1)
    {
    tmpFlushCards =h;
    //log.log("Hearts Flush!");
    }
    else if(flushSuit == 2)
    {
    tmpFlushCards =d;
    //log.log("Diamonds Flush!");
    }
    else
    {
    tmpFlushCards =c;
    //log.log("Clubs Flush!");
    }
    //If you want cards with suit in the globalHandArray , use the below commented code and delete the similar code active below
    /*sort(tmpFlushCards);
    int counter = 0;
    //Code to add final hand array to globalHandArray if it is a flush
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++){
    finalHands[index] = tmpFlushCards[counter];
    counter++;
    }*/
    //Code to convert from 1 - 13
    for(int k = 0 ; k < 7 ; k++){
    if(tmpFlushCards[k] != 100)
    tmpFlushCards[k] = ((tmpFlushCards[k] % 13) == 0) ? 13 : (tmpFlushCards[k] % 13);
    }
    //Get unique cards and sort
    getUnique(tmpFlushCards);
    sort(tmpFlushCards);
    /*log.log("Flush Cards :");
    for(int k = 0 ; k < 7 ; k++){
    log.log("%d",tmpFlushCards[k]);
    }*/
    int tmpCounter = 0;
    //Code to add final hand array to globalHandArray if it is a flush
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++){
    finalHands[index] = tmpFlushCards[tmpCounter];
    tmpCounter++;
    }
    //Check straight flush
    if(checkStraight(tmpFlushCards)){
    log.log("[Dealer] Player %d has Straight Flush!",i);
    hasStraightFlush = true;
    int tmpCounter = 0;
    //Code to add final hand array to globalHandArray if it is a flush
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++){
    finalHands[index] = tmpFlushCards[tmpCounter];
    tmpCounter++;
    }	
    }
    //Check royal flush
    //If straight flush is true
    if(hasStraightFlush){
    //Call nut straight operation to check if SF is of the highest order
    if(checkIfNutStraight(tmpFlushCards))
    {
    hasRoyalFlush = true;
    log.log("[Dealer] Woah! Player %d has ROYAL Flush!!", i);

    //Counter for tmpFlushc
    int tmpCounter = 0;
    //Code to add final hand array to globalHandArray if it is a flush
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++)
    {
    finalHands[index] = tmpFlushCards[tmpCounter];
    tmpCounter++;
    }
    }
    }
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__pair_dubs_trips_quads_fh_( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play transition Play::Looping,Play::subvertex5,tick:tickIn */
    //Temp array
    int tempArr1[7];
    //Initialize best of seven card array
    seven[0] = hands[temp];  
    seven[1] = hands[temp+1];
    seven[2] = flop[0];
    seven[3] = flop[1];
    seven[4] = flop[2];
    seven[5] = flop[3];
    seven[6] = flop[4];
    //Same card hit counter
    int scHit = 0;
    //Pointer array
    int* finalHandForPair = new int[7];
    //Make copy of seven array after applying mod of 13 to convert to 1-13 
    for(int z = 0; z<=6; z++)
    {
    tempArr1[z] = ((seven[z] % 13) == 0) ? 13 : (seven[z] % 13);
    finalHandForPair[z] = 100;
    }
    //Check hands logic for pair, dubs, trips, quads and FH
    for(int x=0;x<players;x++)
    {
    //If already 100 then ignore
    if(tempArr1[x] == 100)
    {
    continue;
    }

    for(int y=x+1; y<7; y++)
    {
    if(tempArr1[x] == tempArr1[y])
    {
    //Check hits
    scHit++;
    tempArr1[y] = 100;
    }	
    }

    if(scHit == 1)
    {	
    //Hit a pair after trips then full house
    if(hasTrips == true)
    {	
    hasFull = true;
    hasTrips = false;
    hasPair = false;
    }
    //Hit a pair after another pair then dubs
    else if (hasPair == true){ 

    hasDubs = true; 
    hasPair = false;
    }
    //No hand before, hence pair
    else{	
    hasPair = true;	
    }	
    }
    if(scHit == 2)
    {	
    //Full house case
    if(hasPair == true){ 

    hasFull = true; 
    hasTrips = false;
    hasPair = false;
    }
    //Trips case
    else{	

    hasTrips = true;
    hasPair = false;	
    }	

    }
    //Another same card hit after trips then Quads
    if(scHit == 3)
    {	
    hasQuads = true;
    hasFull = false;
    hasTrips = false;
    hasPair = false;
    }
    if(scHit > 0)
    tempArr1[x] = 100;	
    scHit = 0;	

    }
    //Print hand
    if(hasPair){
    log.log("[Dealer] Player %d has pair", i);
    }
    else if(hasDubs){
    log.log("[Dealer] Player %d has double pair", i);
    }
    else if(hasTrips)
    {
    log.log("[Dealer] Player %d has trips", i);
    }
    else if(hasQuads)
    {
    log.log("[Dealer] Player %d has four of a kind", i);
    }
    else if(hasFull) 
    {
    log.log("[Dealer] Player %d has full house", i);
    }	
    //Code to set all the scHit cards replaced as 100 to be referenced from seven and stored in finalHand array
    for(int index =0 ; index < 7 ; index++){
    if(tempArr1[index] == 100)
    finalHandForPair[index] = ((seven[index] % 13) == 0) ? 13 : (seven[index] % 13);
    }
    //Sorting the array
    sort(finalHandForPair);
    //Initializing counter for finalHandForPair array
    int counter = 0;
    //Code to add final hand array to globalHandArray
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++){
    finalHands[index] = finalHandForPair[counter];
    counter++;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Play__straight_( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play transition Play::Check Straight,Play::Check Flush,tick:tickIn */
    //Create another array
    pTempArr = new int[7];
    //Store in temparray
    for(int z = 0; z<=6; z++)
    {
    tempArr[z] = seven[z];
    }
    //Convert to 1 - 13
    for(int j=0; j<=6; j++)
    {	
    tempArr[j] = ((tempArr[j] % 13) == 0) ? 13 : (tempArr[j] % 13);
    }
    //Sort tempArray
    pTempArr = sort(tempArr);
    //Get unique cards
    pTempArr = getUnique(pTempArr);
    //Sort tempArray to sort after getting unique elements
    pTempArr = sort(pTempArr);
    //Set counter for 'ptempArr'
    int counter = 0 ;
    //Call straight check function
    if(checkStraight(pTempArr)){

    log.log("[Dealer] Player %d has a Straight",i);
    hasStraight = true;

    //Code to add final hand array to globalHandArray if it is a straight
    for(int index = (i-1)*7 ; index < ((i-1)*7) + 7 ; index++){
    finalHands[index] = pTempArr[counter];
    counter++;
    }

    }
    //Self message
    tickOut.tick().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Rounds_Left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer transition subvertex4,Deal Cards::connectionPoint0 */
    log.log("[Dealer] ********************");
    log.log("[Dealer] Next round starting..");
    log.log("[Dealer] ********************");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____Rounds_played( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer transition subvertex4,Finish */
    log.log("[Dealer] #######################");
    log.log("[Dealer] Game Over!");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rounds ( *(const char * *)msg->getParam( 0 ) )
    #define twoDigitRounds ( *(bool *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer transition Start,Deck Gen::connectionPoint0,inp:input */
    //take user input
    int r1 = toDigit(rounds[0]);
    int r2 = 0;
    r = 0;
    //handle two digit
    if(twoDigitRounds == true){
    r2 = toDigit(rounds[1]);
    r1 = r1*10;
    }
    roundC = r1 + r2;
    log.log("[Dealer] Total Rounds: %d", roundC);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef twoDigitRounds
    #undef rounds
}

void Capsule_Dealer::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer transition Deal Cards::connectionPoint1,Open Flop::connectionPoint0 */
    //Increment rounds
    r++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__No_Tie( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner guard Check Winner::subvertex5,Check Winner::Declare Winner */
    //To check if more than one player has not incremented high count to decide winner
    return (highCount == 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner guard Check Winner::subvertex5,Check Winner::Tie::connectionPoint0 */
    //To check if more than one player has incremented high count, if true then TIE
    return (highCount > 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex6,Check Winner::Tie::Tie on Straight */
    return (highestRank == 5);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition11( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex6,Check Winner::Tie::subvertex5 */
    return (!(highestRank == 5));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition12( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex5,Check Winner::Tie::subvertex4 */
    return (!(highestRank == 6));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition13( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex4,Check Winner::Tie::subvertex9 */
    return (!(highestRank == 7));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition14( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex5,Check Winner::Tie::Tie on Flush */
    return (highestRank == 6);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition15( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex4,Check Winner::Tie::Tie on Full */
    return (highestRank == 7);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition16( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex9,Check Winner::Tie::subvertex10 */
    return (!(highestRank == 8));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition17( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex10,Check Winner::Tie::connectionPoint1 */
    return (!(highestRank == 9));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition18( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex9,Check Winner::Tie::Tie on Quads */
    return (highestRank == 8);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition19( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex10,Check Winner::Tie::Tie on St. Flush */
    return (highestRank == 9);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex1,Check Winner::Tie::subvertex3 */
    return (!(highestRank == 1));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex1,Check Winner::Tie::Tie on HighCard */
    return (highestRank == 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex3,Check Winner::Tie::subvertex8 */
    return (!(highestRank == 2));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex8,Check Winner::Tie::subvertex7 */
    return (!(highestRank == 3));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex3,Check Winner::Tie::Tie on Pair */
    return (highestRank == 2);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex8,Check Winner::Tie::Tie on Dubs */
    return (highestRank == 3);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex7,Check Winner::Tie::Tie on Trips */
    return (highestRank == 4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Check_Winner__Tie__transition9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Check Winner::Tie guard Check Winner::Tie::subvertex7,Check Winner::Tie::subvertex6 */
    return (!(highestRank == 4));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Deal_Cards__transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards guard Deal Cards::subvertex3,Deal Cards::connectionPoint1 */
    return (temp > players);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Deal_Cards__transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deal Cards guard Deal Cards::subvertex3,Deal Cards::Dealing */
    return (temp <= players);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen guard Deck Gen::subvertex0,Deck Gen::connectionPoint1 */
    return (i > 52);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Deck Gen guard Deck Gen::subvertex0,Deck Gen::Add to Deck */
    return (i <= 52);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Open_Flop__Flop_done( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop guard Open Flop::subvertex1,Open Flop::connectionPoint1 */
    return (counter == 6);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Open Flop guard Open Flop::subvertex1,Open Flop::Looping */
    return (!(counter == 6));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__AllPlayersAreDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play guard Play::subvertex2,Play::connectionPoint1 */
    return (i == players);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex4,Play::Hand Rank::subvertex1 */
    return hasQuads;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____4_of_a_kind( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex4,Play::Hand Rank::subvertex5 */
    return (!(hasQuads));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____dubs( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex9,Play::Hand Rank::subvertex10 */
    return (!(hasDubs));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex6,Play::Hand Rank::subvertex8 */
    return (!(hasFlush));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____full_house( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex5,Play::Hand Rank::subvertex6 */
    return (!(hasFull));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____royal_flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex2,Play::Hand Rank::subvertex3 */
    return (!(hasRoyalFlush));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____st__flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex3,Play::Hand Rank::subvertex4 */
    return (!(hasStraightFlush));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____straight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex8,Play::Hand Rank::subvertex7 */
    return (!(hasStraight));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank____trips( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex7,Play::Hand Rank::subvertex9 */
    return (!(hasTrips));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__dubs( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex9,Play::Hand Rank::subvertex1 */
    return hasDubs;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex6,Play::Hand Rank::subvertex1 */
    return hasFlush;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__full_house( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex5,Play::Hand Rank::subvertex1 */
    return hasFull;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex10,Play::Hand Rank::connectionPoint1 */
    return (!(hasPair));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__pair( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex10,Play::Hand Rank::subvertex1 */
    return hasPair;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex2,Play::Hand Rank::subvertex1 */
    return hasRoyalFlush;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex3,Play::Hand Rank::subvertex1 */
    return hasStraightFlush;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__straight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex8,Play::Hand Rank::subvertex1 */
    return hasStraight;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__Hand_Rank__trips( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play::Hand Rank guard Play::Hand Rank::subvertex7,Play::Hand Rank::subvertex1 */
    return hasTrips;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play____AllPlayersAreDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play guard Play::subvertex2,Play::Looping */
    return (!(i == players));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play guard Play::subvertex5,Play::Check Straight */
    return (!(hasQuads || hasFull));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Play__hasFull_or_hasQuads( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer::Play guard Play::subvertex5,Play::Hand Rank::connectionPoint0 */
    return (hasQuads || hasFull);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Rounds_Left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer guard subvertex4,Deal Cards::connectionPoint0 */
    return (!(r == roundC));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Dealer::guard_____Rounds_played( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Poker/Poker.uml Poker::Dealer guard subvertex4,Finish */
    return (r == roundC);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Dealer::actionchain_____Check_Winner__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Initial( msg );
    update_state( Check_Winner__Initial );
}

void Capsule_Dealer::actionchain_____Check_Winner__Next_round( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Next_round( msg );
}

void Capsule_Dealer::actionchain_____Check_Winner__No_Tie( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__No_Tie( msg );
    update_state( Check_Winner__Declare_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie_( const UMLRTMessage * msg )
{
    update_state( Check_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__Evaluate( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__Evaluate( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Initial );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__Initial( msg );
    update_state( Check_Winner__Tie__Initial );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalDubs( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalDubs( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Dubs );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalFlush( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalFlush( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalFull( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalFull( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Full );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalHC( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalHC( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_HighCard );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalPair( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalPair( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Pair );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalQuads( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalQuads( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Quads );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalSt_( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalSt_( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Straight );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalSt_Flush( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalSt_Flush( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_St__Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__evalTrips( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie );
    transitionaction_____Check_Winner__Tie__evalTrips( msg );
    save_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Trips );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_30( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Initial );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_31( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_HighCard );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_32( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Pair );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_33( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Trips );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_34( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_35( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Straight );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_36( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Dubs );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_37( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Full );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_38( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_Quads );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_39( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__Tie_on_St__Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_40_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__boundary );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__new_transition_41_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Tie__boundary );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition10( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition10( msg );
    update_state( Check_Winner__Tie__Tie_on_Straight );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition14( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition14( msg );
    update_state( Check_Winner__Tie__Tie_on_Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition15( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition15( msg );
    update_state( Check_Winner__Tie__Tie_on_Full );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition18( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition18( msg );
    update_state( Check_Winner__Tie__Tie_on_Quads );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition19( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition19( msg );
    update_state( Check_Winner__Tie__Tie_on_St__Flush );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition3( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition3( msg );
    update_state( Check_Winner__Tie__Tie_on_HighCard );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition6( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition6( msg );
    update_state( Check_Winner__Tie__Tie_on_Pair );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition7( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition7( msg );
    update_state( Check_Winner__Tie__Tie_on_Dubs );
}

void Capsule_Dealer::actionchain_____Check_Winner__Tie__transition8( const UMLRTMessage * msg )
{
    transitionaction_____Check_Winner__Tie__transition8( msg );
    update_state( Check_Winner__Tie__Tie_on_Trips );
}

void Capsule_Dealer::actionchain_____Check_Winner__decide_Winner( const UMLRTMessage * msg )
{
    update_state( Check_Winner );
    transitionaction_____Check_Winner__decide_Winner( msg );
    update_state( Check_Winner__Check_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__declare( const UMLRTMessage * msg )
{
    update_state( Check_Winner );
    transitionaction_____Check_Winner__declare( msg );
    save_history( Check_Winner, Check_Winner__Declare_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__new_transition_24( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Initial );
}

void Capsule_Dealer::actionchain_____Check_Winner__new_transition_25( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Check_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__new_transition_26( const UMLRTMessage * msg )
{
    update_state( Check_Winner__Declare_Winner );
}

void Capsule_Dealer::actionchain_____Check_Winner__new_transition_28_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Check_Winner__boundary );
}

void Capsule_Dealer::actionchain_____Check_Winner__new_transition_29_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Check_Winner__boundary );
}

void Capsule_Dealer::actionchain_____Check_Winner__transition5( const UMLRTMessage * msg )
{
    update_state( Check_Winner );
    save_history( Check_Winner, Check_Winner__Tie );
}

void Capsule_Dealer::actionchain_____Deal_Cards__deal1( const UMLRTMessage * msg )
{
    update_state( Deal_Cards );
    transitionaction_____Deal_Cards__deal1( msg );
    update_state( Deal_Cards__Deal_Card_1 );
}

void Capsule_Dealer::actionchain_____Deal_Cards__deal2( const UMLRTMessage * msg )
{
    update_state( Deal_Cards );
    transitionaction_____Deal_Cards__deal2( msg );
    update_state( Deal_Cards__Deal_Card_2 );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_1( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__Deal_Card_1 );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_2( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__Looping );
    entryaction_____Deal_Cards__Looping( msg );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_3( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__Dealing );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_4( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__Continue );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_5( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__Deal_Card_2 );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_6_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__boundary );
}

void Capsule_Dealer::actionchain_____Deal_Cards__new_transition_7_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Deal_Cards__boundary );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition0( const UMLRTMessage * msg )
{
    transitionaction_____Deal_Cards__transition0( msg );
    update_state( Deal_Cards__Looping );
    entryaction_____Deal_Cards__Looping( msg );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition2( const UMLRTMessage * msg )
{
    update_state( Deal_Cards );
    transitionaction_____Deal_Cards__transition2( msg );
    update_state( Deal_Cards__Continue );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition3( const UMLRTMessage * msg )
{
    transitionaction_____Deal_Cards__transition3( msg );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition4( const UMLRTMessage * msg )
{
    transitionaction_____Deal_Cards__transition4( msg );
    update_state( Deal_Cards__Dealing );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition5( const UMLRTMessage * msg )
{
    update_state( Deal_Cards );
    save_history( Deal_Cards, Deal_Cards__Looping );
}

void Capsule_Dealer::actionchain_____Deal_Cards__transition7( const UMLRTMessage * msg )
{
    update_state( Deal_Cards );
    transitionaction_____Deal_Cards__transition7( msg );
    update_state( Deal_Cards__Looping );
    entryaction_____Deal_Cards__Looping( msg );
}

void Capsule_Dealer::actionchain_____Deck_Gen__52_Cards_Generated( const UMLRTMessage * msg )
{
    transitionaction_____Deck_Gen__52_Cards_Generated( msg );
}

void Capsule_Dealer::actionchain_____Deck_Gen__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Deck_Gen__Initial( msg );
    update_state( Deck_Gen__Initial );
    entryaction_____Deck_Gen__Initial( msg );
}

void Capsule_Dealer::actionchain_____Deck_Gen__Next_Card( const UMLRTMessage * msg )
{
    update_state( Deck_Gen );
    transitionaction_____Deck_Gen__Next_Card( msg );
    update_state( Deck_Gen__Initial );
    entryaction_____Deck_Gen__Initial( msg );
}

void Capsule_Dealer::actionchain_____Deck_Gen__Not_All_Cards_Generated( const UMLRTMessage * msg )
{
    transitionaction_____Deck_Gen__Not_All_Cards_Generated( msg );
    update_state( Deck_Gen__Add_to_Deck );
}

void Capsule_Dealer::actionchain_____Deck_Gen__Starting( const UMLRTMessage * msg )
{
    update_state( Deck_Gen );
    save_history( Deck_Gen, Deck_Gen__Initial );
}

void Capsule_Dealer::actionchain_____Deck_Gen__new_transition_10_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Deck_Gen__boundary );
}

void Capsule_Dealer::actionchain_____Deck_Gen__new_transition_11_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Deck_Gen__boundary );
}

void Capsule_Dealer::actionchain_____Deck_Gen__new_transition_8( const UMLRTMessage * msg )
{
    update_state( Deck_Gen__Initial );
    entryaction_____Deck_Gen__Initial( msg );
}

void Capsule_Dealer::actionchain_____Deck_Gen__new_transition_9( const UMLRTMessage * msg )
{
    update_state( Deck_Gen__Add_to_Deck );
}

void Capsule_Dealer::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( Start );
}

void Capsule_Dealer::actionchain_____Open_Flop__Flop_done( const UMLRTMessage * msg )
{
    transitionaction_____Open_Flop__Flop_done( msg );
}

void Capsule_Dealer::actionchain_____Open_Flop__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Open_Flop__Initial( msg );
    update_state( Open_Flop__Looping );
    entryaction_____Open_Flop__Looping( msg );
}

void Capsule_Dealer::actionchain_____Open_Flop__continue_opening_flop( const UMLRTMessage * msg )
{
    transitionaction_____Open_Flop__continue_opening_flop( msg );
    update_state( Open_Flop__Looping );
    entryaction_____Open_Flop__Looping( msg );
}

void Capsule_Dealer::actionchain_____Open_Flop__new_transition_12( const UMLRTMessage * msg )
{
    update_state( Open_Flop__Looping );
    entryaction_____Open_Flop__Looping( msg );
}

void Capsule_Dealer::actionchain_____Open_Flop__new_transition_13_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Open_Flop__boundary );
}

void Capsule_Dealer::actionchain_____Open_Flop__new_transition_14_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Open_Flop__boundary );
}

void Capsule_Dealer::actionchain_____Open_Flop__opening( const UMLRTMessage * msg )
{
    update_state( Open_Flop );
    save_history( Open_Flop, Open_Flop__Looping );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__4_of_a_kind( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__4_of_a_kind( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__Initial( msg );
    update_state( Play__Hand_Rank__Initial );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__checkRank( const UMLRTMessage * msg )
{
    update_state( Play__Hand_Rank );
    save_history( Play__Hand_Rank, Play__Hand_Rank__Initial );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__dubs( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__dubs( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__flush( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__flush( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__full_house( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__full_house( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__high_Card( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__high_Card( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__new_transition_21( const UMLRTMessage * msg )
{
    update_state( Play__Hand_Rank__Initial );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__new_transition_22_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Play__Hand_Rank__boundary );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__new_transition_23_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Play__Hand_Rank__boundary );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__pair( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__pair( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__royal_flush( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__royal_flush( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__st__flush( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__st__flush( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__straight( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__straight( msg );
}

void Capsule_Dealer::actionchain_____Play__Hand_Rank__trips( const UMLRTMessage * msg )
{
    transitionaction_____Play__Hand_Rank__trips( msg );
}

void Capsule_Dealer::actionchain_____Play__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Play__Initial( msg );
    update_state( Play__Looping );
    entryaction_____Play__Looping( msg );
}

void Capsule_Dealer::actionchain_____Play____AllPlayersAreDone( const UMLRTMessage * msg )
{
    update_state( Play__Looping );
    entryaction_____Play__Looping( msg );
}

void Capsule_Dealer::actionchain_____Play____hasFull_or_hasQuads( const UMLRTMessage * msg )
{
    transitionaction_____Play____hasFull_or_hasQuads( msg );
    update_state( Play__Check_Straight );
}

void Capsule_Dealer::actionchain_____Play__continue( const UMLRTMessage * msg )
{
    update_state( Play );
    save_history( Play, Play__Hand_Rank );
}

void Capsule_Dealer::actionchain_____Play__flush_st_flush_royal_flush_( const UMLRTMessage * msg )
{
    update_state( Play );
    transitionaction_____Play__flush_st_flush_royal_flush_( msg );
    update_state( Play__Hand_Rank );
}

void Capsule_Dealer::actionchain_____Play__hasFull_or_hasQuads( const UMLRTMessage * msg )
{
    update_state( Play__Hand_Rank );
}

void Capsule_Dealer::actionchain_____Play__new_transition_15( const UMLRTMessage * msg )
{
    update_state( Play__Looping );
    entryaction_____Play__Looping( msg );
}

void Capsule_Dealer::actionchain_____Play__new_transition_16( const UMLRTMessage * msg )
{
    update_state( Play__Check_Straight );
}

void Capsule_Dealer::actionchain_____Play__new_transition_18( const UMLRTMessage * msg )
{
    update_state( Play__Check_Flush );
}

void Capsule_Dealer::actionchain_____Play__new_transition_19_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Play__boundary );
}

void Capsule_Dealer::actionchain_____Play__new_transition_20_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Play__boundary );
}

void Capsule_Dealer::actionchain_____Play__pair_dubs_trips_quads_fh_( const UMLRTMessage * msg )
{
    update_state( Play );
    transitionaction_____Play__pair_dubs_trips_quads_fh_( msg );
}

void Capsule_Dealer::actionchain_____Play__straight_( const UMLRTMessage * msg )
{
    update_state( Play );
    transitionaction_____Play__straight_( msg );
    update_state( Play__Check_Flush );
}

void Capsule_Dealer::actionchain_____Rounds_Left( const UMLRTMessage * msg )
{
    transitionaction_____Rounds_Left( msg );
    update_state( Deal_Cards );
}

void Capsule_Dealer::actionchain_____Rounds_played( const UMLRTMessage * msg )
{
    transitionaction_____Rounds_played( msg );
    update_state( Finish );
}

void Capsule_Dealer::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( Deck_Gen );
}

void Capsule_Dealer::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( Open_Flop );
}

void Capsule_Dealer::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Play );
}

void Capsule_Dealer::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Deal_Cards );
}

void Capsule_Dealer::actionchain_____transition7( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Check_Winner );
}

void Capsule_Dealer::actionchain_____transition8( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__Tie__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Check_Winner__Tie__Initial( msg );
    return Check_Winner__Tie__Initial;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__Tie__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____Check_Winner__transition5( msg );
    return junction_____Check_Winner__subvertex4( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__Tie__subvertex19( const UMLRTMessage * msg )
{
    return junction_____Check_Winner__Tie__connectionPoint1( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Check_Winner__Initial( msg );
    return Check_Winner__Initial;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition8( msg );
    return choice_____subvertex4( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Check_Winner__subvertex4( const UMLRTMessage * msg )
{
    actionchain_____Check_Winner__Next_round( msg );
    return junction_____Check_Winner__connectionPoint1( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Deal_Cards__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Deal_Cards__transition0( msg );
    return Deal_Cards__Looping;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Deal_Cards__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition2( msg );
    return junction_____Open_Flop__connectionPoint0( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Deck_Gen__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Deck_Gen__Initial( msg );
    return Deck_Gen__Initial;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Deck_Gen__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition6( msg );
    return junction_____Deal_Cards__connectionPoint0( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Open_Flop__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Open_Flop__Initial( msg );
    return Open_Flop__Looping;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Open_Flop__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition3( msg );
    return junction_____Play__connectionPoint0( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Play__Hand_Rank__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Play__Hand_Rank__Initial( msg );
    return Play__Hand_Rank__Initial;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Play__Hand_Rank__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____Play__continue( msg );
    return choice_____Play__subvertex2( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Play__Hand_Rank__subvertex1( const UMLRTMessage * msg )
{
    return junction_____Play__Hand_Rank__connectionPoint1( msg );
}

Capsule_Dealer::State Capsule_Dealer::junction_____Play__connectionPoint0( const UMLRTMessage * msg )
{
    actionchain_____Play__Initial( msg );
    return Play__Looping;
}

Capsule_Dealer::State Capsule_Dealer::junction_____Play__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition7( msg );
    return junction_____Check_Winner__connectionPoint0( msg );
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Check_Winner__Tie, Check_Winner__Tie__Initial ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_30( msg );
        return Check_Winner__Tie__Initial;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_HighCard ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_31( msg );
        return Check_Winner__Tie__Tie_on_HighCard;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Pair ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_32( msg );
        return Check_Winner__Tie__Tie_on_Pair;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Trips ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_33( msg );
        return Check_Winner__Tie__Tie_on_Trips;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Flush ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_34( msg );
        return Check_Winner__Tie__Tie_on_Flush;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Straight ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_35( msg );
        return Check_Winner__Tie__Tie_on_Straight;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Dubs ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_36( msg );
        return Check_Winner__Tie__Tie_on_Dubs;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Full ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_37( msg );
        return Check_Winner__Tie__Tie_on_Full;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_Quads ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_38( msg );
        return Check_Winner__Tie__Tie_on_Quads;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__Tie_on_St__Flush ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_39( msg );
        return Check_Winner__Tie__Tie_on_St__Flush;
    }
    else if( check_history( Check_Winner__Tie, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_40_to_unvisited_boundary( msg );
        return Check_Winner__Tie__boundary;
    }
    else if( check_history( Check_Winner__Tie, Check_Winner__Tie__boundary ) )
    {
        actionchain_____Check_Winner__Tie__new_transition_41_to_visited_boundary( msg );
        return Check_Winner__Tie__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex1( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition2( msg ) )
        return choice_____Check_Winner__Tie__subvertex3( msg );
    else if( guard_____Check_Winner__Tie__transition3( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition3( msg );
        return Check_Winner__Tie__Tie_on_HighCard;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex10( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition17( msg ) )
        return junction_____Check_Winner__Tie__connectionPoint1( msg );
    else if( guard_____Check_Winner__Tie__transition19( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition19( msg );
        return Check_Winner__Tie__Tie_on_St__Flush;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex3( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition4( msg ) )
        return choice_____Check_Winner__Tie__subvertex8( msg );
    else if( guard_____Check_Winner__Tie__transition6( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition6( msg );
        return Check_Winner__Tie__Tie_on_Pair;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex4( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition13( msg ) )
        return choice_____Check_Winner__Tie__subvertex9( msg );
    else if( guard_____Check_Winner__Tie__transition15( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition15( msg );
        return Check_Winner__Tie__Tie_on_Full;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex5( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition12( msg ) )
        return choice_____Check_Winner__Tie__subvertex4( msg );
    else if( guard_____Check_Winner__Tie__transition14( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition14( msg );
        return Check_Winner__Tie__Tie_on_Flush;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex6( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition10( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition10( msg );
        return Check_Winner__Tie__Tie_on_Straight;
    }
    else if( guard_____Check_Winner__Tie__transition11( msg ) )
        return choice_____Check_Winner__Tie__subvertex5( msg );
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex7( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition8( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition8( msg );
        return Check_Winner__Tie__Tie_on_Trips;
    }
    else if( guard_____Check_Winner__Tie__transition9( msg ) )
        return choice_____Check_Winner__Tie__subvertex6( msg );
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex8( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition5( msg ) )
        return choice_____Check_Winner__Tie__subvertex7( msg );
    else if( guard_____Check_Winner__Tie__transition7( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition7( msg );
        return Check_Winner__Tie__Tie_on_Dubs;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__Tie__subvertex9( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__Tie__transition16( msg ) )
        return choice_____Check_Winner__Tie__subvertex10( msg );
    else if( guard_____Check_Winner__Tie__transition18( msg ) )
    {
        actionchain_____Check_Winner__Tie__transition18( msg );
        return Check_Winner__Tie__Tie_on_Quads;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Check_Winner, Check_Winner__Initial ) )
    {
        actionchain_____Check_Winner__new_transition_24( msg );
        return Check_Winner__Initial;
    }
    else if( check_history( Check_Winner, Check_Winner__Check_Winner ) )
    {
        actionchain_____Check_Winner__new_transition_25( msg );
        return Check_Winner__Check_Winner;
    }
    else if( check_history( Check_Winner, Check_Winner__Declare_Winner ) )
    {
        actionchain_____Check_Winner__new_transition_26( msg );
        return Check_Winner__Declare_Winner;
    }
    else if( check_history( Check_Winner, Check_Winner__Tie ) )
        return choice_____Check_Winner__Tie__deephistory( msg );
    else if( check_history( Check_Winner, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Check_Winner__new_transition_28_to_unvisited_boundary( msg );
        return Check_Winner__boundary;
    }
    else if( check_history( Check_Winner, Check_Winner__boundary ) )
    {
        actionchain_____Check_Winner__new_transition_29_to_visited_boundary( msg );
        return Check_Winner__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Check_Winner__subvertex5( const UMLRTMessage * msg )
{
    if( guard_____Check_Winner__No_Tie( msg ) )
    {
        actionchain_____Check_Winner__No_Tie( msg );
        return Check_Winner__Declare_Winner;
    }
    else if( guard_____Check_Winner__Tie( msg ) )
    {
        actionchain_____Check_Winner__Tie( msg );
        return junction_____Check_Winner__Tie__connectionPoint0( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Deal_Cards__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Deal_Cards, Deal_Cards__Deal_Card_1 ) )
    {
        actionchain_____Deal_Cards__new_transition_1( msg );
        return Deal_Cards__Deal_Card_1;
    }
    else if( check_history( Deal_Cards, Deal_Cards__Looping ) )
    {
        actionchain_____Deal_Cards__new_transition_2( msg );
        return Deal_Cards__Looping;
    }
    else if( check_history( Deal_Cards, Deal_Cards__Dealing ) )
    {
        actionchain_____Deal_Cards__new_transition_3( msg );
        return Deal_Cards__Dealing;
    }
    else if( check_history( Deal_Cards, Deal_Cards__Continue ) )
    {
        actionchain_____Deal_Cards__new_transition_4( msg );
        return Deal_Cards__Continue;
    }
    else if( check_history( Deal_Cards, Deal_Cards__Deal_Card_2 ) )
    {
        actionchain_____Deal_Cards__new_transition_5( msg );
        return Deal_Cards__Deal_Card_2;
    }
    else if( check_history( Deal_Cards, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Deal_Cards__new_transition_6_to_unvisited_boundary( msg );
        return Deal_Cards__boundary;
    }
    else if( check_history( Deal_Cards, Deal_Cards__boundary ) )
    {
        actionchain_____Deal_Cards__new_transition_7_to_visited_boundary( msg );
        return Deal_Cards__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Deal_Cards__subvertex3( const UMLRTMessage * msg )
{
    if( guard_____Deal_Cards__transition3( msg ) )
    {
        actionchain_____Deal_Cards__transition3( msg );
        return junction_____Deal_Cards__connectionPoint1( msg );
    }
    else if( guard_____Deal_Cards__transition4( msg ) )
    {
        actionchain_____Deal_Cards__transition4( msg );
        return Deal_Cards__Dealing;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Deck_Gen__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Deck_Gen, Deck_Gen__Initial ) )
    {
        actionchain_____Deck_Gen__new_transition_8( msg );
        return Deck_Gen__Initial;
    }
    else if( check_history( Deck_Gen, Deck_Gen__Add_to_Deck ) )
    {
        actionchain_____Deck_Gen__new_transition_9( msg );
        return Deck_Gen__Add_to_Deck;
    }
    else if( check_history( Deck_Gen, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Deck_Gen__new_transition_10_to_unvisited_boundary( msg );
        return Deck_Gen__boundary;
    }
    else if( check_history( Deck_Gen, Deck_Gen__boundary ) )
    {
        actionchain_____Deck_Gen__new_transition_11_to_visited_boundary( msg );
        return Deck_Gen__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Deck_Gen__subvertex0( const UMLRTMessage * msg )
{
    if( guard_____Deck_Gen__Not_All_Cards_Generated( msg ) )
    {
        actionchain_____Deck_Gen__Not_All_Cards_Generated( msg );
        return Deck_Gen__Add_to_Deck;
    }
    else if( guard_____Deck_Gen__52_Cards_Generated( msg ) )
    {
        actionchain_____Deck_Gen__52_Cards_Generated( msg );
        return junction_____Deck_Gen__connectionPoint1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Open_Flop__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Open_Flop, Open_Flop__Looping ) )
    {
        actionchain_____Open_Flop__new_transition_12( msg );
        return Open_Flop__Looping;
    }
    else if( check_history( Open_Flop, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Open_Flop__new_transition_13_to_unvisited_boundary( msg );
        return Open_Flop__boundary;
    }
    else if( check_history( Open_Flop, Open_Flop__boundary ) )
    {
        actionchain_____Open_Flop__new_transition_14_to_visited_boundary( msg );
        return Open_Flop__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Open_Flop__subvertex1( const UMLRTMessage * msg )
{
    if( guard_____Open_Flop__Flop_done( msg ) )
    {
        actionchain_____Open_Flop__Flop_done( msg );
        return junction_____Open_Flop__connectionPoint1( msg );
    }
    else if( guard_____Open_Flop__continue_opening_flop( msg ) )
    {
        actionchain_____Open_Flop__continue_opening_flop( msg );
        return Open_Flop__Looping;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Play__Hand_Rank, Play__Hand_Rank__Initial ) )
    {
        actionchain_____Play__Hand_Rank__new_transition_21( msg );
        return Play__Hand_Rank__Initial;
    }
    else if( check_history( Play__Hand_Rank, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Play__Hand_Rank__new_transition_22_to_unvisited_boundary( msg );
        return Play__Hand_Rank__boundary;
    }
    else if( check_history( Play__Hand_Rank, Play__Hand_Rank__boundary ) )
    {
        actionchain_____Play__Hand_Rank__new_transition_23_to_visited_boundary( msg );
        return Play__Hand_Rank__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex10( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank__pair( msg ) )
    {
        actionchain_____Play__Hand_Rank__pair( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    else if( guard_____Play__Hand_Rank__high_Card( msg ) )
    {
        actionchain_____Play__Hand_Rank__high_Card( msg );
        return junction_____Play__Hand_Rank__connectionPoint1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex2( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank__royal_flush( msg ) )
    {
        actionchain_____Play__Hand_Rank__royal_flush( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    else if( guard_____Play__Hand_Rank____royal_flush( msg ) )
        return choice_____Play__Hand_Rank__subvertex3( msg );
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex3( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank__st__flush( msg ) )
    {
        actionchain_____Play__Hand_Rank__st__flush( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    else if( guard_____Play__Hand_Rank____st__flush( msg ) )
        return choice_____Play__Hand_Rank__subvertex4( msg );
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex4( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank____4_of_a_kind( msg ) )
        return choice_____Play__Hand_Rank__subvertex5( msg );
    else if( guard_____Play__Hand_Rank__4_of_a_kind( msg ) )
    {
        actionchain_____Play__Hand_Rank__4_of_a_kind( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex5( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank____full_house( msg ) )
        return choice_____Play__Hand_Rank__subvertex6( msg );
    else if( guard_____Play__Hand_Rank__full_house( msg ) )
    {
        actionchain_____Play__Hand_Rank__full_house( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex6( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank____flush( msg ) )
        return choice_____Play__Hand_Rank__subvertex8( msg );
    else if( guard_____Play__Hand_Rank__flush( msg ) )
    {
        actionchain_____Play__Hand_Rank__flush( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex7( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank____trips( msg ) )
        return choice_____Play__Hand_Rank__subvertex9( msg );
    else if( guard_____Play__Hand_Rank__trips( msg ) )
    {
        actionchain_____Play__Hand_Rank__trips( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex8( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank____straight( msg ) )
        return choice_____Play__Hand_Rank__subvertex7( msg );
    else if( guard_____Play__Hand_Rank__straight( msg ) )
    {
        actionchain_____Play__Hand_Rank__straight( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__Hand_Rank__subvertex9( const UMLRTMessage * msg )
{
    if( guard_____Play__Hand_Rank__dubs( msg ) )
    {
        actionchain_____Play__Hand_Rank__dubs( msg );
        return junction_____Play__Hand_Rank__subvertex1( msg );
    }
    else if( guard_____Play__Hand_Rank____dubs( msg ) )
        return choice_____Play__Hand_Rank__subvertex10( msg );
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Play, Play__Looping ) )
    {
        actionchain_____Play__new_transition_15( msg );
        return Play__Looping;
    }
    else if( check_history( Play, Play__Check_Straight ) )
    {
        actionchain_____Play__new_transition_16( msg );
        return Play__Check_Straight;
    }
    else if( check_history( Play, Play__Hand_Rank ) )
        return choice_____Play__Hand_Rank__deephistory( msg );
    else if( check_history( Play, Play__Check_Flush ) )
    {
        actionchain_____Play__new_transition_18( msg );
        return Play__Check_Flush;
    }
    else if( check_history( Play, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Play__new_transition_19_to_unvisited_boundary( msg );
        return Play__boundary;
    }
    else if( check_history( Play, Play__boundary ) )
    {
        actionchain_____Play__new_transition_20_to_visited_boundary( msg );
        return Play__boundary;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__subvertex2( const UMLRTMessage * msg )
{
    if( guard_____Play__AllPlayersAreDone( msg ) )
        return junction_____Play__connectionPoint1( msg );
    else if( guard_____Play____AllPlayersAreDone( msg ) )
    {
        actionchain_____Play____AllPlayersAreDone( msg );
        return Play__Looping;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____Play__subvertex5( const UMLRTMessage * msg )
{
    if( guard_____Play__hasFull_or_hasQuads( msg ) )
    {
        actionchain_____Play__hasFull_or_hasQuads( msg );
        return junction_____Play__Hand_Rank__connectionPoint0( msg );
    }
    else if( guard_____Play____hasFull_or_hasQuads( msg ) )
    {
        actionchain_____Play____hasFull_or_hasQuads( msg );
        return Play__Check_Straight;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::choice_____subvertex4( const UMLRTMessage * msg )
{
    if( guard_____Rounds_Left( msg ) )
    {
        actionchain_____Rounds_Left( msg );
        return junction_____Deal_Cards__connectionPoint0( msg );
    }
    else if( guard_____Rounds_played( msg ) )
    {
        actionchain_____Rounds_played( msg );
        return Finish;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Check_Winner( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie_( msg );
            return choice_____Check_Winner__subvertex5( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Declare_Winner( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__declare( msg );
            return junction_____Check_Winner__subvertex4( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__decide_Winner( msg );
            return Check_Winner__Check_Winner;
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__Evaluate( msg );
            return choice_____Check_Winner__Tie__subvertex1( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Dubs( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalDubs( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Flush( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalFlush( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Full( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalFull( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_HighCard( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalHC( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Pair( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalPair( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Quads( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalQuads( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_St__Flush( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalSt_Flush( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Straight( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalSt_( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__Tie_on_Trips( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Check_Winner__Tie__evalTrips( msg );
            return junction_____Check_Winner__Tie__subvertex19( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__Tie__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Check_Winner__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__Continue( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Deal_Cards__deal2( msg );
            return Deal_Cards__Deal_Card_2;
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

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__Deal_Card_1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_playPort:
        switch( msg->getSignalId() )
        {
        case Play::signal_ack:
            actionchain_____Deal_Cards__transition2( msg );
            return Deal_Cards__Continue;
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

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__Deal_Card_2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_playPort:
        switch( msg->getSignalId() )
        {
        case Play::signal_ack:
            actionchain_____Deal_Cards__transition7( msg );
            return Deal_Cards__Looping;
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

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__Dealing( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Deal_Cards__deal1( msg );
            return Deal_Cards__Deal_Card_1;
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

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__Looping( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Deal_Cards__transition5( msg );
            return choice_____Deal_Cards__subvertex3( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Deal_Cards__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Deck_Gen__Add_to_Deck( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Deck_Gen__Next_Card( msg );
            return Deck_Gen__Initial;
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

Capsule_Dealer::State Capsule_Dealer::state_____Deck_Gen__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Deck_Gen__Starting( msg );
            return choice_____Deck_Gen__subvertex0( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Deck_Gen__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Finish( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Open_Flop__Looping( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Open_Flop__opening( msg );
            return choice_____Open_Flop__subvertex1( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Open_Flop__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Play__Check_Flush( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Play__flush_st_flush_royal_flush_( msg );
            return junction_____Play__Hand_Rank__connectionPoint0( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Play__Check_Straight( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Play__straight_( msg );
            return Play__Check_Flush;
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

Capsule_Dealer::State Capsule_Dealer::state_____Play__Hand_Rank__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Play__Hand_Rank__checkRank( msg );
            return choice_____Play__Hand_Rank__subvertex2( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Play__Hand_Rank__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Play__Looping( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tickIn:
        switch( msg->getSignalId() )
        {
        case Tick::signal_tick:
            actionchain_____Play__pair_dubs_trips_quads_fh_( msg );
            return choice_____Play__subvertex5( msg );
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

Capsule_Dealer::State Capsule_Dealer::state_____Play__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Dealer::State Capsule_Dealer::state_____Start( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_input:
        switch( msg->getSignalId() )
        {
        case Input::signal_inp:
            actionchain_____transition1( msg );
            return junction_____Deck_Gen__connectionPoint0( msg );
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
        Capsule_Dealer::port_input,
        "Input",
        "input",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Dealer::port_playPort,
        "Play",
        "playPort",
        "",
        6,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Dealer::port_tickIn,
        "Tick",
        "tickIn",
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
        Capsule_Dealer::port_tickOut,
        "Tick",
        "tickOut",
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
        Capsule_Dealer::port_timing,
        "Timing",
        "timing",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Dealer::port_log,
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

static void instantiate_Dealer( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Dealer );
    UMLRTFrameService::connectPorts( borderPorts[Capsule_Dealer::borderport_tickIn], 0, borderPorts[Capsule_Dealer::borderport_tickOut], 0 );
    UMLRTFrameService::connectPorts( borderPorts[Capsule_Dealer::borderport_tickOut], 0, borderPorts[Capsule_Dealer::borderport_tickIn], 0 );
    slot->capsule = new Capsule_Dealer( &Dealer, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Dealer = 
{
    "Dealer",
    NULL,
    instantiate_Dealer,
    0,
    NULL,
    4,
    portroles_border,
    2,
    portroles_internal
};

