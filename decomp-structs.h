#pragma once

#ifndef _DECOMP_STRUCTS_H_
#define _DECOMP_STRUCTS_H_

#include <SADXModLoader.h>


#define CWK_FLAG_HIT    0x1          /* Currently intersecting another collision */
#define CWK_FLAG_2      0x2          /* ? */
#define CWK_FLAG_4      0x4          /* ? */
#define CWK_FLAG_8      0x8          /* ? */
#define CWK_FLAG_PUSH   0x10         /* Currently being pushed by another collision */
#define CWK_FLAG_DAMAGE 0x20         /* Currently receiving damage */
#define CWK_FLAG_HOMING 0x40         /* Can be added to the target lists */
#define CWK_FLAG_INFO   0x8000       /* Contains a valid info array */

#define CI_ATTR_NO_SEND      0x4     /* Do not send information to other collisions */
#define CI_ATTR_NO_RECEIVE   0x8     /* Do not receive information from other collisions */
#define CI_ATTR_IGNORE       0x10    /* Do not run physical collision check */
#define CI_ATTR_POS_ABSOLUTE 0x20    /* The position is no longer relative to the entity */
#define CI_ATTR_ANG_YZX      0x200   /* Use YZX rotation order instead of ZXY */
#define CI_ATTR_DAMAGE       0x400   /* Allow damage */
#define CI_ATTR_2000         0x2000  /* ? */
#define CI_ATTR_NO_PUSH      0x4000  /* Do not get pushed by other collisions */
#define CI_ATTR_ANG_ABSOLUTE 0x8000  /* The angle is no longer relative to the entity */

#define PL_FLAG_ONLAND     0x1                              /* On a geometry collision */
#define PL_FLAG_ONCCL      0x2                              /* On a shape collision */
#define PL_FLAG_FLOOR      (PL_FLAG_ONLAND | PL_FLAG_ONCCL) /* On geometry or shape collision */
#define PL_FLAG_DAMAGE     0x4                              /* Player is hurt */
#define PL_FLAG_COLLIDED   0x8                              /* Touched a collision */
#define PL_FLAG_10         0x10                             /* ? */
#define PL_FLAG_20         0x20                             /* ? */
#define PL_FLAG_BALL       0x100                            /* Ball mode */
#define PL_FLAG_LIGHTDASH  0x200                            /* In Light Speed Dash mode */
#define PL_FLAG_ATTACK     0x400                            /* Can hurt other entities */
#define PL_FLAG_HOLD       0x800                            /* Holding mode */
#define PL_FLAG_INPUT      0x1000                           /* Following a guiding path */
#define PL_FLAG_PATH       0x2000                           /* Following a guiding path */
#define PL_FLAG_NOCON      0x4000                           /* Control disabled */

/******** �{�^���萔 *******************************************************/
/******** Button ***********************************************************/
#define PDD_DGT_TL    (1 << 17)            /* L�{�^��(�G�~�����[�V����)    */
										   /* L button(emulation)          */
#define PDD_DGT_TR    (1 << 16)            /* R�{�^��(�G�~�����[�V����)    */
										   /* R button(emulation)          */
#define PDD_DGT_KRB   (1 << 15)            /* �f�W�^���\���L�[B�E          */
										   /* Right button B               */
#define PDD_DGT_KLB   (1 << 14)            /* �f�W�^���\���L�[B��          */
										   /* Left button B                */
#define PDD_DGT_KDB   (1 << 13)            /* �f�W�^���\���L�[B��          */
										   /* Down button B                */
#define PDD_DGT_KUB   (1 << 12)            /* �f�W�^���\���L�[B��          */
										   /* Up button B                  */
#define PDD_DGT_TD    (1 << 11)            /* D�{�^��                      */
										   /* D button                     */
#define PDD_DGT_TX    (1 << 10)            /* X�{�^��                      */
										   /* X button                     */
#define PDD_DGT_TY    (1 <<  9)            /* Y�{�^��                      */
										   /* Y button                     */
#define PDD_DGT_TZ    (1 <<  8)            /* Z�{�^��                      */
										   /* Z button                     */
#define PDD_DGT_KR    (1 <<  7)            /* �f�W�^���\���L�[A�E          */
										   /* Right button A               */
#define PDD_DGT_KL    (1 <<  6)            /* �f�W�^���\���L�[A��          */
										   /* Left button A                */
#define PDD_DGT_KD    (1 <<  5)            /* �f�W�^���\���L�[A��          */
										   /* Down button A                */
#define PDD_DGT_KU    (1 <<  4)            /* �f�W�^���\���L�[A��          */
										   /* Up button A                  */
#define PDD_DGT_ST    (1 <<  3)            /* �X�^�[�g�{�^��               */
										   /* Start button                 */
#define PDD_DGT_TA    (1 <<  2)            /* A�{�^��                      */
										   /* A button                     */
#define PDD_DGT_TB    (1 <<  1)            /* B�{�^��                      */
										   /* B button                     */
#define PDD_DGT_TC    (1 <<  0)            /* C�{�^��                      */
										   /* C button                     */

const Sint32 jump_button = PDD_DGT_TA;
const Sint32 action_button = (PDD_DGT_TB | PDD_DGT_TX);
const Sint32 camera_button = 0;
const Sint32 hold_button = (PDD_DGT_TB | PDD_DGT_TX);

enum {
	PSG_TYPE_FLOOR,
	PSG_TYPE_WALL,
	PSG_TYPE_CRASH,
	PSG_TYPE_OTTOTTO
};

enum {
	MD_MTN_INIT,
	MD_MTN_SET,
	MD_MTN_CHNG,
	MD_MTN_LOOP,
	MD_MTN_NEXT,
	MD_MTN_STOP,
	MD_MTN_TXEN,
	MD_MTN_POTS,
	MD_MTN_COMB,
	MD_MTN_XSPD,
	MD_MTN_WORK,
	MD_MTN_WKNX,
	MD_MTN_MANU,
	MD_MTN_TRNS,
	MD_MTN_END
};

enum {
	PLNO_SONIC,
	PLNO_EGGMAN,
	PLNO_TAILS,
	PLNO_KNUCKLES,
	PLNO_TIKAL,
	PLNO_AMY,
	PLNO_E102,
	PLNO_BIG,
	PLNO_METAL_SONIC,
	NB_PLNO
};


#endif _DECOMP_STRUCTS_H_