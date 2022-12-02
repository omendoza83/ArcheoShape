//=================================================================================================================
/**
 *  @file       nct_exception_strings.h
 *  @brief      Definition of exception strings.
 *  @details    Definition file of the exception strings used to report errors in the nct namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2019 Omar Mendoza Montoya \n \n
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 *  associated documentation files (the "Software"), to deal in the Software without restriction,  
 *  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,  
 *  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions: \n
 *  The above copyright notice and this permission notice shall be included in all copies or substantial 
 *  portions of the Software. \n
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 *  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=================================================================================================================

#ifndef NCT_EXCEPTION_STRINGS_H_INCLUDE
#define NCT_EXCEPTION_STRINGS_H_INCLUDE

//=================================================================================================================
namespace nct {

// Auxiliar strings for error messages.
inline constexpr const char* exc_log_separator {"\n\n========================================"};
inline constexpr const char* exc_father_exception {"\n****Father exception\n"};
inline constexpr const char* exc_info {"Info: "};
inline constexpr const char* exc_source {"Source: "};
inline constexpr const char* exc_timestamp {"Timestamp: "};
inline constexpr const char* exc_details {"Details: "};
inline constexpr const char* exc_argument {"Argument: "};
inline constexpr const char* exc_arguments {"Arguments: "};
inline constexpr const char* exc_value {"Value: "};
inline constexpr const char* exc_valid_range {"Valid range: "};
inline constexpr const char* exc_valid_value {"Valid value: "};
inline constexpr const char* exc_valid_values {"Valid values: "};
inline constexpr const char* exc_index {"Index: "};
inline constexpr const char* exc_pointer {"Pointer: "};
inline constexpr const char* exc_iterator {"Iterator: "};
inline constexpr const char* exc_range {"Range: "};
inline constexpr const char* exc_file {"File: "};
inline constexpr const char* exc_array {"Array: "};
inline constexpr const char* exc_step {"Step: "};

// Strings for exception classes.
inline constexpr const char* exc_unknown {"Unknown exception."};
inline constexpr const char* exc_memory_exception {"Unable to allocate the necessary memory."};
inline constexpr const char* exc_bad_argument {"The specified argument is not valid or out of range."};
inline constexpr const char* exc_bad_arguments {"One or more arguments are not valid or out of range."};
inline constexpr const char* exc_index_out_of_range {"The specified index is out of range."};
inline constexpr const char* exc_indices_out_of_range {"One or more indices are out of range."};
inline constexpr const char* exc_bad_iterator {"The specified iterator is not valid or out of range."};
inline constexpr const char* exc_null_pointer {"The specified pointer is null and cannot be dereferenced."};
inline constexpr const char* exc_null_iterator {"The specified iterator is null and cannot be dereferenced."};
inline constexpr const char* exc_bad_range {"The specified range is empty or is not valid for this operation."};
inline constexpr const char* exc_initialization_error {"An error occurred during the object initialization."};
inline constexpr const char* exc_bad_class_member {"The class member is not implemented or not valid for "
    "this instance."};
inline constexpr const char* exc_arithmetic_error {"An exceptional arithmetic condition has occurred."};
inline constexpr const char* exc_bad_configuration {"The current object configuration is not valid for the "
    "specified operation."};
inline constexpr const char* exc_io_exception {"An error occurred in an I/O operation."};
inline constexpr const char* exc_operation_error {"The current operation was interrupted because of an error."};
inline constexpr const char* exc_empty_array {"The specified array is empty."};

// Strings for initialization errors.
inline constexpr const char* exc_bad_init_method {"The specified initialization method is not valid."};
inline constexpr const char* exc_error_initializing_with_random_data {"Unable to initialize object using "
    "random data."};
inline constexpr const char* exc_error_initializing_internal_objects {"Unable to initialize internal objects."};

// Strings for configuration errors.
inline constexpr const char* exc_uninitialized_object {"The object has not been initialized or configured "
    "properly for this operation."};
inline constexpr const char* exc_error_configuring_algorithm {"Unable to initialize the parameters of "
    "the algorithm."};

// Strings for arithmetic errors.
inline constexpr const char* exc_div_by_zero {"Division by zero."};
inline constexpr const char* exc_log_of_negative_number {"Logarithm of a negative number."};
inline constexpr const char* exc_negative_denominator {"Negative denominator."};

// Strings for operation errors.
inline constexpr const char* exc_maximum_number_of_iterations_exceeded {"The maximum number of allowed "
    "iterations has been exceeded."};
inline constexpr const char* exc_null_step_size {"The step size cannot be zero for this operation."};
inline constexpr const char* exc_too_small_step_size {"The step size is too small for this operation."};

inline constexpr const char* exc_event_without_observers {"The specified event has not attached "
    "observers."};
inline constexpr const char* exc_process_id_already_included_in_observer {"The specified process is already in"
    "observer."};

inline constexpr const char* exc_error_in_parallel_for {"Unable to complete parallel execution. "};
inline constexpr const char* exc_error_invoking_function {"Unable to invoke the specified function."};
inline constexpr const char* exc_error_invoking_functions {"Unable to invoke one or more of the specified "
    "functions."};
inline constexpr const char* exc_bad_returning_object {"The object returned by the invoked function is not "
    "valid for this operation."};

// Strings for common enumerations.
inline constexpr const char* exc_bad_method {"The specified method is not valid."};
inline constexpr const char* exc_bad_test_type {"The specified test type is not valid."};
inline constexpr const char* exc_bad_result_type {"The specified result type is not valid."};
inline constexpr const char* exc_bad_error_type {"The specified error type is not valid."};
inline constexpr const char* exc_bad_relational_operator {"The specified relational operator is not valid."};

inline constexpr const char* exc_bad_metric {"The specified metric is not valid."};
inline constexpr const char* exc_bad_threshold_type {"The specified threshold operation is not valid."};
inline constexpr const char* exc_bad_distance_function {"The specified distance function is not valid."};
inline constexpr const char* exc_bad_n_connectivity {"The specified type of N-connectivity is not valid."};

inline constexpr const char* exc_bad_scaling_method {"The specified scaling method is not valid."};
inline constexpr const char* exc_bad_scaling_function {"The specified scaling function is not valid."};
inline constexpr const char* exc_bad_normalization_method {"The specified normalization method is not valid."};

inline constexpr const char* exc_bad_optimization_method {"The specified optimization method is not valid."};
inline constexpr const char* exc_bad_step_size_method {"The specified method for step size estimation"
    "is not valid."};

// Strings for numeric casts.
inline constexpr const char* exc_bad_precision_for_safe_cast {"Precision of the floating point "
    "representation of the given value is not enough to cast exactly to the specified integer type."};
inline constexpr const char* exc_value_under_lower_limit_in_safe_cast {"The specified real number is "
    "greater than the minimum possible integer value."};
inline constexpr const char* exc_value_above_upper_limit_in_safe_cast {"The specified real number is "
    "greater than the maximum possible integer value."};

// Strings for bounded variables.
inline constexpr const char* exc_bad_bounds {"The specified values are not valid as upper and lower "
"limits. Make sure that the lower limit is not greater than the upper limit."};
inline constexpr const char* exc_bad_thresholds {"The specified values are not valid as upper and lower "
    "thresholds. Make sure that the lower threshold is not greater than the upper threshold."};
inline constexpr const char* exc_bad_min_max_values {"The minimum value cannot be greater than the "
    "maximum value."};
inline constexpr const char* exc_value_outside_bounds {"The specified value is out of bounds."};
inline constexpr const char* exc_values_outside_bounds {"One or more of the specified values are out "
    "of bounds."};
inline constexpr const char* exc_value_too_large {"The specified value is too large for this operation."};
inline constexpr const char* exc_value_above_maximum_limit {"The specified value is greater than the "
    "upper limit."};
inline constexpr const char* exc_value_below_minimum_limit {"The specified value is less than the "
    "lower limit."};

// Strings for numeric arguments.
inline constexpr const char* exc_values_are_not_positive {"One or more values are not positive numbers."};
inline constexpr const char* exc_two_variables_are_the_same {"Both variables are taking the same value, "
    "but they must be different."};
inline constexpr const char* exc_two_non_positive_values {"Both variables must be positive values."};
inline constexpr const char* exc_two_values_with_different_signs {"Both variables must have the same sign."};

// Strings for containers.
inline constexpr const char* exc_bad_container_size {"The size of the container is not valid for this "
    "operation."};
inline constexpr const char* exc_bad_sizes_of_containers {"The sizes of the containers are not valid for this "
    "operation."};
inline constexpr const char* exc_empty_container {"The specified container is empty or not valid."};

// Strings for IO operations.
inline constexpr const char* exc_bad_input_stream {"The input stream reported an error before being used."};
inline constexpr const char* exc_bad_output_stream {"The output stream reported an error before being used."};

inline constexpr const char* exc_error_opening_file {"Unable to open the specified file."};
inline constexpr const char* exc_error_opening_input_file {"Unable to open the specified input file."};
inline constexpr const char* exc_error_reading_input_file {"Unable to read data from the specified file."};
inline constexpr const char* exc_error_opening_ouput_file {"Unable to open the specified output file."};
inline constexpr const char* exc_error_writing_ouput_file {"Unable to save data in the specified file."};
inline constexpr const char* exc_error_reading_string_line {"Unable to read a line from the input stream."};

inline constexpr const char* exc_error_reading_data {"Unable to read data from input stream."};
inline constexpr const char* exc_error_writing_data {"Unable to write data to output stream."};

inline constexpr const char* exc_error_reading_file_header {"Unable to read file header."};
inline constexpr const char* exc_error_writing_header {"Unable to write file header."};

inline constexpr const char* exc_bad_magic_key {"The opened file does not start with the correct magic key."};
inline constexpr const char* exc_error_reading_magic {"Unable to read magic key."};

inline constexpr const char* exc_bad_file_format {"The file cannot be decoded because the data format is not "
    "recognized."};
inline constexpr const char* exc_not_supported_file {"The format of the opened file is not supported by "
    "the target object."};

inline constexpr const char* exc_bad_file_type {"The specified file type is not valid."};
inline constexpr const char* exc_bad_data_type_in_file {"The data stored in the opened file is "
    "not supported by the target object."};
inline constexpr const char* exc_error_decoding_file {"Unable to parse and decode the specified file."};

// Strings for iterators.
inline constexpr const char* exc_bad_iterator_shift_mode {"The specified shift mode is not valid or "
    "supported by the iterator class of the target container."};
inline constexpr const char* exc_iterators_attached_to_different_objects {"The iterators are not attached to "
    "the same container."};
inline constexpr const char* exc_iterators_attached_to_different_sequence {"The iterators are not attached to "
    "the same sequence."};

// Strings for ranges.
inline constexpr const char* exc_empty_range {"The specified range is empty."};
inline constexpr const char* exc_bad_range_size {"The size of the specified range is not valid for this "
    "operation."};
inline constexpr const char* exc_bad_sizes_of_ranges {"The size of one or more of the specified ranges is not "
    "valid for this operation."};
inline constexpr const char* exc_two_ranges_of_different_sizes {"Both ranges most have the same number of "
    "elements."};
inline constexpr const char* exc_range_with_less_than_two_elements {"The specified range has less than two "
    "elements."};
inline constexpr const char* exc_range_with_less_than_three_elements {"The specified range has less than three "
    "elements."};

// Strings for arrays.
inline constexpr const char* exc_error_copying_array {"Unable to copy array."};

inline constexpr const char* exc_null_first_element {"The first element of the array cannot be null."};
inline constexpr const char* exc_bad_array_elements {"One or more elements of the array are not valid for this "
    "operation."};

inline constexpr const char* exc_bad_array_size {"The size of the array is not valid for this operation."};
inline constexpr const char* exc_bad_array_dimensions {"The sizes of the dimensions of the array are not "
    "valid for this operation."};
inline constexpr const char* exc_bad_number_of_rows {"The number of rows of the array is not valid for this "
    "operation."};
inline constexpr const char* exc_bad_number_of_columns {"The number of columns of the array is not valid for "
    "this operation."};
inline constexpr const char* exc_bad_dimension1 {"Dimension 1 of array is not valid for this operation."};
inline constexpr const char* exc_bad_dimension2 {"Dimension 2 of array is not valid for this operation."};
inline constexpr const char* exc_bad_dimension3 {"Dimension 3 of array is not valid for this operation."};
inline constexpr const char* exc_bad_dimension4 {"Dimension 4 of array is not valid for this operation."};

inline constexpr const char* exc_bad_lengths_of_arrays {"The length of one ore more arrays is not valid "
    "for this operation."};
inline constexpr const char* exc_bad_dimensions_of_arrays {"The sizes of the dimensions of the arrays are not "
    "valid for this operation."};
inline constexpr const char* exc_arrays_of_different_lengths {"The arrays are of different lengths, but they "
    "must have the same number of elements."};
inline constexpr const char* exc_arrays_of_different_dimensions {"The arrays are of different dimensions, but "
    "they must have the same shape."};
inline constexpr const char* exc_arrays_with_different_number_of_colums {"The arrays have different numbers of "
    "columns, but this dimension must be the same for them."};
inline constexpr const char* exc_arrays_with_different_number_of_rows {"The arrays have different numbers of "
    "rows, but this dimension must be the same for them."};

inline constexpr const char* exc_bad_reshape_dimensions {"An array cannot be reshaped if the new dimensions "
    "do not guarantee the same number of elements."};
inline constexpr const char* exc_bad_initializer_list_size {"The size of the initializer list is not valid "
    "for this operation."};
inline constexpr const char* exc_bad_array_of_arrays_subscript {"Unable to get data from the specified "
    "subscript."};
inline constexpr const char* exc_first_element_of_arrays_different {"The first element of the arrays must be "
    "the same."};
inline constexpr const char* exc_bad_hankel_arguments {"The last element of the first column and the first "
    "element of the last row must be the same."};

inline constexpr const char* exc_array_with_less_than_two_elements {"The array must have at least two elements."};
inline constexpr const char* exc_array_with_less_than_three_elements {"The array must have at least three "
    "elements."};

inline constexpr const char* exc_array_with_less_than_two_rows {"The array must have at least two rows."};
inline constexpr const char* exc_array_with_less_than_three_rows {"The array must have at least three rows."};

inline constexpr const char* exc_array_with_less_than_two_columns {"The array must have at least 2 columns."};
inline constexpr const char* exc_array_with_less_than_three_columns {"The array must have at least 3 columns."};

inline constexpr const char* exc_array_with_less_than_two_rows_and_two_columns {"The array must have at least "
    "two rows and two columns."};
inline constexpr const char* exc_array_dimensions_are_lower_than_two {"The sizes of the array dimensions "
    "must be at least two."};

inline constexpr const char* exc_array_too_big {"The sizes of the array dimensions are too big for this "
    "operation."};
inline constexpr const char* exc_array_length_different_than_problem_dimension {"The array must be of the "
    "same length as the dimension of the optimization problem."};

// Strings for IO operations with arrays.
inline constexpr const char* exc_error_reading_array_size {"Unable to read size of array."};
inline constexpr const char* exc_error_writing_array_size {"Unable to write size of array."};

inline constexpr const char* exc_error_reading_number_of_rows {"Unable to read number of rows of array."};
inline constexpr const char* exc_error_writing_number_of_rows {"Unable to write number of rows of array."};

inline constexpr const char* exc_error_reading_number_of_columns {"Unable to read number of columns of array."};
inline constexpr const char* exc_error_writing_number_of_columns {"Unable to write number of columns of array."};

inline constexpr const char* exc_error_reading_dimension1 {"Unable to read dimension 1 of array."};
inline constexpr const char* exc_error_writing_dimension1 {"Unable to write dimension 1 of array."};

inline constexpr const char* exc_error_reading_dimension2 {"Unable to read dimension 2 of array."};
inline constexpr const char* exc_error_writing_dimension2 {"Unable to write dimension 2 of array."};

inline constexpr const char* exc_error_reading_dimension3 {"Unable to read dimension 3 of array."};
inline constexpr const char* exc_error_writing_dimension3 {"Unable to write dimension 3 of array."};

inline constexpr const char* exc_error_reading_dimension4 {"Unable to read dimension 4 of array."};
inline constexpr const char* exc_error_writing_dimension4 {"Unable to write dimension 4 of array."};

inline constexpr const char* exc_error_reading_null_value {"Unable to read null value of spare array."};
inline constexpr const char* exc_error_writing_null_value {"Unable to write null value of spare array."};

// Strings for IO operations with numeric classes.
inline constexpr const char* exc_error_reading_real_component {"Unable to read real component."};
inline constexpr const char* exc_error_writing_real_component {"Unable to write real component."};

inline constexpr const char* exc_error_reading_imaginary_component {"Unable to read imaginary component."};
inline constexpr const char* exc_error_writing_imaginary_component {"Unable to write imaginary component."};

inline constexpr const char* exc_error_reading_first_component {"Unable to read the first component."};
inline constexpr const char* exc_error_writing_first_component {"Unable to write the first component."};

inline constexpr const char* exc_error_reading_second_component {"Unable to read the second component."};
inline constexpr const char* exc_error_writing_second_component {"Unable to write the second component."};

inline constexpr const char* exc_error_reading_third_component {"Unable to read the third component."};
inline constexpr const char* exc_error_writing_third_component {"Unable to read the third component."};

inline constexpr const char* exc_error_reading_fourth_component {"Unable to read the fourth component."};
inline constexpr const char* exc_error_writing_fourth_component {"Unable to write the fourth component."};

// Strings for linear algebra methods.
inline constexpr const char* exc_singular_system_matrix {"The system matrix is a singular."};
inline constexpr const char* exc_multiple_solution_system {"The linear system has multiple solutions."};
inline constexpr const char* exc_singular_matrix {"The array is a singular matrix."};
inline constexpr const char* exc_non_square_matrix {"The array is not a square matrix."};
inline constexpr const char* exc_non_symmetric_matrix {"The array is not a symmetric matrix."};
inline constexpr const char* exc_non_pos_def_matrix {"The array is not a positive definite matrix."};
inline constexpr const char* exc_non_upper_triangular_matrix {"The array is not an upper triangular matrix."};
inline constexpr const char* exc_non_lower_triangular_matrix {"The array is not a lower triangular matrix."};
inline constexpr const char* exc_non_diagonal_matrix {"The array is not a diagonal matrix."};
inline constexpr const char* exc_non_tridiagonal_matrix {"The array is not a tri-diagonal matrix."};
inline constexpr const char* exc_non_hermitian_matrix {"The array is not a Hermitian matrix."};

inline constexpr const char* exc_error_computing_matrix_factorization {"Unable to find a valid matrix "
    "factorization for the given array."};
inline constexpr const char* exc_error_computing_eigenvalues {"Unable to calculate eigenvalues of the "
    "specified matrix."};
inline constexpr const char* exc_null_diagonal_element {"There is a null element on the main diagonal of "
    "the matrix."};

inline constexpr const char* exc_bad_pivot {"The specified pivot vector is not valid."};
inline constexpr const char* exc_bad_linear_system {"The specified linear system is not valid and cannot be "
    "solved."};
inline constexpr const char* exc_bad_condition_number {"The condition number of a matrix is too big."};
inline constexpr const char* exc_error_solving_linear_system {"Unable to solve linear system."};
inline constexpr const char* exc_error_computing_inverse {"Unable to find inverse of a matrix."};

// Strings for math functions and transformations.
inline constexpr const char* exc_bad_binomial_coefficient {"k must be lower than or equal to n."};
inline constexpr const char* exc_bad_halton_arguments {"The variable index cannot be greater than 100."};
inline constexpr const char* exc_bad_legendre_arguments {"The degree of the polynomial cannot be greater than "
    "the order of the polynomial."};

inline constexpr const char* exc_error_evaluating_bessy_series {"Bessy series failed to converge."};
inline constexpr const char* exc_error_evaluating_bessk_series {"Bessk series failed to converge."};

inline constexpr const char* exc_bad_integration_limits {"The specified integration limits are not valid."};
inline constexpr const char* exc_error_computing_integration_weights {"Unable to get integration weights."};

inline constexpr const char* exc_non_coprimes_numbers {"The given numbers are not co-primes."};
inline constexpr const char* exc_non_prime_number {"The specified number is not a prime."};
inline constexpr const char* exc_error_finding_primitive_root {"Unable to find primitive root."};

inline constexpr const char* exc_bad_rotation_axis {"Rotation axis can't be a null vector."};

// Strings for probability and density functions.
inline constexpr const char* exc_bad_covariance_matrix {"The matrix is not square and symmetric, "
    "or its dimensions are not valid according to the other parameters of the distribution."};

inline constexpr const char* exc_pro_sum_greater_than_one {"Sum of probabilities cannot be greater than 1."};
inline constexpr const char* exc_values_are_not_probabilities {"One or more elements are not probability "
    "values."};

inline constexpr const char* exc_undefined_mean {"Undefined mean for this density function."};
inline constexpr const char* exc_undefined_mode {"Undefined mode for this density function."};
inline constexpr const char* exc_undefined_variance {"Undefined variance for this density function."};
inline constexpr const char* exc_undefined_skewness {"Undefined skewness for this density function."};
inline constexpr const char* exc_undefined_kurtosis {"Undefined kurtosis for this density function."};
inline constexpr const char* exc_undefined_mean_direction {"Undefined mean direction for this density "
    "function."};

inline constexpr const char* exc_infinite_circular_dispersion {"Infinite circular dispersion."};

inline constexpr const char* exc_undefined_mean_for_configuration {"The mean of the distribution is undefined "
    "for the current object configuration and cannot be calculated."};
inline constexpr const char* exc_undefined_mode_for_configuration {"The mode of the distribution is undefined "
    "for the current object configuration and cannot be calculated."};
inline constexpr const char* exc_undefined_variance_for_configuration {"The variance of the distribution "
    "is undefined for the current object configuration and cannot be calculated."};
inline constexpr const char* exc_undefined_skewness_for_configuration {"The skewness of the distribution "
    "is undefined for the current object configuration and cannot be calculated."};
inline constexpr const char* exc_undefined_kurtosis_for_configuration {"The kurtosis of the distribution "
    "is undefined for the current object configuration and cannot be calculated."};

inline constexpr const char* exc_bad_distribution_bounds {"The given values cannot be used as the upper and "
    "lower bounds of the distribution. Make shure that the lower limit is not greater than the upper limit."};
inline constexpr const char* exc_bad_distribution_parameters {"The given values cannot be used to define "
    "a valid distribution."};

inline constexpr const char* exc_bad_ks_function {"The specified function to be estimated is not valid "
    "for this operation."};
inline constexpr const char* exc_bad_ks_method {"The specified estimation method is not valid for "
    "this operation."};
inline constexpr const char* exc_bad_ks_weights {"One or more weights are not valid or are out of range."};
inline constexpr const char* exc_bad_ks_bounding_method {"The specified estimation method is not valid "
    "for this operation."};

// Strings for errors in statistical methods and modeling.
inline constexpr const char* exc_univariate_kernel {"This kernel is not valid for multivariate data."};

inline constexpr const char* exc_error_computing_inverse_of_cov_matrix {"Unable to compute inverse of "
    "covariance matrix."};

inline constexpr const char* exc_not_enough_observations {"The number of observations are not enough for "
    "this operation."};
inline constexpr const char* exc_too_many_observations {"Too many observations for this operation."};

inline constexpr const char* exc_data_with_less_than_one_observation {"The data must contain at least one "
    "observation."};
inline constexpr const char* exc_data_with_less_than_two_observations {"The data must contain at least two "
    "observations."};
inline constexpr const char* exc_data_with_less_than_three_observations {"The data must contain at least "
    "three observations."};

inline constexpr const char* exc_data_with_less_than_one_group {"The data set must contain at least "
    "one group."};
inline constexpr const char* exc_data_with_less_than_two_groups {"The data set must contain at least "
    "two groups."};
inline constexpr const char* exc_data_with_less_than_three_groups {"The data set must contain at least "
    "three groups."};

inline constexpr const char* exc_groups_with_less_than_one_observation {"One or more groups contain less than "
    "one observation."};
inline constexpr const char* exc_groups_with_less_than_two_observations {"One or more groups contain less than "
    "two observation."};
inline constexpr const char* exc_groups_with_less_than_three_observations {"One or more groups contain less "
    "than three observation."};

inline constexpr const char* exc_objects_with_different_number_of_observations {"All data sets must have the "
    "same number of observations."};
inline constexpr const char* exc_objects_with_different_number_of_variables {"All observations must have the "
    "same number of variables."};

inline constexpr const char* exc_bad_permutation_array {"The array of the permutations must have the same "
    "number of columns as observations to be resampled."};
inline constexpr const char* exc_bad_null_statistic_array {"The array with the null statistic must have the "
    "same number of columns as variables to be tested."};
inline constexpr const char* exc_bad_kfwer_parameter {"The k parameter must be a number between 1 and the "
    "number of tests."};

inline constexpr const char* exc_values_are_not_pvalues {"One or more elements are not p-values."};
inline constexpr const char* exc_bad_pval_type {"The specified p-value type is not valid."};

inline constexpr const char* exc_number_of_observations_different_than_mean_vector_length {"The number of "
    "observations must be the same as the length of the mean vector."};
inline constexpr const char* exc_array_length_different_than_number_of_observations {"The length of the "
    "specified array is different than the number of observations."};

inline constexpr const char* exc_bad_array_for_paired_data {"Paired data are defined by arrays with two "
    "columns."};

inline constexpr const char* exc_bad_test_object {"The test object is not properly configured for this "
    "operation."};
inline constexpr const char* exc_bad_resampling_method {"The specified resampling method is "
    "not valid."};
inline constexpr const char* exc_bad_pca_method {"The specified PCA method is not valid."};

inline constexpr const char* exc_bad_sign_test {"The number of computed signs is not valid."};
inline constexpr const char* exc_bad_fisher_test {"No successes were found by the test algorithm."};

inline constexpr const char* exc_error_performing_resampling {"Unable to perform resampling operation."};
inline constexpr const char* exc_error_calculating_statistic {"Unable to calculate statistic of data."};

inline constexpr const char* exc_error_at_mls_algorithm {"Unable to apply MLS algorithm on the specified data."};
inline constexpr const char* exc_error_testing_mls_algorithm {"Unable to test results of MLS algorithm."};
inline constexpr const char* exc_error_finding_optimal_mls_parameters {"Unable to estimate optimal thresholds "
    "of the MLS algorithm."};
inline constexpr const char* exc_error_computing_mls_difference_matrix {"Unable to compute difference "
    "matrix."};
inline constexpr const char* exc_error_computing_mls_difference_matrices {"Unable to compute difference "
    "matrices."};

inline constexpr const char* exc_error_at_rht_algorithm {"Unable to apply RHT algorithm on the specified data."};

// Strings for parametric shapes and geometric objects.
inline constexpr const char* exc_two_points_are_equal {"The start and end points are the same."};

inline constexpr const char* exc_bad_circle {"The circle has radix zero or negative."};
inline constexpr const char* exc_bad_line {"The line is not well defined by two different points."};
inline constexpr const char* exc_bad_ellipse {"The ellipse is not well defined by two positive radices."};
inline constexpr const char* exc_bad_polygon {"The polygon has less than two vertices."};
inline constexpr const char* exc_non_convex_polygon {"The polygon is not convex."};

inline constexpr const char* exc_bad_arc_parameters {"Unable to build arc with the given start and end points."};
inline constexpr const char* exc_error_building_arc {"Unable to build arc."};

inline constexpr const char* exc_complex_circle_center {"The calculated circle center is complex."};

inline constexpr const char* exc_error_computing_area_of_base {"Unable to calculate the area of the base."};
inline constexpr const char* exc_error_computing_perimeter_and_area_of_base {"Unable to calculate the "
    "perimeter and area of the base."};

inline constexpr const char* exc_bad_grid_limits {"The given bounds of the grid are not valid."};
inline constexpr const char* exc_point_out_of_bounds {"Point out of bounds."};

// Strings for root finding methods.
inline constexpr const char* exc_error_finding_root {"The method failed to find a root within the "
    "specified accuracy."};
inline constexpr const char* exc_non_bracked_root {"It is not possible to find a bracked solution "
    "for the specified function using the initial range."};

inline constexpr const char* exc_polynomial_of_degree_zero {"The degree of the polynomial is zero."};
inline constexpr const char* exc_complex_roots {"One or more roots are complex."};
inline constexpr const char* exc_complex_polynomial {"The specified polynomial has complex coefficients."};

inline constexpr const char* exc_negative_discriminant {"The discriminant of the polynomial function is "
    "negative."};
inline constexpr const char* exc_null_quadratic_term {"Quadratic term can't be zero."};
inline constexpr const char* exc_null_cubic_term {"Cubic term can't be zero."};
inline constexpr const char* exc_null_quartic_term {"Quartic term can't be zero."};

inline constexpr const char* exc_null_derivative {"One calculated derivative during the execution of the "
    "root finding algorithm is zero."};

// Strings for optimization methods.
inline constexpr const char* exc_error_in_optimization_method {"Unable to find an optimal solution to the "
    "specified problem."};
inline constexpr const char* exc_bad_wolfe_conditions {"Bad Wolfe conditions. C1 cannot be greater than or "
    "equal to C2."};

inline constexpr const char* exc_non_bracked_optimum {"It is not possible to find a bracked solution for "
    "the specified function using the initial range."};

inline constexpr const char* exc_bad_chromosome_length {"The length of the chromosomes is not valid for "
    "this operation."};
inline constexpr const char* exc_chromosome_variable_too_big {"The length of the variables represented by the "
    "chromosomes is bigger than the number of bits of the requested data type."};
inline constexpr const char* exc_different_types_of_chromosomes {"The chromosomes are not of the same type."};

inline constexpr const char* exc_bad_constraint_function {"The constraint function returns and array of a size "
    "different than the number of constraints."};
inline constexpr const char* exc_bad_gradient_function {"The gradient function returns and array of a size "
    "different than the number of variables."};
inline constexpr const char* exc_bad_hessian_function {"The hessian function returns and array of dimensions "
    "different than the number of variables X the number of variables."};
inline constexpr const char* exc_bad_jacobian_function {"The jacobian function returns and array of dimensions "
    "different than the number of constraints X the number variables."};

// Strings for regression methods.
inline constexpr const char* exc_bad_regression_model {"The regression model is not valid for the "
    "specified operation."};
inline constexpr const char* exc_bad_regression_model_for_input_data {"The current regression model is not "
    "valid for the specified input data."};
inline constexpr const char* exc_non_univariate_regression_model {"The current regression model is not for "
    "univariate data."};
inline constexpr const char* exc_error_computing_regression_model {"Unable to find a regression model for "
    "the specified data."};
inline constexpr const char* exc_regression_model_for_univariate_data {"This regression model is only "
    "for univariate data."};

// Strings for classification methods.
inline constexpr const char* exc_bad_classification_model {"The classification model is not valid for "
    "the specified operation."};
inline constexpr const char* exc_non_univariate_classifier {"The current classification model is not "
    "for univariate data."};
inline constexpr const char* exc_less_than_two_classes {"The data must have observations for at least two "
    "classes."};
inline constexpr const char* exc_error_selecting_features {"Unable to select features."};
inline constexpr const char* exc_error_evaluating_weak_classifier {"Unable to evaluate weak classifier."};

// Strings for clustering methods.
inline constexpr const char* exc_clustering_error {"Unable to find clusters for the specified observations."};
inline constexpr const char* exc_empty_cluster {"One or more clusters are empty."};
inline constexpr const char* exc_number_of_clusters_less_than_observations {"The specified number of cluster "
    "is greater than the number of observations."};
inline constexpr const char* exc_bad_eigenvalues_of_laplacian {"Unable to compute eigenvalues of Laplacian "
    "matrix."};

// Strings for interpolation methods.
inline constexpr const char* exc_bad_interpolation_model {"The classification model is not valid for "
    "the specified operation"};
inline constexpr const char* exc_bad_initialization_points {"The given points cannot be used to build the "
    "interpolation object."};
inline constexpr const char* exc_bad_point_for_evaluation {"The given point cannot be evaluated using the "
    "interpolation object."};
inline constexpr const char* exc_error_updating_interpolation_model {"Unable to update interpolation model."};

// Strings for digital filters.
inline constexpr const char* exc_null_filter_numerator_degree {"The degree of the numerator is zero."};
inline constexpr const char* exc_null_filter_denominator_degree {"The degree of the denominator is zero."};
inline constexpr const char* exc_filter_order_too_large {"The order of specified filter is too large."};
inline constexpr const char* exc_numerator_order_greater_than_denominator_order {"The order of the numerator "
    "is greater than the order of the denominator."};

inline constexpr const char* exc_bad_window_length {"The length of the window object is not "
    "valid for this operation."};

inline constexpr const char* exc_complex_filter_coefficient {"The specified filter has "
    "one complex coefficient."};
inline constexpr const char* exc_complex_filter_gain {"The gain of the filter is complex."};

inline constexpr const char* exc_bad_filter_length {"The length of the filter is not valid "
    "for this operation."};
inline constexpr const char* exc_bad_filter_bandwidth {"The specified filter bandwidth is not valid."};
inline constexpr const char* exc_bad_filter_origin {"The filter origin must be a number between 0 "
    "and length-1."};

inline constexpr const char* exc_bad_length_of_savitzky_golay_filter {"The length of the filter must be "
    "greater than the degree of the polynomial."};
inline constexpr const char* exc_bad_derivative_of_savitzky_golay_filter {"The order of the derivative "
    "must be lower than the degree of the polynomial."};

inline constexpr const char* exc_not_odd_symetric_fir_filter_length {"Odd order symmetric FIR filters "
    "must have a gain of zero at the Nyquist frequency. The length of the filter must be odd."};

inline constexpr const char* exc_bad_frequency {"The specified frequency is greater "
    "than the Nyquist frequency or is negative."};
inline constexpr const char* exc_bad_central_frequency {"The central frequency is greater "
    "than the Nyquist frequency or is negative."};
inline constexpr const char* exc_bad_cutoff_frequency {"The cutoff frequency is greater "
    "than the Nyquist frequency or is negative."};
inline constexpr const char* exc_bad_tunning_frequency {"The specified tunning frequency is "
    "greater than the Nyquist frequency or is negative."};
inline constexpr const char* exc_bad_band_pass_and_band_stop_frequencies {"The bandpass frequency must be "
    "lower than the stop frequency."};
inline constexpr const char* exc_bad_frequencies {"One or more of the specified frequency are greater "
    "than the Nyquist frequency or are negative."};
inline constexpr const char* exc_bad_widths_of_filters {"One or more filter widths are null or negative "
    "numbers."};
inline constexpr const char* exc_bandwidths_of_filters {"One or more bandwidths are null or negative "
"numbers."};

inline constexpr const char* exc_bad_filter_rise_time_range {"The specified rise time range is not valid."};
inline constexpr const char* exc_bad_filter_constant_time_range {"The specified constant time range "
    "is not valid."};
inline constexpr const char* exc_bad_filter_fall_time_range {"The specified fall time range is not valid."};

inline constexpr const char* exc_bad_filter_rise_frequency_range {"The specified rise frequency range "
    "is not valid."};
inline constexpr const char* exc_bad_filter_constant_frequency_range {"The specified constant frequency range "
    "is not valid."};
inline constexpr const char* exc_bad_filter_fall_frequency_range {"The specified fall frequency range "
    "is not valid."};

inline constexpr const char* exc_error_calculating_state_space_representation {"Unable to calculate discrete "
    "state-space representation."};
inline constexpr const char* exc_error_filtering_data {"Unable to filter input data."};
inline constexpr const char* exc_error_building_filter_bank {"Unable to build filter bank."};

// Strings for signal processing.
inline constexpr const char* exc_bad_fft_direction {"The specified FFT direction is not valid."};
inline constexpr const char* exc_bad_spectrum_type {"The specified spectrum type is not valid."};

inline constexpr const char* exc_signal_length_is_not_prime {"The length of the signal is not a prime number."};
inline constexpr const char* exc_signal_length_is_not_a_power_of_two {"The length of the signal is not "
    "a power of two."};
inline constexpr const char* exc_signal_length_is_not_equal_to_window_length {"The lengths of the signal "
    "and the window function are not he same."};

inline constexpr const char* exc_bad_convolution_size_in_bluestein {"Convolution size too large in "
    "Bluestein's algorithm."};
inline constexpr const char* exc_bad_convolution_size_in_rader {"Convolution size too large in "
    "Rader's algorithm."};

inline constexpr const char* exc_bad_window_size_for_psd {"The window length is greater than the length of the "
    "input array."};
inline constexpr const char* exc_bad_window_size_and_padding_size {"The window length cannot be greater "
    "than the number of points for zero-padding."};
inline constexpr const char* exc_bad_subwindows_for_psd {"The number of subwindows cannot be zero."};
inline constexpr const char* exc_bad_overlapping_psd {"The overlapping between consecutive windows is too big."};

inline constexpr const char* exc_bad_lag_variable {"The lag value is not valid for this operation."};
inline constexpr const char* exc_bad_signal_phase_variable {"The phase value is out of the signal bounds."};
inline constexpr const char* exc_bad_convolution_kernel_length {"The length of the convolution kernel is "
    "not valid for this operation."};
inline constexpr const char* exc_bad_linear_detrend_model {"It is not possible to find a valid model for "
    "linear detrending."};
inline constexpr const char* exc_sampling_rate_in_filter_bank {"All the filters in the bank must have the same "
    "sampling rate."};

inline constexpr const char* exc_error_calculating_fft {"Unable to calculate FFT."};
inline constexpr const char* exc_error_calculating_psd {"Unable to calculate power spectrum."};
inline constexpr const char* exc_error_calculating_spectrogram {"Unable to calculate spectrogram."};
inline constexpr const char* exc_error_calculating_convolution {"Unable to compute convolution "
    "between signals."};
inline constexpr const char* exc_error_calculating_deconvolution {"Unable to compute deconvolution "
    "between signals."};
inline constexpr const char* exc_error_calculating_cross_correlation {"Unable to compute cross-correlation "
    "between signals."};
inline constexpr const char* exc_error_calculating_cross_covariance {"Unable to compute cross-covariance "
    "between signals."};
inline constexpr const char* exc_error_calculating_frequency_response {"Unable to compute frequency response "
    "of the specified filter/signal."};
inline constexpr const char* exc_error_calculating_empirical_mode_decomposition {"Unable to compute empirical "
    "mode decomposition of the specified signal."};
inline constexpr const char* exc_error_calculating_hilbert_transform {"Unable to compute Hilbert "
    "transform of the specified signal."};
inline constexpr const char* exc_error_calculating_analitic_function {"Unable to compute analytic "
    "signal of the specified sequence."};
inline constexpr const char* exc_error_calculating_instantaneus_spectrum {"Unable to compute instantaneus "
    "spectrum of the specified signal."};
inline constexpr const char* exc_error_calculating_hilbert_huang_transform {"Unable to compute Hilbert-Huang "
    "transform of the specified signal."};

// Strings for AR and VAR models.
inline constexpr const char* exc_bad_ar_model_order {"The order of the model must be lower than the "
    "number of observations."};
inline constexpr const char* exc_bad_ar_covariance_matrix {"The size of the covariance matrix is not "
    "valid for this model."};
inline constexpr const char* exc_non_univariate_model {"This model is not for univariate data."};

// Strings for color spaces.
inline constexpr const char* exc_bad_color {"The specified color is not valid."};
inline constexpr const char* exc_bad_color_palette {"The specified color palette is not valid."};
inline constexpr const char* exc_bad_color_space {"The specified color space is not valid."};

inline constexpr const char* exc_bad_color_string {"The specified string does not represent a valid color."};
inline constexpr const char* exc_bad_color_string_length {"The length of the color string is not valid."};

inline constexpr const char* exc_less_than_two_pivot_colors {"A color palette only can be built if at least 2 "
    "pivot colors are defined."};
inline constexpr const char* exc_bad_pivot_color_indices {"The indices of the pivot colors are not valid."};

// Strings for mesh files.
inline constexpr const char* exc_bad_ply_file {"The specified file doesn't contain a PLY model."};
inline constexpr const char* exc_bad_face_in_ply_object {"One face is a line or a point."};
inline constexpr const char* exc_missing_elements_in_ply_object {"The current object doesn't have the "
    "elements vertex and/or face."};
inline constexpr const char* exc_missing_properties_in_ply_object {"The current object doesn't have the "
    "properties x, y, z and/or vertexIndex."};

inline constexpr const char* exc_bad_shape_distribution {"The specified shape distribution is not valid."};

// Strings for image files.
inline constexpr const char* exc_bad_image_bit_position {"The bit position of the specified channel is "
    "out of range."};
inline constexpr const char* exc_bad_image_channel_max_value {"The specified maximum value is out of range."};
inline constexpr const char* exc_bad_image_indexed_channel_type {"Indexed channels must be represented by "
    "integer variables."};
inline constexpr const char* exc_image_color_palette_too_big {"The specified color palette is too big."};
inline constexpr const char* exc_image_too_big {"The image dimensions are too big to be allocated in memory."};
inline constexpr const char* exc_error_reading_image_size {"Unable to read image size."};
inline constexpr const char* exc_error_reading_image_properties {"Unable to read image properties."};

inline constexpr const char* exc_non_integer_image_data {"This function only saves images defined by "
    "integer values."};
inline constexpr const char* exc_non_binary_image {"This function only works with binary images."};
inline constexpr const char* exc_non_grayscale_image {"This function only works with grayscale images."};
inline constexpr const char* exc_non_rgb_image {"This function only works with RGB images."};

inline constexpr const char* exc_bad_bitmap_type {"Bad bitmap type. Expected 19778."};
inline constexpr const char* exc_bad_bitmap_information_header {"Bad information header. "
    "Only BITMAPINFOHEADER is supported by this library."};
inline constexpr const char* exc_bad_bitmap_bit_count {"The bit count of the image file is not supported."};
inline constexpr const char* exc_bad_bitmap_file_size {"The size of the bitmap file is not valid."};
inline constexpr const char* exc_bad_bitmap_image_type {"The image type specified in the data object "
    "cannot be exported to a bitmap file."};

inline constexpr const char* exc_error_building_huffman_tree {"Unable to build 2D Huffman tree."};
inline constexpr const char* exc_bad_huffman_tree {"A tree without symbols is not allowed."};
inline constexpr const char* exc_bad_png_number_of_codes {"Imposible to represent all the symbols with "
    "the specified number of bits."};
inline constexpr const char* exc_bad_png_filter_type {"Unknown filter type."};
inline constexpr const char* exc_bad_png_lazy_matching {"Error at lazy matching."};
inline constexpr const char* exc_bad_png_offset {"Bad offset value."};
inline constexpr const char* exc_bad_png_end_code_length {"Bad end code length."};
inline constexpr const char* exc_bad_png_data_chunk {"Bad data chunk."};
inline constexpr const char* exc_bad_png_data_chunk_size {"Data chunk too small."};
inline constexpr const char* exc_bad_png_data_chunk_crc {"Bad chunk CRC."};
inline constexpr const char* exc_bad_png_header_chunk {"Bad header chunk."};
inline constexpr const char* exc_bad_png_header_configuration {"Unknown header configuration."};
inline constexpr const char* exc_bad_png_data_cheacksum_crc {"Bad data checksum."};
inline constexpr const char* exc_bad_png_image_type {"The image type specified in the data object "
    "cannot be exported to a bitmap file."};

inline constexpr const char* exc_zlib_error_fcheck {"zLib error: bad FCHECK value."};
inline constexpr const char* exc_zlib_error_compression_method {"zLib error: The compression method "
    "is not valid. Only sliding window of 32k is supported by the PNG spec."};
inline constexpr const char* exc_zlib_error_preset_dictionary {"zLib error: Additional flags should not "
    "specify a preset dictionary."};
inline constexpr const char* exc_zlib_error_bit_pointer {"zLib error: Bit pointer out of bounds."};
inline constexpr const char* exc_zlib_error_huffman_tree {"zLib error: Bad Huffman tree."};
inline constexpr const char* exc_zlib_error_supported_data_type {"zLib error: Only compressed data with "
    "Huffman trees are supported by this library."};
inline constexpr const char* exc_zlib_error_literal_length_code {"zLib error: Bad last literal length code."};
inline constexpr const char* exc_zlib_error_distance_code {"zLib error: Bad distance code."};
inline constexpr const char* exc_zlib_error_distance_length {"zLib error: Bad distance length."};

inline constexpr const char* exc_bad_pnm_image_type {"The specified pnm file type is not valid."};
inline constexpr const char* exc_bad_pnm_image_header {"The image header is not valid."};

// Strings for SVG files.
inline constexpr const char* exc_bad_svg_adjustment_type {"The specified adjustment type is not valid."};
inline constexpr const char* exc_bad_svg_spread_method {"The specified spread method is not valid."};
inline constexpr const char* exc_bad_svg_units {"The specified units are not valid."};
inline constexpr const char* exc_bad_svg_property {"The specified property is not valid."};

inline constexpr const char* exc_svg_object_without_transformation {"No transformation has been defined in "
    "this object."};
inline constexpr const char* exc_svg_object_without_style {"No style has been defined in this object."};

inline constexpr const char* exc_svg_item_out_of_bounds {"One element is out of bounds."};

// Strings for real-time processing tools
inline constexpr const char* exc_bad_buffer_data_array {"The specified data array is not valid."};
inline constexpr const char* exc_error_opening_output_file {"Unable to open output file."};
inline constexpr const char* exc_error_writing_channel_names {"Unable to write channel names of EEG data."};

}
#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
