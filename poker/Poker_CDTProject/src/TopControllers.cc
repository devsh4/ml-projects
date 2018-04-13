
#include "TopControllers.hh"

#include "Dealer.hh"
#include "Player.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static UMLRTCommsPortFarEnd internalfarEndList_Top[] = 
{
    {
        0,
        &borderports_Top_d1[Capsule_Dealer::borderport_input]
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top[] = 
{
    {
        &Top,
        Capsule_Top::internalport_input,
        &Top_slots[InstId_Top],
        1,
        internalfarEndList_Top,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &Top,
        Capsule_Top::internalport_log,
        &Top_slots[InstId_Top],
        1,
        &internalfarEndList_Top[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_ptrs[] = 
{
    &internalports_Top[0],
    &internalports_Top[1]
};

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, internalports_Top_ptrs, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_d1],
    &Top_slots[InstId_Top_p1],
    &Top_slots[InstId_Top_p2],
    &Top_slots[InstId_Top_p3],
    &Top_slots[InstId_Top_p4],
    &Top_slots[InstId_Top_p5],
    &Top_slots[InstId_Top_p6]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_d1,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_p1,
        1,
        &slots_Top[1]
    },
    {
        &Top,
        Capsule_Top::part_p2,
        1,
        &slots_Top[2]
    },
    {
        &Top,
        Capsule_Top::part_p3,
        1,
        &slots_Top[3]
    },
    {
        &Top,
        Capsule_Top::part_p4,
        1,
        &slots_Top[4]
    },
    {
        &Top,
        Capsule_Top::part_p5,
        1,
        &slots_Top[5]
    },
    {
        &Top,
        Capsule_Top::part_p6,
        1,
        &slots_Top[6]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_d1[] = 
{
    {
        0,
        &internalports_Top[Capsule_Top::internalport_input]
    },
    {
        0,
        &borderports_Top_p1[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_p2[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_p3[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_p4[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_p5[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_p6[Capsule_Player::borderport_playPort]
    },
    {
        0,
        &borderports_Top_d1[Capsule_Dealer::borderport_tickOut]
    },
    {
        0,
        &borderports_Top_d1[Capsule_Dealer::borderport_tickIn]
    }
};

UMLRTCommsPort borderports_Top_d1[] = 
{
    {
        &Dealer,
        Capsule_Dealer::borderport_input,
        &Top_slots[InstId_Top_d1],
        1,
        borderfarEndList_Top_d1,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &Dealer,
        Capsule_Dealer::borderport_playPort,
        &Top_slots[InstId_Top_d1],
        6,
        &borderfarEndList_Top_d1[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &Dealer,
        Capsule_Dealer::borderport_tickIn,
        &Top_slots[InstId_Top_d1],
        1,
        &borderfarEndList_Top_d1[7],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true
    },
    {
        &Dealer,
        Capsule_Dealer::borderport_tickOut,
        &Top_slots[InstId_Top_d1],
        1,
        &borderfarEndList_Top_d1[8],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_d1_ptrs[] = 
{
    &borderports_Top_d1[0],
    &borderports_Top_d1[1],
    &borderports_Top_d1[2],
    &borderports_Top_d1[3]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_d1[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_d1[] = 
{
    {
        &Dealer,
        Capsule_Dealer::internalport_timing,
        &Top_slots[InstId_Top_d1],
        1,
        &internalfarEndList_Top_d1[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Dealer,
        Capsule_Dealer::internalport_log,
        &Top_slots[InstId_Top_d1],
        1,
        internalfarEndList_Top_d1,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_d1_ptrs[] = 
{
    &internalports_Top_d1[0],
    &internalports_Top_d1[1]
};

static Capsule_Dealer top_d1( &Dealer, &Top_slots[InstId_Top_d1], borderports_Top_d1_ptrs, internalports_Top_d1_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p1[] = 
{
    {
        0,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p1[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p1],
        1,
        borderfarEndList_Top_p1,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p1_ptrs[] = 
{
    &borderports_Top_p1[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p1[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p1[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p1],
        1,
        internalfarEndList_Top_p1,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p1_ptrs[] = 
{
    &internalports_Top_p1[0]
};

static Capsule_Player top_p1( &Player, &Top_slots[InstId_Top_p1], borderports_Top_p1_ptrs, internalports_Top_p1_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p2[] = 
{
    {
        1,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p2[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p2],
        1,
        borderfarEndList_Top_p2,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p2_ptrs[] = 
{
    &borderports_Top_p2[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p2[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p2[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p2],
        1,
        internalfarEndList_Top_p2,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p2_ptrs[] = 
{
    &internalports_Top_p2[0]
};

static Capsule_Player top_p2( &Player, &Top_slots[InstId_Top_p2], borderports_Top_p2_ptrs, internalports_Top_p2_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p3[] = 
{
    {
        2,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p3[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p3],
        1,
        borderfarEndList_Top_p3,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p3_ptrs[] = 
{
    &borderports_Top_p3[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p3[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p3[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p3],
        1,
        internalfarEndList_Top_p3,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p3_ptrs[] = 
{
    &internalports_Top_p3[0]
};

static Capsule_Player top_p3( &Player, &Top_slots[InstId_Top_p3], borderports_Top_p3_ptrs, internalports_Top_p3_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p4[] = 
{
    {
        3,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p4[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p4],
        1,
        borderfarEndList_Top_p4,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p4_ptrs[] = 
{
    &borderports_Top_p4[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p4[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p4[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p4],
        1,
        internalfarEndList_Top_p4,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p4_ptrs[] = 
{
    &internalports_Top_p4[0]
};

static Capsule_Player top_p4( &Player, &Top_slots[InstId_Top_p4], borderports_Top_p4_ptrs, internalports_Top_p4_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p5[] = 
{
    {
        4,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p5[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p5],
        1,
        borderfarEndList_Top_p5,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p5_ptrs[] = 
{
    &borderports_Top_p5[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p5[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p5[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p5],
        1,
        internalfarEndList_Top_p5,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p5_ptrs[] = 
{
    &internalports_Top_p5[0]
};

static Capsule_Player top_p5( &Player, &Top_slots[InstId_Top_p5], borderports_Top_p5_ptrs, internalports_Top_p5_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_p6[] = 
{
    {
        5,
        &borderports_Top_d1[Capsule_Dealer::borderport_playPort]
    }
};

UMLRTCommsPort borderports_Top_p6[] = 
{
    {
        &Player,
        Capsule_Player::borderport_playPort,
        &Top_slots[InstId_Top_p6],
        1,
        borderfarEndList_Top_p6,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_p6_ptrs[] = 
{
    &borderports_Top_p6[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_p6[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_p6[] = 
{
    {
        &Player,
        Capsule_Player::internalport_log,
        &Top_slots[InstId_Top_p6],
        1,
        internalfarEndList_Top_p6,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_p6_ptrs[] = 
{
    &internalports_Top_p6[0]
};

static Capsule_Player top_p6( &Player, &Top_slots[InstId_Top_p6], borderports_Top_p6_ptrs, internalports_Top_p6_ptrs, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        7,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.d1",
        0,
        &Dealer,
        &Top,
        Capsule_Top::part_d1,
        &top_d1,
        &DefaultController_,
        0,
        NULL,
        4,
        borderports_Top_d1,
        NULL,
        true,
        false
    },
    {
        "Top.p1",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p1,
        &top_p1,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p1,
        NULL,
        true,
        false
    },
    {
        "Top.p2",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p2,
        &top_p2,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p2,
        NULL,
        true,
        false
    },
    {
        "Top.p3",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p3,
        &top_p3,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p3,
        NULL,
        true,
        false
    },
    {
        "Top.p4",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p4,
        &top_p4,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p4,
        NULL,
        true,
        false
    },
    {
        "Top.p5",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p5,
        &top_p5,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p5,
        NULL,
        true,
        false
    },
    {
        "Top.p6",
        0,
        &Player,
        &Top,
        Capsule_Top::part_p6,
        &top_p6,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_p6,
        NULL,
        true,
        false
    }
};

