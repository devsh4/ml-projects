
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_d1,
    InstId_Top_p1,
    InstId_Top_p2,
    InstId_Top_p3,
    InstId_Top_p4,
    InstId_Top_p5,
    InstId_Top_p6
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort internalports_Top[];
extern UMLRTCommsPort borderports_Top_d1[];
extern UMLRTCommsPort internalports_Top_d1[];
extern UMLRTCommsPort borderports_Top_p1[];
extern UMLRTCommsPort internalports_Top_p1[];
extern UMLRTCommsPort borderports_Top_p2[];
extern UMLRTCommsPort internalports_Top_p2[];
extern UMLRTCommsPort borderports_Top_p3[];
extern UMLRTCommsPort internalports_Top_p3[];
extern UMLRTCommsPort borderports_Top_p4[];
extern UMLRTCommsPort internalports_Top_p4[];
extern UMLRTCommsPort borderports_Top_p5[];
extern UMLRTCommsPort internalports_Top_p5[];
extern UMLRTCommsPort borderports_Top_p6[];
extern UMLRTCommsPort internalports_Top_p6[];
extern UMLRTSlot Top_slots[];

#endif

