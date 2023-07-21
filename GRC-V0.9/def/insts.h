#pragma once

#include "etc.h"

typedef float (*f_t)(
	float * dar, float * poid);
typedef void (*df_t)(
	float * dar, float * poids,
	float dy, float * d_dar, float * d_poid);
typedef void (*d2f_t)(	//grad2 donc dwidwi pas dwidwj
	float * dar, float * poids,
	float dy, float * d_dar, float * d_poid,
	float d2y, float * d2_dar, float * d2_poid);

typedef struct {
	f_t f;
	df_t df;
	d2f_t d2f;
	//ddf_t ddf;
	//
	uint dar;	//	Chaque instruction a `dar` entrees
	uint poids;	//	Chaque instruction possede N poids
	//
	char * nom;
} Inst_t;

//	Nb max Entree et Poids
#define max_dar 3
#define max_poid 4

//	Un neurone peut avoire >1 entrees
//	Une connection peut avoire 1 entree
#define INSTS 6
uint INSTS_1DAR;
Inst_t * INST[INSTS];
Inst_t * INST_1DAR[INSTS];

void generer_les_instructions();

//
Inst_t logistic1;
Inst_t tanh1;
Inst_t gauss1;
Inst_t axb1;
Inst_t axbxc2;
Inst_t axbxcxd3;

#define LOGISTIQUE 0
#define TANH 1
#define GAUSS 2
#define AXB 3
#define AXBXC 4
#define AXBXCXD 5

#define NEU1 AXB
#define NEU2 AXBXC
#define NEU3 AXBXCXD 