#include <math.h>

double MonteCarloMethod::upperConfidenceBound(
    double this_method_winning_percentage,
    int total_method_counts,
    int this_method_study_counts,
    double constant ) {
        return this_method_winning_percentage + ( constant * ( sqrt( log( total_method_counts ) / this_method_study_counts ) ) );
}
