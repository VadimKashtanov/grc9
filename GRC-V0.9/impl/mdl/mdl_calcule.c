#include "mdl.h"

void mdl_nouveau_jour(Mdl_t * mdl, uint jour, uint depart) {
	//memset(socle->_var + jour*total + DAR, 0,	sizeof(float) * (total-DAR));
	//for (uint i=0; i < DAR; i++) socle->_var[jour*mdl->socle->total + i] = valeurs[depart*INFORMATION_FOURNIE + i];
	for (uint i=0; i < socle->dar_influents; i++) {
		socle->_var[jour*total + socle->influent[i]] = valeurs[depart*INFOS_FOURNIE + socle->influent[i]];
	}
};

void mdl_f(Mdl_t * mdl, uint jour) {
	float null_flt_ptr[] = {0};
	//
	float entree[max_dar];
	//
	uint inst, temps, __i;
	for (uint i=socle->dar_influents; i < socle->influents; i++) {
		__i = socle->influent[i];
		
		inst = mdl->neurone_inst[__i];

		//	Calcule des connections
		for (uint j=0; j < INST[inst]->dar; j++) {
			temps = mdl->conn_temps[__i][j];
			//
			if (jour > 0) {
				entree[j] = INST_1DAR[ mdl->conn_inst[__i][j] ]->f(
					socle->_var + (jour-temps)*total + mdl->conn[__i][j],
					socle->_poid + socle->conn_poid_depart[__i][j]
				);
				if (temps == 1) raise(SIGINT);
			} else {
				entree[j] = INST_1DAR[ mdl->conn_inst[__i][j] ]->f(
					(temps == 1 ? null_flt_ptr : socle->_var + mdl->conn[__i][j]),
					socle->_poid + socle->conn_poid_depart[__i][j]
				);
			}
		};

		//	Calcule des neurones
		socle->_var[jour*total + __i] = INST[inst]->f(
			entree,
			socle->_poid + socle->neurone_poid_depart[__i]
		);
	};
};

//	selection haplogroupique
//	beaucoup plus couteux (ou pas jsp)
//	ca assure la stabilitee

float mdl_gain(Mdl_t * mdl, uint depart) {
	float usdt = DEPART_SESSION;
	float pourcent, levier, p0, p1;
	float changement;
	//
	for (uint i=0; i < TAILLE_SESSION; i++)
	{
		mdl_nouveau_jour(mdl, i, depart + i);
		mdl_f(mdl, i);
		//
		pourcent = tanh(socle->_var[(i+1)*total - 2]);
		levier = 1+(LEVIER_MAX-1)/(1.0 + expf(-socle->_var[(i+1)*total - 1]));
		p0 = prixs[depart + i];
		p1 = prixs[depart + i+1];
		//
		changement = usdt*pourcent*levier*(p1/p0 - 1);
		usdt += changement;
	}
	//
	return usdt - DEPART_SESSION;
};

float mdl_sessions(Mdl_t * mdl, uint S) {
	float gain = 0;
	for (uint i=0; i < S; i++) {
		gain += mdl_gain(mdl, rand() % (PRIXS_VALIDES-TAILLE_SESSION-1));
	}
	return gain;
};

float mdl_gain_derniers_jours(Mdl_t * mdl) {
	return mdl_gain(mdl, PRIXS_VALIDES-TAILLE_SESSION-1);
};