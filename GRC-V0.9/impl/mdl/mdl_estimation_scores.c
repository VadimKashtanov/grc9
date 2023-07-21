#include "mdl.h"

#define JOURS TAILLE_SESSION

float mdl_score_aveugle(Mdl_t * mdl, uint S, uint N, float alpha) {
	uint jusque = TAILLE_SESSION + rand() % (PRIXS_VALIDES - 1 - TAILLE_SESSION) - 1;
	
	//	Le plus proche depart d'apprentissage. Apres c'est le domaine d'ignorance post-apprentissage
	uint dernier_depart = 1 + jusque - TAILLE_SESSION;

	for (uint n=0; n < N; n++) {
		memset(socle->_dpoid, 0, sizeof(float) * socle->poids);
		//
		for (uint i=0; i < S; i++)
			retro_propa(mdl, rand() % dernier_depart);
		//
		for (uint i=0; i < socle->poids; i++)
			socle->_poid[i] += alpha*socle->_dpoid[i] / (S*JOURS);
	}

	//	Score dans une zone non entrainnee
	return mdl_gain(mdl, jusque);
};

float mdl_moyenne_score_aveugle(Mdl_t * mdl, uint S, uint N, float alpha, uint tours) {
	float _s = 0;
	for (uint i=0; i < tours; i++) _s += mdl_score_aveugle(mdl, S, N, alpha);
	return _s / tours;	//(meme si en soit /tours n'a strictement aucune influence sur la selection)
};