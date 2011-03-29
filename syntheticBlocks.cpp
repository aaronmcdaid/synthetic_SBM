#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <gsl/gsl_randist.h>
#include "aaron_utils.hpp"
using namespace std;
int main(int argc, char ** argv) {
	if(argc != 1 + 2) {
		cerr << "Must have 2 args: N K" << endl;
		exit(1);
	}
	const int N = atoi(argv[1]);
	const int K = atoi(argv[2]);

	srand48(0);
	const gsl_rng * rng = gsl_rng_alloc (gsl_rng_taus);

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
