#pragma once

#include "marchee.h"
#include "insts.h"

#define KER 12
#define total (DAR+KER+EXI)

typedef struct {//Socle_t {
	float _var[total * TAILLE_SESSION];
	float _grad[total * TAILLE_SESSION];
	float _grad2[total * TAILLE_SESSION];	//dsds/dxidxi
	//
	float _poid[(KER+EXI)*(max_poid + max_dar*max_poid)];
	float _dpoid[(KER+EXI)*(max_poid + max_poid*max_poid)];
	float _d2poid[(KER+EXI)*(max_poid + max_poid*max_poid)];	//	dsds/dwidwi

	//==============================

	//	Il peut y avoire plusieurs poids par instruction
	//	Depart des poids pour chaque neurone
	uint neurone_poid_depart[total];		//pos dans _poid
	uint conn_poid_depart[total][max_dar];	//pos dans _poid
	//
	uint actifs;		//	Ceux qui ne sont pas neutre
	uint actif[total];	//
	//
	uint influents;			//	Ceux qui sont sur le chemin des EXI
	uint dar_influents;		//	Cmb de dar sont influents
	uint ker_influents;		//	Cmb de ker sont influents
	//
	uint influent_oui_non[total];	//	0;1
	uint influent[total];			//	pos dans neurone_inst

	/*	Poids  */
	uint poids;
} Socle_t;// __socle = {0};

//struct Socle_t * socle = &__socle;

Socle_t __socle;
Socle_t * socle;

typedef struct mdl_t {
	uint neurone_inst[total];
	uint conn[total][max_dar];
	uint conn_temps[total][max_dar];
	uint conn_inst[total][max_dar];
} Mdl_t;

//	Mem
Mdl_t * cree_mdl();
Mdl_t * copier_mdl(Mdl_t * mdl);

//	Associe le model au socle. Model pret a calculer.
void lier_le_socle(Mdl_t * mdl);

void plum_mdl_socle(Mdl_t * mdl); 

//	Controle
void aleatoire_poids();

//	Generique
Mdl_t * generique();

//	Calcule
void mdl_nouveau_jour(Mdl_t * mdl, uint jour, uint depart);
void mdl_f(Mdl_t * mdl, uint jour);
//
float mdl_gain(Mdl_t * mdl, uint depart);
float mdl_sessions(Mdl_t * mdl, uint S);
float mdl_gain_derniers_jours(Mdl_t * mdl);

//	Calcule Derivation
void mdl_gradient(Mdl_t * mdl, uint S, uint graine);
void mdl_optimiser(Mdl_t * mdl, uint N, float alpha);
float mdl_estimer_meilleur(Mdl_t * mdl, uint S, uint N, float alpha);
//
//void mdl_df(Mdl_t * mdl, uint jour);
void retro_propa(Mdl_t * mdl, uint depart);
void mdl_retro_propagation(Mdl_t * mdl, uint S, uint grain);
void mdl_optimiser_retro_propa(Mdl_t * mdl, uint S, uint N, float alpha);
float mdl_estimer_meilleur_retro_propa(Mdl_t * mdl, uint S, uint N, float alpha);
//
//void mdl_d2f(Mdl_t * mdl, uint jour);
void retro_propa_2(Mdl_t * mdl, uint depart);
void mdl_retro_propagation_2(Mdl_t * mdl, uint S, uint grain);
void mdl_optimiser_retro_propa_2(Mdl_t * mdl, uint S, uint N);

//	Scores
float mdl_score_aveugle(Mdl_t * mdl, uint S, uint N, float alpha);
float mdl_moyenne_score_aveugle(Mdl_t * mdl, uint S, uint N, float alpha, uint tours);