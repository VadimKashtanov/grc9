#include "mdl.h"

float axbxc2_f(float * dar, float * poid) {return dar[0]*poid[0] + dar[1]*poid[1] + poid[2];};
void axbxc2_df(float * dar, float * poid, float dy, float * d_dar, float * d_poid) {
	d_dar[0] += dy * poid[0];
	d_poid[0] += dy * dar[0];
	d_dar[1] += dy * poid[1];
	d_poid[1] += dy * dar[1];
	d_poid[2] += dy;
}
void axbxc2_d2f(float * dar, float * poid, float dy, float * d_dar, float * d_poid, float d2y, float * d2_dar, float * d2_poid) {
	//	d2[n+1] = d2[n]*f'*f' + d[n]*f''
	d2_dar[0] += d2y * (poid[0]*poid[0]) + dy * 1;
	d2_poid[0] += d2y * (dar[0]*dar[0]) + dy * 1;
	d2_dar[1] += d2y * (poid[1]*poid[1]) + dy * 1;
	d2_poid[1] += d2y * (dar[1]*dar[1]) + dy * 1;
	d2_poid[2] += d2y * (1*1) + dy*0;
};

Inst_t axbxc2 = {
	axbxc2_f, axbxc2_df, axbxc2_d2f,
	2, //dar
	3, //poids
	"axbxc2"
};