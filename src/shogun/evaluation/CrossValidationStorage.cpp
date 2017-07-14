/*
* Written (W) 2017 uriel
*/

#include <shogun/labels/Labels.h>
#include <shogun/evaluation/CrossValidationStorage.h>

using namespace shogun;

CrossValidationStorage::CrossValidationStorage() : CCrossValidationOutput()
{
}

CrossValidationStorage::~CrossValidationStorage()
{
	delete m_test_result;
	delete m_test_true_result;
}

void CrossValidationStorage::update_evaluation_result(
    float64_t result, const char* prefix)
{
	m_evaluation_result = result;
}

void CrossValidationStorage::update_train_indices(
    SGVector<index_t> indices, const char* prefix)
{
	m_train_indices = indices;
}

void CrossValidationStorage::update_test_indices(
    SGVector<index_t> indices, const char* prefix)
{
	m_test_indices = indices;
}

void CrossValidationStorage::update_test_result(
    CLabels* results, const char* prefix)
{
	m_test_result = (CLabels*)results->clone();
}

void CrossValidationStorage::update_test_true_result(
    CLabels* results, const char* prefix)
{
	m_test_true_result = (CLabels*)results->clone();
}

const SGVector<index_t>& CrossValidationStorage::get_train_indices() const
{
	return m_train_indices;
}

const SGVector<index_t>& CrossValidationStorage::get_test_indices() const
{
	return m_test_indices;
}

CLabels* CrossValidationStorage::get_test_result() const
{
	return m_test_result;
}

CLabels* CrossValidationStorage::get_test_true_result() const
{
	return m_test_true_result;
}

float64_t CrossValidationStorage::get_evaluation_result() const
{
	return m_evaluation_result;
}
