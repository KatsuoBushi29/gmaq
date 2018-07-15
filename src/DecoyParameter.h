#ifndef _DECOY_PARAMETER_H__
#define _DECOY_PARAMETER_H__


/* --- Init Parameter --- */
/* health */
#define	DECOY_INIT_HEALTH			0x00000080u /* 128	*/
#define	DECOY_MAX_HEALTH			0x00000100u /* 256	*/
#define DECOY_POOR_HEALTH			0x00000040u	/* 64	*/
#define DECOY_EMPTY_HEALTH			0x00000000u	/* 0	*/
#define DECOY_ENOUGH_HEALTH			0x00000060u	/* 96	*/

#define DECOY_REPAIR_HEALTH_VALUE	0x00000008u	/* 8	*/
#define DECOY_DEBILITY_HEALTH_VALUE	0x00000004u	/* 4	*/

/* stamina */
#define	DECOY_INIT_STAMINA			0x00000060u /* 96	*/
#define	DECOY_MAX_STAMINA			0x00000080u /* 128	*/
#define DECOY_POOR_STAMINA			0x00000040u	/* 64	*/
#define DECOY_EMPTY_STAMINA			0x00000000u	/* 0	*/
#define DECOY_ENOUGH_STAMINA		0x00000060u	/* 96	*/

#define	DECOY_RECOVER_STAMINA_VALUE	0x00000008u	/* 8	*/
#define DECOY_MOVE_STAMINA_VALUE	0x00000001u	/* 8	*/

/* waste */
#define DECOY_INIT_WASTE			0x00000000u	/* 0	*/
#define	DECOY_WASTE_CAPACITY		0x00000080u /* 128	*/
#define DECOY_EXCRETED_WASTE		0x00000060u	/* 96	*/

/* energy */
#define	DECOY_ENERGY_CAPACITY		0x00000080u /* 128	*/
#define	DECOY_INIT_ENERGY			0x00000060u /* 96	*/
#define	DECOY_POOR_ENERGY			0x00000040u /* 64	*/
#define DECOY_EMPTY_ENERGY			0x00000000u	/* 0	*/
#define DECOY_ENOUGH_ENERGY			0x00000060u	/* 96	*/

#define	DECOY_TOSOIL_VALUE			0x00000002u /* 2	*/

/* lifespan */
#define	DECOY_LIFESPAN				0x00000040u /* 64	*/

/* Strength */
#define DECOY_ATTACK_RANGE			0x00000004	/* 2	*/
#define DECOY_ATTACK_DAMAGE			0x00000008	/* 8	*/

/* Agirity */
#define DECOY_WOLKING_DISTANCE		0x00000020	/* 1	*/
#define DECOY_CHASE_DISTANCE		0x00000002	/* 2	*/

/* Vitality */
#define DECOY_TAKED_ENERGY_VALUE	0x00000004	/* 4	*/

/* --- Judgement Parameter --- */
#define DECOY_ADVANTAGE_VALUE		0x00000002	/* 2	*/


#endif /* _DECOY_PARAMETER_H__ */
