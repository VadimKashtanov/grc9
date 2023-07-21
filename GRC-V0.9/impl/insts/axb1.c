#include "mdl.h"

float axb1_f(float * dar, float * poid) {return dar[0]*poid[0] + poid[1];};
void axb1_df(float * dar, float * poid, float dy, float * d_dar, float * d_poid) {
	d_dar[0] += dy*poid[0];
	d_poid[0] += dy*dar[0];
	d_poid[1] += dy;
}
void axb1_d2f(float * dar, float * poid, float dy, float * d_dar, float * d_poid, float d2y, float * d2_dar, float * d2_poid) {
	//	d2[n+1] = d2[n]*f'*f' + d[n]*f''
	d2_dar[0] += d2y*(poid[0]*poid[0]) + dy*1;
	d2_poid[0] += d2y*(dar[0]*dar[0]) + dy*1;
	d2_poid[1] += d2y*(1*1) + dy*0;
}
Inst_t axb1 = {
	axb1_f, axb1_df, axb1_d2f,
	1, //dar
	2, //poids
	"axb1"
};