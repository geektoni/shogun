/*
* Written (W) 2017 uriel
*/

#ifndef SHOGUN_CROSSVALIDATIONSTORAGE_H
#define SHOGUN_CROSSVALIDATIONSTORAGE_H

#include <shogun/evaluation/CrossValidationOutput.h>

namespace shogun
{
	class CrossValidationStorage : public CCrossValidationOutput
	{

	public:
		CrossValidationStorage();
		~CrossValidationStorage();

		/** update train indices
		 *
		 * @param indices indices used for training
		 * @param prefix prefix for output
		 */
		virtual void update_train_indices(
		    SGVector<index_t> indices, const char* prefix = "");

		/** update test indices
		 *
		 * @param indices indices used for testing/validation
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_indices(SGVector<index_t> indices, const char* prefix = "");

		/** update trained machine
		 *
		 * @param machine trained machine instance
		 * @param prefix prefix for output
		 */
		virtual void
		update_trained_machine(CMachine* machine, const char* prefix = ""){};

		/** update test result
		 *
		 * @param results result labels for test/validation run
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_result(CLabels* results, const char* prefix = "");

		/** update test true result
		 *
		 * @param results ground truth labels for test/validation run
		 * @param prefix prefix for output
		 */
		virtual void
		update_test_true_result(CLabels* results, const char* prefix = "");

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
		update_evaluation_result(float64_t result, const char* prefix = "");

		const SGVector<index_t>& get_train_indices() const;

		const SGVector<index_t>& get_test_indices() const;

		CLabels* get_test_result() const;

		CLabels* get_test_true_result() const;

		float64_t get_evaluation_result() const;

		bool operator==(const CrossValidationStorage &rhs) const {
			return true;
		}

		virtual const char* get_name() const
		{
			return "CrossValidationStorage";
		}

	private:
		SGVector<index_t> m_train_indices;
		SGVector<index_t> m_test_indices;
		CLabels* m_test_result;
		CLabels* m_test_true_result;
		float64_t m_evaluation_result;
	};
}

#endif // SHOGUN_CROSSVALIDATIONSTORAGE_H
