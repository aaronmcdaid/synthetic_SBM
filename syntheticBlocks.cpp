#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <gsl/gsl_randist.h>
#include "aaron_utils.hpp"
#include "cmdline.h"
using namespace std;
int main(int argc, char ** argv) {
	gengetopt_args_info args_info;
	if (cmdline_parser (argc, argv, &args_info) != 0)
		exit(1) ;
	if(args_info.inputs_num != 0) { // not expecting any non-option arguments
		cmdline_parser_print_help();
		exit(1);
	}
	PP(args_info.N_arg);
	PP(args_info.K_arg);
	PP(args_info.seed_arg);

	const int N = args_info.N_arg;
	const int K = args_info.K_arg;
	const int seed = args_info.seed_arg;
	PP2(N,K);

	srand48(seed);
	const gsl_rng * rng = gsl_rng_alloc (gsl_rng_mt19937);
	PP(gsl_rng_uniform(rng));
	gsl_rng_set(rng, seed);
	PP(gsl_rng_uniform(rng));

	const vector<double> alpha(K, 1.0);
	vector<double> theta(K);
	gsl_ran_dirichlet(rng, K, &alpha.front(), &theta.front());
	double verifyIs1 = 0.0;
	for(int k=0; k<K; k++) {
		verifyIs1 += theta.at(k);
		cout << k
			<< '\t' << theta.at(k)
			<< endl;
	}
	assert(fabs(verifyIs1 - 1.0) < 1e-10);

	vector<int> z(N);
	for(int n=0; n<N; n++) {
		double u = drand48();
		int z_i = 0;
		while(theta.at(z_i) < u) {
			u -= theta.at(z_i);
			++ z_i;
			assert(z_i < K);
		}
		PP(z_i);
		z.at(n)=z_i;
	}
	map< pair<int,int>, double> pi;
	for(int i=0; i<K; i++) {
		for(int j=0; j<K; j++) {
			PP2(i,j);
			const double pi_ij = drand48();
			pi[make_pair(i,j)] = pi_ij;
			PP(pi[make_pair(i,j)]);
		}
	}
	for(int i=0; i<K; i++) {
		for(int j=0; j<K; j++) {
			PP2(i,j);
			double pi_ij = pi[make_pair(i,j)];
			for(int n=0; n<N; n++) {
				if(z.at(n)==i) {
					for(int m=0; m<N; m++) {
						if(z.at(m)==j) {
							const double u = drand48();
							PP2(n,m);
							if(u < pi_ij) {
								cerr << n << '\t' << m << endl;
							}
						}
					}
				}
			}
			cout << endl;
		}
	}
}
