#include "mdl.h"

float tanh1_f(float * dar, float * poid) {return tanh(dar[0]);};
void tanh1_df(float * dar, float * poid, float grad, float * d_dar, float * d_poid) {
	d_dar[0] += grad * d_tanh(dar[0]);
}
void tanh1_d2f(float * dar, float * poid, float dy, float * d_dar, float * d_poid, float d2y, float * d2_dar, float * d2_poid) {
	d2_dar[0] += d2y * pow( d_tanh(dar[0]), 2 ) + dy * dd_tanh(dar[0]);
}
Inst_t tanh1 = {
	tanh1_f, tanh1_df, tanh1_d2f,
	1, //dar
	0, //poids
	"tanh1"
};