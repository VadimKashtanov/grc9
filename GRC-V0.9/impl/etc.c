#include "etc.h"

void FREE(uint len, ...) {
	va_list valist;
	va_start(valist, len);
	for (uint i=0; i < len; i++)
		free(va_arg(valist, void*));
	va_end(valist);
};

float rnd() {return (float)(rand()%100)/99;};

float gauss(float x) {return exp(-x*x);}
float d_gauss(float x) {return -2*x*gauss(x);}
float dd_gauss(float x) {return 4*x*x*gauss(x) - 2*gauss(x);}

float logistique(float x) {return 1 / (1 + exp(-x));}
float d_logistique(float x) {return logistique(x)*(1 - logistique(x));}
float dd_logistique(float x) {return d_logistique(x)*(1+2*logistique(x));}

//inline float tanh(float x) {return exp(-x*x);}
float d_tanh(float x) {return 1 - pow(tanh(x), 2);}
float dd_tanh(float x) {return -2 * tanh(x) * d_tanh(x);}

void gnuplot(float * arr, uint len) {
	char buff[100];
	//
	FILE * fp = fopen("gnuplot_dat.dat", "w");
	//
	for (uint i=0; i < len; i++) {
		if (arr[i] == 123456.0) {
			snprintf(buff, 100, "\n");
			fputs(buff, fp);
		} else {
			snprintf(buff, 100, "%i ", i);
			fputs(buff, fp);
			//
			snprintf(buff, 100, "%f\n", arr[i]);
			fputs(buff, fp);
		}
	}
	fclose(fp);
	//
	//system("gnuplot -p -e \"plot \\\"gnuplot_dat.dat\\\" every :::0::1 with lp, \\\"\\\" every :::2::2 with lp\"");
	system("gnuplot -p -e \"plot 'gnuplot_dat.dat' with lp\"");
	//
	system("rm gnuplot_dat.dat");
};