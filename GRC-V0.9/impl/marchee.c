#include "marchee.h"

/*
Infos:
	#0
	moy[4000:5000]
	moy[3000:4000]
	moy[2000:3000]		moyenne 1000
	moy[1000:2000]
	moy[   0:1000]
	#4
	moy[400:500]
	moy[300:400]
	moy[200:300]		moyenne 100
	moy[100:200]
	moy[  0:100]
	#9
	[10]
	[9]
	[8]
	[7]
	[6]					prixs
	[5]
	[4]
	[3]
	[2]
	[1]
	[0]
	#29
	ema[36:45]
	ema[27:36]
	ema[18:27]			moyenne dynamique 9
	ema[9:18]
	ema[0 :9]
	#
	ema[48:60]
	ema[36:48]
	ema[24:36]			moyenne dynamique 12
	ema[12:24]
	ema[0 :12]
	#
	ema[104:130]
	ema[78:104]
	ema[52:78]			moyenne dynamique 26
	ema[26:52]
	ema[0 :26]
	#
	macd_signale[]
	macd_signale[]
	macd_signale[]		= ema9
	macd_signale[]
	macd_signale[]
	#
	macd_macd[]
	macd_macd[]
	macd_macd[]			= ema12 - ema26
	macd_macd[]
	macd_macd[]
*/

/*static void les_valeurs() {
	uint DEPART = 5000;
	PRIXS_VALIDES = PRIXS - DEPART;
	//
	INFOS_FOURNIE = 5+5+10+ 5+5+5+ 5+5;
	INFOS = INFOS_FOURNIE * PRIXS_VALIDES;
	//
	valeurs = malloc(sizeof(float) * INFOS);
	//
	//	float _somme4000_5000;
	//	float _somme3000_4000;
	//	float _somme2000_3000;
	//	float _somme1000_2000;
	//	float _somme0000_1000;
	//	//
	//	float _somme400_500;
	//	float _somme300_400;
	//	float _somme200_300;
	//	float _somme100_200;
	//	float _somme000_100;
	

	//	DEPART est le minimum pour avoire la moyenne la plus grosse.
	//On fait les moyenne avant DEPART pour chaque intervalle.
	//Puis pour chaque nouvelle heure : -premier +actuel
	

	float _somme4000_5000[5*2];
	memset(_somme4000_5000, 0, sizeof(float) * 5*2);
	for (uint i=0; i < 2; i++) {
		for (uint j=0; j < 5; j++) {
			for (uint k=0; k < pow(10, 3-i); k++) {
				_somme4000_5000[i*5 + j] += prixs[DEPART-(5-j)*(uint)powf(10,3-i) + k];
			}
		}
	}

	float ema[5*3];
	uint periode[3] = {9, 12, 26};
	float k[3] = {1.0/10.0, 1.0/13.0, 1.0/27.0};
	memset(ema, 0, sizeof(float) * 5*3);
	for (uint p=0; p < 3; p++) {
		for (int i=4; i >= 0; i--) {
			for (uint j=i*periode[m]; j < DEPART; j++) {
				ema[p*5 + 4-i] = prixs[j-i*periode[m]]*k[m] + ema[p*5 + 4-i]*(1 - k[m]); 
			}
		}
	};
	
	//
	for (uint i=0; i < PRIXS_VALIDES; i++) {

		//	Moyenne1000, Moyenne100
		for (uint m=0; m < 2; m++) {
			for (uint j=0; j < 5; j++) {
				_somme4000_5000[m*5 + j] -= prixs[DEPART-(5-j)*(uint)powf(10,3-m) + 0 + i];
				_somme4000_5000[m*5 + j] += prixs[DEPART-(4-j)*(uint)powf(10,3-m) + 0 + i];
				//
				valeurs[i*INFOS_FOURNIE + m*5 + j] = _somme4000_5000[m*5 + j] / (uint)powf(10, 3-m);
			}
		}
		
		//	Prixs[-10:]
		valeurs[i*INFOS_FOURNIE + 15] = prixs[DEPART+i-9];
		valeurs[i*INFOS_FOURNIE + 16] = prixs[DEPART+i-8];
		valeurs[i*INFOS_FOURNIE + 17] = prixs[DEPART+i-7];
		valeurs[i*INFOS_FOURNIE + 18] = prixs[DEPART+i-6];
		valeurs[i*INFOS_FOURNIE + 19] = prixs[DEPART+i-5];
		valeurs[i*INFOS_FOURNIE + 20] = prixs[DEPART+i-4];
		valeurs[i*INFOS_FOURNIE + 21] = prixs[DEPART+i-3];
		valeurs[i*INFOS_FOURNIE + 22] = prixs[DEPART+i-2];
		valeurs[i*INFOS_FOURNIE + 23] = prixs[DEPART+i-1];
		valeurs[i*INFOS_FOURNIE + 24] = prixs[DEPART+i-0];

		for (uint p=0; p < 3; p++) {
			for (uint l=0; l < 5; l++) {
				ema[p*5 + l] = prixs[DEPART+i-l*periode[]]*k[m] + ema[p*5 + l]*(1 - k[m]); 
			}
		};
	};
	//
	float * _prixs = malloc(sizeof(float) * PRIXS_VALIDES);
	memcpy(_prixs, prixs + DEPART, sizeof(float) * PRIXS_VALIDES);
	free(prixs);
	prixs = _prixs;
};*/

/*void charger_les_prixs() {
	FILE * fp = fopen("prix/prixs.bin", "rb");
	fread(&PRIXS, sizeof(float), 1, fp);
	prixs = (float*)malloc(sizeof(float) * PRIXS);
	fread(prixs, sizeof(float), PRIXS, fp);
	fclose(fp);
	//
	les_valeurs();
};

void liberer_les_prixs() {
	free(valeurs);
	free(prixs);
}*/