
#ifndef _WOLF_PARAMETER_H__
#define _WOLF_PARAMETER_H__


/* --- Init Parameter --- */
/* health */
#define	WOLF_INIT_HEALTH			0x00000080u /* 128	*/
#define	WOLF_MAX_HEALTH				0x00000100u /* 256	*/
#define WOLF_POOR_HEALTH			0x00000040u	/* 64	*/
#define WOLF_EMPTY_HEALTH			0x00000000u	/* 0	*/
#define WOLF_ENOUGH_HEALTH			0x00000060u	/* 96	*/

#define WOLF_REPAIR_HEALTH_VALUE	0x00000008u	/* 8	*/
#define WOLF_DEBILITY_HEALTH_VALUE	0x00000004u	/* 4	*/

/* stamina */
#define	WOLF_INIT_STAMINA			0x00000060u /* 96	*/
#define	WOLF_MAX_STAMINA			0x00000080u /* 128	*/
#define WOLF_POOR_STAMINA			0x00000040u	/* 64	*/
#define WOLF_EMPTY_STAMINA			0x00000000u	/* 0	*/
#define WOLF_ENOUGH_STAMINA			0x00000060u	/* 96	*/

#define	WOLF_RECOVER_STAMINA_VALUE	0x00000008u	/* 8	*/
#define WOLF_MOVE_STAMINA_VALUE		0x00000001u	/* 8	*/

/* waste */
#define WOLF_INIT_WASTE			0x00000000u	/* 0	*/
#define	WOLF_WASTE_CAPACITY		0x00000080u /* 128	*/
#define WOLF_EXCRETED_WASTE		0x00000060u	/* 96	*/

/* energy */
#define	WOLF_ENERGY_CAPACITY	0x00000080u /* 128	*/
#define	WOLF_INIT_ENERGY		0x00000060u /* 96	*/
#define	WOLF_POOR_ENERGY		0x00000040u /* 64	*/
#define WOLF_EMPTY_ENERGY		0x00000000u	/* 0	*/
#define WOLF_ENOUGH_ENERGY		0x00000060u	/* 96	*/

#define	WOLF_TOSOIL_VALUE		0x00000002u /* 2	*/

/* lifespan */
#define	WOLF_LIFESPAN			0x00000040u /* 64	*/

/* Length of sight */
#define WOLF_SIGHT_LENGTH		0x00000004u	/* 4	*/

/* Strength */
#define WOLF_ATTACK_RANGE		0x00000004	/* 2	*/
#define WOLF_ATTACK_DAMAGE		0x00000008	/* 8	*/

/* Agirity */
#define WOLF_WOLKING_DISTANCE	0x00000020	/* 1	*/
#define WOLF_CHASE_DISTANCE		0x00000002	/* 2	*/

/* Vitality */
#define WOLF_TAKED_ENERGY_VALUE	0x00000004	/* 4	*/

/* --- Judgement Parameter --- */
#define WOLF_ADVANTAGE_VALUE	0x00000002	/* 2	*/


#endif /* _WOLF_PARAMETER_H__ */
