#include "mdl.h"

#define JOURS TAILLE_SESSION

void mdl_gradient(Mdl_t * mdl, uint S, uint graine) {
	srand(graine);
	float _fx, _f;
	_f = mdl_sessions(mdl, S);
	//
	float _1E5 = 1e-3;
	//
	for (uint i=0; i < socle->poids; i++) {
		socle->_poid[i] += _1E5;
		srand(graine);
		_fx = mdl_sessions(mdl, S);
		socle->_poid[i] -= _1E5;
		//
		socle->_dpoid[i] = (_fx - _f)/_1E5    /  (S*JOURS);
	}
};

void mdl_optimiser(Mdl_t * mdl, uint N, float alpha) {
	for (uint n=0; n < N; n++) {
		mdl_gradient(mdl, 10, rand() % 10000);
		for (uint i=0; i < socle->poids; i++) socle->_poid[i] += alpha*socle->_dpoid[i];
	}
};

float mdl_estimer_meilleur(Mdl_t * mdl, uint S, uint N, float alpha) {
	uint graine_ancienne = rand() % 1000000;
	//
	uint graine_test = rand() % 100000;
	//
	srand(graine_test);
	float meilleur = mdl_sessions(mdl, S);
	//
	float tmp;
	//
	for (uint n=0; n < N; n++) {
		mdl_gradient(mdl, S, graine_test + n);
		for (uint i=0; i < socle->poids; i++)
			socle->_poid[i] += alpha*socle->_dpoid[i];
		//
		srand(graine_test);
		tmp = mdl_sessions(mdl, S);
		if (tmp > meilleur)
			meilleur = tmp;
	}

	//	Apres avoire "deregler avec srand" on "reregle sur une ancienne graine"
	srand(graine_ancienne);
	//
	return meilleur;
};
