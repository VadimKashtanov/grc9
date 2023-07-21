#include "mdl.h"

#define JOURS TAILLE_SESSION

void mdl_df(Mdl_t * mdl, uint jour) {
	float null_flt_ptr[] = {0};
	//
	float entree[max_dar];
	float d_entree[max_dar];
	//
	uint inst, temps, __i;
	for (int i=socle->influents-1; i >=0; i--) {
		__i = socle->influent[i];
		
		inst = mdl->neurone_inst[__i];

		//	Gradient du neurone
		//mdl->socle->_var[jour*mdl->socle->total + __i] = insts_neurone[inst]->f(
		//	entree,
		//	mdl->socle->_poid + mdl->neurone_poid_depart[__i]
		//);

		//	Propagation connections
		for (uint j=0; j < INST[inst]->dar; j++) {
			temps = mdl->conn_temps[__i][j];
			//
			if (jour > 0) {
					entree[j] = INST_1DAR[ mdl->conn_inst[__i][j] ]->f(
					socle->_var + (jour-temps)*total + mdl->conn[__i][j],
					socle->_poid + socle->conn_poid_depart[__i][j]
				);
			} else {
				entree[j] = INST_1DAR[ mdl->conn_inst[__i][j] ]->f(
					(temps == 1 ? null_flt_ptr : socle->_var + mdl->conn[__i][j]),
					socle->_poid + socle->conn_poid_depart[__i][j]
				);
			}
		};

		//	Gradient du neurone
		memset(d_entree, 0, sizeof(float) * max_dar);
		INST[inst]->df(
			entree,
			socle->_poid + socle->neurone_poid_depart[__i],
			//
			socle->_grad[jour*total + __i],
			//
			d_entree,
			socle->_dpoid + socle->neurone_poid_depart[__i]
		);

		//	Propagation connections
		for (uint j=0; j < INST[inst]->dar; j++) {
			temps = mdl->conn_temps[__i][j];
			//
			if (jour > 0) {
				INST_1DAR[ mdl->conn_inst[__i][j] ]->df(
					socle->_var + (jour-temps)*total + mdl->conn[__i][j],
					socle->_poid + socle->conn_poid_depart[__i][j],
					//
					d_entree[j],
					//
					socle->_grad + (jour-temps)*total + mdl->conn[__i][j],
					socle->_dpoid + socle->conn_poid_depart[__i][j]
				);
			} else {
				if (temps == 0) {
					INST_1DAR[ mdl->conn_inst[__i][j] ]->df(
						socle->_var + mdl->conn[__i][j],
						socle->_poid + socle->conn_poid_depart[__i][j],
						//
						d_entree[j],
						//
						socle->_grad + mdl->conn[__i][j],
						socle->_dpoid + socle->conn_poid_depart[__i][j]
					);
				}
			}
		};
	};
};

void retro_propa(Mdl_t * mdl, uint depart) {
	float * grad = socle->_grad;
	//
	float usdt_lst[JOURS];
	float usdt = DEPART_SESSION;
	float pourcent, levier, p0, p1;
	//
	float gain_potentiel = DEPART_SESSION;
	//
	//	Propagation
	//
	for (uint j=0; j < JOURS; j++) {
		//
		memset(grad + j*total, 0, sizeof(float) * total);
		//
		usdt_lst[j] = usdt;
		mdl_nouveau_jour(mdl, j, depart + j);
		mdl_f(mdl, j);
		//
		pourcent = tanh(socle->_var[(j+1)*total - 2]);
		levier = 1+(LEVIER_MAX-1)/(1.0 + expf(-socle->_var[(j+1)*total - 1]));
		p0 = prixs[depart + j];
		p1 = prixs[depart + j+1];
		//
		usdt += usdt*pourcent*levier*(p1/p0 - 1);
		gain_potentiel += LEVIER_MAX*gain_potentiel*1.0*(p1/p0 - 1);
	}

	//float score = .5*pow( gain_potentiel - (usdt-DEPART_SESSION) , 2);
	//float dscore = ((usdt-DEPART_SESSION) - gain_potentiel > 0) ? 1 : -1;
	float dscore = ((usdt) > 0) ? 1 : -1;
	//float dscore = (usdt-DEPART_SESSION) - gain_potentiel;

	//
	//	Retro Propagation
	//
	float dusdt, dpourcent, dlevier, dfx;
	//
	dusdt = dscore;
	for (int j=JOURS-1; j >= 0; j--) {
		pourcent = tanh(socle->_var[(j+1)*total - 2]);
		levier = 1+(LEVIER_MAX-1)/(1.0 + expf(-socle->_var[(j+1)*total - 1]));
		p0 = prixs[depart + j];
		p1 = prixs[depart + j+1];
		//
		//usdt = usdt + usdt*f(x)*(p1/p0 - 1)
		//usdt = usdt + usdt*pourcent*levier*(p1/p0 - 1));
		//
		dfx = dusdt * usdt_lst[j]*(p1/p0 - 1.0);
		//
		dpourcent = (1 - pourcent*pourcent) * levier * dfx;
		dlevier = (levier-1) * (LEVIER_MAX-1 - (levier-1)) * pourcent * dfx/(LEVIER_MAX-1);
		dusdt *= (1 + pourcent*levier*(p1/p0 - 1));
		//
		grad[j*total + total - 1] = dlevier;
		grad[j*total + total - 2] = dpourcent;
		//
		mdl_df(mdl, j);
	};
};

void mdl_retro_propagation(Mdl_t * mdl, uint S, uint graine) {
	memset(socle->_dpoid, 0, sizeof(float) * socle->poids);
	//
	srand(graine);
	for (uint i=0; i < S; i++) {
		//srand(graine + i);
		retro_propa(mdl, rand() % PRIXS_VALIDES);
	}
	for (uint i=0; i < socle->poids; i++) socle->_dpoid[i] /= (S*JOURS);
};

void mdl_optimiser_retro_propa(Mdl_t * mdl, uint S, uint N, float alpha) {
	for (uint n=0; n < N; n++) {
		mdl_retro_propagation(mdl, S, rand() % 10000);
		for (uint i=0; i < socle->poids; i++) {
			socle->_poid[i] += alpha*socle->_dpoid[i];
		}
	}
};

float mdl_estimer_meilleur_retro_propa(Mdl_t * mdl, uint S, uint N, float alpha) {
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
		mdl_retro_propagation(mdl, S, graine_test + n);
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
}