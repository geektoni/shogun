/*
* BSD 3-Clause License
*
* Copyright (c) 2017, Shogun-Toolbox e.V. <shogun-team@shogun-toolbox.org>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of the copyright holder nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Written (W) 2017 Giovanni De Toni
*
*/

#include <shogun/evaluation/CrossValidationStorage.h>
#include <shogun/lib/parameter_observers/ParameterObserverCrossValidation.h>

using namespace shogun;

ParameterObserverCrossValidation::ParameterObserverCrossValidation()
{
}

ParameterObserverCrossValidation::~ParameterObserverCrossValidation()
{
	for (auto v : m_fold_observations)
		delete v;
}

void ParameterObserverCrossValidation::on_next(const TimedObservedValue& value)
{
	// Simply store the result into the vector
	if (value.first.get_value().type_info().hash_code() ==
	    typeid(CCrossValidationStorage).hash_code())
	{
		auto v = recall_type<CrossValidationStorage>(value.first.get_value());
		m_fold_observations.push_back((CrossValidationStorage*)v.clone());
	}
	else
	{
		SG_SERROR("Object received is not of type CCrossValidationOutput.");
	}
}

std::vector<CrossValidationStorage*>
ParameterObserverCrossValidation::get_observations()
{
	return m_fold_observations;
}