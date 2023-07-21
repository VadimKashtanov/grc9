#include "mdl.h"

float logistic1_f(float * dar, float * poid) {return logistique(dar[0]);};
void logistic1_df(float * dar, float * poid, float dy, float * d_dar, float * d_poid) {
	d_dar[0] += dy * d_logistique(dar[0]);
};
void logistic1_d2f(float * dar, float * poid, float dy, float * d_dar, float * d_poid, float d2y, float * d2_dar, float * d2_poid) {
	d2_dar[0] += d2y * pow( d_logistique(dar[0]), 2 ) + dy * dd_logistique(dar[0]);
}

Inst_t logistic1 = {
	logistic1_f, logistic1_df, logistic1_d2f,
	1, //dar
	0, //poids
	"logistique1"
};