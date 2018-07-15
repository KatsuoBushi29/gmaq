#pragma once

enum Hairiness_t
{
	NONE,
	HAIRY,
};

enum Physique_t
{
	BONY,
	SKINNY,
	SLENDER,
	MEDIUM,
	ROBUST,
	MUSCULAR,
	FAT,
};

enum Condition_t
{
	DYING,
	BAD,
	NORMAL,
	GOOD,
};


typedef struct appearanceFactor {
	Hairiness_t	hairiness;
	Physique_t	physique;
	Condition_t	condition;
} appearanceFactor_t;

enum appearanceFactorIdx_t {
	HAIRINESS,
	PHYSIQUE,
	CONDITION,
	FACTOR_NUM,
};


class Appearance
{
public:
	Appearance(appearanceFactor_t &factor);
	~Appearance(void);

	int calcAdvantage(Appearance &appearance);
	const appearanceFactor_t *getFactor(void);
	void updateFactor(appearanceFactor_t &factor);

private:
	appearanceFactor_t m_factor;

};

