
#ifndef _REED_PARAMETER_H__
#define _REED_PARAMETER_H__


/* --- Init Parameter --- */
/* health */
#define	REED_INIT_HEALTH			0x00000080u /* 128	*/
#define	REED_MAX_HEALTH				0x00000100u /* 256	*/
#define REED_POOR_HEALTH			0x00000040u	/* 64	*/
#define REED_EMPTY_HEALTH			0x00000000u	/* 0	*/
#define REED_ENOUGH_HEALTH			0x00000060u	/* 96	*/

#define REED_REPAIR_HEALTH_VALUE	0x00000008u	/* 8	*/
#define REED_DEBILITY_HEALTH_VALUE	0x00000004u	/* 4	*/

/* stamina */
#define	REED_INIT_STAMINA			0x00000060u /* 96	*/
#define	REED_MAX_STAMINA			0x00000080u /* 128	*/
#define REED_POOR_STAMINA			0x00000040u	/* 64	*/
#define REED_EMPTY_STAMINA			0x00000000u	/* 0	*/
#define REED_ENOUGH_STAMINA			0x00000060u	/* 96	*/

#define	REED_RECOVER_STAMINA_VALUE	0x00000008u	/* 8	*/
#define REED_MOVE_STAMINA_VALUE		0x00000001u	/* 8	*/

/* waste */
#define REED_INIT_WASTE			0x00000000u	/* 0	*/
#define	REED_WASTE_CAPACITY		0x00000080u /* 128	*/
#define REED_EXCRETED_WASTE		0x00000060u	/* 96	*/

/* energy */
#define	REED_ENERGY_CAPACITY	0x00000080u /* 128	*/
#define	REED_INIT_ENERGY		0x00000060u /* 96	*/
#define	REED_POOR_ENERGY		0x00000040u /* 64	*/
#define REED_EMPTY_ENERGY		0x00000000u	/* 0	*/
#define REED_ENOUGH_ENERGY		0x00000060u	/* 96	*/

#define	REED_TOSOIL_VALUE		0x00000002u /* 2	*/

/* lifespan */
#define	REED_LIFESPAN			0x00000040u /* 64	*/

/* Length of sight */
#define REED_SIGHT_LENGTH		0x00000001u	/* 1	*/

/* Strength */
#define REED_ATTACK_RANGE		0x00000004	/* 2	*/
#define REED_ATTACK_DAMAGE		0x00000008	/* 8	*/

/* Agirity */
#define REED_WOLKING_DISTANCE	0x00000020	/* 1	*/
#define REED_CHASE_DISTANCE		0x00000002	/* 2	*/

/* Vitality */
#define REED_TAKED_ENERGY_VALUE	0x00000004	/* 4	*/

/* --- Judgement Parameter --- */
#define REED_ADVANTAGE_VALUE	0x00000002	/* 2	*/


#endif /* _REED_PARAMETER_H__ */
