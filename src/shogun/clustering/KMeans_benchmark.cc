/*
* Written (W) 2019 Giovanni De Toni
*/

#include <benchmark/benchmark.h>
#include <shogun/lib/SGMatrix.h>
#include <shogun/mathematics/Math.h>
#include <shogun/features/DenseFeatures.h>
#include <shogun/labels/MulticlassLabels.h>
#include <shogun/distance/EuclideanDistance.h>
#include <shogun/clustering/KMeans.h>

namespace shogun {

	Some<CMulticlassLabels> generate_labels(const int num_features) {
			auto labels= some<CMulticlassLabels>(num_features);
			for (index_t i=0; i<num_features; ++i)
				labels->set_label(i, i%2==0 ? 0 : 1);
			return labels;
	};

	SGMatrix<float64_t> generate_cluster_centers(const int dim_features, const int num_clusters)
	{
		SGMatrix<float64_t> cluster_centers(dim_features, num_clusters);
		SGVector<float64_t>::random_vector(cluster_centers.matrix, dim_features*num_clusters,
										   -10.0, 10.0);
		return cluster_centers;
	}


	SGMatrix<float64_t> generate_data(const SGMatrix<float64_t >& cluster_centers,
									  const int num_clusters,
									  const int num_features,
									  const int dim_features,
									  const int num_vectors_per_cluster,
									  const float64_t cluster_std_dev)
	{
		SGMatrix<float64_t> data(dim_features, num_clusters*num_vectors_per_cluster);
		for (index_t i=0; i<num_clusters; ++i)
		{
			for (index_t j=0; j<dim_features; ++j)
			{
				for (index_t k=0; k<num_vectors_per_cluster; ++k)
				{
					index_t idx=i*dim_features*num_vectors_per_cluster;
					idx+=j;
					idx+=k*dim_features;
					float64_t entry=cluster_centers.matrix[i*dim_features+j];
					data.matrix[idx]=CMath::normal_random(entry, cluster_std_dev);
				}
			}
		}
		return data;
	}

	void execute_kmeans(SGMatrix<float64_t> data, const int num_clusters) {

		init_shogun_with_defaults();

		/* create features */
		auto features = some<CDenseFeatures<float64_t>>(data);

		/* create distance */
		auto distance = some<CEuclideanDistance>(features, features);

		/* create distance machine */
		auto clustering = some<CKMeans>(num_clusters, distance);
		clustering->train(features);

		exit_shogun();

	}

	void KMeans_benchmark(benchmark::State &state) {

		/* Some initialization variables */
		const int num_clusters=4;
		const int num_features=state.range(0);
		const int dim_features=3;
		const int num_vectors_per_cluster=num_features/num_clusters;
		const float64_t cluster_std_dev=2.0;

		/* Generate random centers and random data */
		auto centers = generate_cluster_centers(dim_features, num_clusters);
		auto data = generate_data(centers, num_clusters,
								  num_features, dim_features,
								  num_vectors_per_cluster, cluster_std_dev);
		auto labels = generate_labels(num_features);

		for (auto _ : state) {
			execute_kmeans(data, num_clusters);
		}
	}

	BENCHMARK(KMeans_benchmark)->RangeMultiplier(10)->Range(10, 10<<1000000)
}


