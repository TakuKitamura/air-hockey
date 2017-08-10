#ifndef _MONTE_CARLO_METHOD_H
#define _MONTE_CARLO_METHOD_H

class MonteCarloMethod {

public:
    double upperConfidenceBound( double this_method_winning_percentage, int total_method_counts, int this_method_study_counts, double constant );

};

#endif
