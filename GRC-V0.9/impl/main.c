#include "mdl.h"

void comparer() {
	Mdl_t * mdl = generique();
	lier_le_socle(mdl);
	aleatoire_poids();
	plum_mdl_socle(mdl);
	printf("Poids : %i\n", socle->poids);
	//
	uint depart = 0;
	//
	float f = mdl_gain(mdl, depart);
	for (uint i=0; i < total * TAILLE_SESSION; i++)
		printf("%f, ", socle->_var[i]);
	printf("\n");
	//
	socle->_poid[0] -= 1.0;
	printf("====\n");
	//
	f = mdl_gain(mdl, depart);
	for (uint i=0; i < total * TAILLE_SESSION; i++)
		printf("%f, ", socle->_var[i]);
	printf("\n");
	//raise(SIGINT);
	//
	plum_mdl_socle(mdl);
};

void verifier_derivee_seconde() {
	Mdl_t * mdl = generique();
	lier_le_socle(mdl);
	aleatoire_poids();
	//
	plum_mdl_socle(mdl);
	printf("Poids : %i\n", socle->poids);
	//
	uint depart = 0;
	//	/= (S*JOURS)
	//
	float _grad_fait_maison[socle->poids];
	float _grad2_fait_maison[socle->poids];
	//
	float _f, f_1e5, f_1e10;

	float _1E5 = 1e-3;

	_f = mdl_gain(mdl, depart);

	for (uint i=0; i < socle->poids; i++) {
		socle->_poid[i] += _1E5;
		f_1e5 = mdl_gain(mdl, depart);
		raise(SIGINT);
		socle->_poid[i] += _1E5;
		f_1e10 = mdl_gain(mdl, depart);
		raise(SIGINT);
		socle->_poid[i] -= _1E5*2;
		//
		_grad_fait_maison[i] = (f_1e5-_f)/_1E5;
		_grad2_fait_maison[i] = (f_1e10-2*f_1e5+_f)/(_1E5*_1E5);
	};
	printf(" ========== \n");
	//
	//
	memset(socle->_dpoid, 0, sizeof(float) * socle->poids);
	memset(socle->_d2poid, 0, sizeof(float) * socle->poids);
	retro_propa_2(mdl, depart);
	//
	printf(" ========== \n");
	//
	printf("dF/dx\n");
	for (uint i=0; i < socle->poids; i++) {
		printf("%f == %f\n", _grad_fait_maison[i], socle->_dpoid[i]);
	}
	printf("d2F/d2x\n");
	for (uint i=0; i < socle->poids; i++) {
		printf("%f == %f\n", _grad2_fait_maison[i], socle->_d2poid[i]);
	}
	printf("fait maison | retro_propa_2\n");
};

void main() {
	charger_les_prixs();
	generer_les_instructions();

	// ========== Ker Programme ==========
	printf("======= Ker Programme ==========\n");
	
	//verifier_derivee_seconde();
	comparer();
	
	//float infos[50000];
	//for (uint i=0; i < 50000; i++)
	//	infos[i] = valeurs[i*INFOS_FOURNIE + 0];
	//gnuplot(infos, 50000);
	
	// ===================================

	liberer_les_prixs();
};