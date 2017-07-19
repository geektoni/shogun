/*
* Written (W) 2017 uriel
*/

#include <shogun/evaluation/CrossValidationObservedValue.h>

using namespace shogun;

CrossValidationObservedValue::CrossValidationObservedValue() : ObservedValue()
{
	m_type = CROSSVALIDATION;
}

CrossValidationObservedValue::~CrossValidationObservedValue()
{
	SG_UNREF(m_test_result);
	SG_UNREF(m_test_true_result);
	SG_UNREF(m_expose_labels);
}

void CrossValidationObservedValue::update_evaluation_result(
    float64_t result)
{
	m_evaluation_result = result;
}

void CrossValidationObservedValue::update_train_indices(
    SGVector<index_t> indices)
{
	m_train_indices = indices;
}

void CrossValidationObservedValue::update_test_indices(
    SGVector<index_t> indices)
{
	m_test_indices = indices;
}

void CrossValidationObservedValue::update_test_result(
    CLabels * results)
{
	m_test_result = results;
	SG_REF(m_test_result)
}

void CrossValidationObservedValue::update_test_true_result(
    CLabels * results)
{
	m_test_true_result =results;
	SG_REF(m_test_true_result)
}

const SGVector<index_t>& CrossValidationObservedValue::get_train_indices() const
{
	return m_train_indices;
}

const SGVector<index_t>& CrossValidationObservedValue::get_test_indices() const
{
	return m_test_indices;
}

CLabels * CrossValidationObservedValue::get_test_result() const
{
	return m_test_result;
}

CLabels * CrossValidationObservedValue::get_test_true_result() const
{
	return m_test_true_result;
}

float64_t CrossValidationObservedValue::get_evaluation_result() const
{
	return m_evaluation_result;
}

bool CrossValidationObservedValue::operator==(const CrossValidationObservedValue &rhs) const {
	return true;
	/*return m_train_indices.equals(rhs.m_train_indices) &&
		   m_test_indices == rhs.m_test_indices &&
		   m_test_result == rhs.m_test_result &&
		   m_test_true_result == rhs.m_test_true_result &&
		   m_evaluation_result == rhs.m_evaluation_result;
	*/
}

float64_t CrossValidationObservedValue::get_fold_index() const {
	return m_fold_index;
}

void CrossValidationObservedValue::update_fold_index(float64_t fold_index) {
	m_fold_index = fold_index;
}

int64_t CrossValidationObservedValue::get_num_runs() const {
	return m_num_runs;
}

void CrossValidationObservedValue::set_num_runs(int64_t num_runs) {
	m_num_runs = num_runs;
}

int64_t CrossValidationObservedValue::get_num_folds() const {
	return m_num_folds;
}

void CrossValidationObservedValue::set_num_folds(int64_t num_folds) {
	m_num_folds = num_folds;
}

const CLabels *CrossValidationObservedValue::get_expose_labels() const {
	return m_expose_labels;
}

void CrossValidationObservedValue::set_expose_labels(CLabels *expose_labels) {
	m_expose_labels = expose_labels;
	SG_REF(m_expose_labels);
}

void CrossValidationObservedValue::set_run_index(int64_t run_index)
{
	m_run_index = run_index;
}

int64_t CrossValidationObservedValue::get_run_index() const
{
	return m_run_index;
}