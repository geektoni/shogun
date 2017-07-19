/*
* Written (W) 2017 uriel
*/

#ifndef SHOGUN_CROSSVALIDATIONOBSERVEDVALUE_H
#define SHOGUN_CROSSVALIDATIONOBSERVEDVALUE_H

#include <shogun/lib/parameter_observers/ObservedValue.h>
#include <shogun/labels/Labels.h>
#include <shogun/machine/Machine.h>

namespace shogun
{
	class CrossValidationObservedValue : public ObservedValue
	{

	public:
		CrossValidationObservedValue();
		~CrossValidationObservedValue();

		int64_t get_num_runs() const;

		void set_num_runs(int64_t m_num_runs);

		int64_t get_num_folds() const;

		void set_num_folds(int64_t m_num_folds);

		const CLabels * get_expose_labels() const;

		void set_expose_labels(CLabels * m_expose_labels);

		float64_t get_fold_index() const;

		void update_fold_index(float64_t m_fold_index);

		/** update train indices
		 *
		 * @param indices indices used for training
		 * @param prefix prefix for output
		 */
		virtual void update_train_indices(
		    SGVector<index_t> indices);

		/** update test indices
		 *
		 * @param indices indices used for testing/validation
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_indices(SGVector<index_t> indices);

		/** update trained machine
		 *
		 * @param machine trained machine instance
		 * @param prefix prefix for output
		 */
		virtual void
		update_trained_machine(CMachine* machine){};

		/** update test result
		 *
		 * @param results result labels for test/validation run
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_result(CLabels * results);

		/** update test true result
		 *
		 * @param results ground truth labels for test/validation run
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_true_result(CLabels * results);

		/** post update test and true results
		 */
		virtual void post_update_results()
		{
		}

		/** update evaluate result
		 *
		 * @param result evaluation result
		 * @param prefix prefix for output
		 */
		virtual void
		update_evaluation_result(float64_t result);

		const SGVector<index_t>& get_train_indices() const;

		const SGVector<index_t>& get_test_indices() const;

		CLabels * get_test_result() const;

		CLabels * get_test_true_result() const;

		float64_t get_evaluation_result() const;

		int64_t get_run_index() const;

		void set_run_index(int64_t run_index);

		bool operator==(const CrossValidationObservedValue &rhs) const;

	private:
		SGVector<index_t> m_train_indices;
		SGVector<index_t> m_test_indices;
		CLabels * m_test_result;
		CLabels * m_test_true_result;
		float64_t m_fold_index;
		float64_t m_evaluation_result;
		int64_t m_num_runs;
		int64_t m_num_folds;
		int64_t m_run_index;
		CLabels * m_expose_labels;

	};
}

#endif // SHOGUN_CROSSVALIDATIONOBSERVEDVALUE_H
