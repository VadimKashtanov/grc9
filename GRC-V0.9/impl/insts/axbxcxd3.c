#include "mdl.h"

float axbxcxd3_f(float * dar, float * poid) {return dar[0]*poid[0] + dar[1]*poid[1] + dar[2]*poid[2] + poid[3];};
void axbxcxd3_df(float * dar, float * poid, float dy, float * d_dar, float * d_poid) {
	d_dar[0] += dy * poid[0];
	d_poid[0] += dy * dar[0];
	//
	d_dar[1] += dy * poid[1];
	d_poid[1] += dy * dar[1];
	//
	d_dar[2] += dy * poid[2];
	d_poid[2] += dy * dar[2];
	//
	d_poid[3] += dy;
}
void axbxcxd3_d2f(float * dar, float * poid, float dy, float * d_dar, float * d_poid, float d2y, float * d2_dar, float * d2_poid) {
	d2_dar[0] += d2y * pow(poid[0],2) + dy*1;
	d2_poid[0] += d2y * pow(dar[0],2) + dy*1;
	//
	d2_dar[1] += d2y * pow(poid[1],2) + dy*1;
	d2_poid[1] += d2y * pow(dar[1],2) + dy*1;
	//
	d2_dar[2] += d2y * pow(poid[2],2) + dy*1;
	d2_poid[2] += d2y * pow(dar[2],2) + dy*1;
	//
	d2_poid[3] += d2y * (1*1) + dy*0;
};

Inst_t axbxcxd3 = {
	axbxcxd3_f, axbxcxd3_df, axbxcxd3_d2f,
	3, //dar
	4, //poids
	"axbxcxd3"
};