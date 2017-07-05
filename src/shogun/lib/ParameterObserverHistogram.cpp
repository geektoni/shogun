/*
* Written (W) 2017 Giovanni De Toni
*/

#include <shogun/io/TBOutputFormat.h>
#include <shogun/lib/ParameterObserverHistogram.h>

using namespace shogun;

ParameterObserverHistogram::ParameterObserverHistogram()
{
    m_writer.init();
    m_parameters = std::vector<std::string>();
}

ParameterObserverHistogram::ParameterObserverHistogram(
    std::vector<std::string>& parameters)
    : ParameterObserverInterface(parameters)
{
    m_writer.init();
}

ParameterObserverHistogram::ParameterObserverHistogram(
    const std::string& filename, std::vector<std::string>& parameters)
    : ParameterObserverInterface(filename, parameters)
{
    m_writer.init();
}

ParameterObserverHistogram::~ParameterObserverHistogram()
{
    m_writer.flush();
	m_writer.close();
}

void ParameterObserverHistogram::on_next(const ObservedValue& value)
{
	auto node_name = std::string("node");
	auto format = TBOutputFormat();
	auto event_value = format.convert_vector(value.first, value.second, node_name);
	m_writer.writeEvent(event_value);
}

void ParameterObserverHistogram::on_error(std::exception_ptr)
{
}

void ParameterObserverHistogram::on_complete()
{
}

bool ParameterObserverHistogram::filter(const std::string& param)
{
    if (m_parameters.size() == 0)
        return true;

	for (auto v : m_parameters)
		if (v == param)
			return true;
	return false;
}
