#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    return safeCall( userId, [ this, &returnValues ]( const std::unique_ptr<IDataSelector>& selector )
    {
        auto bindFn = std::bind( &IDataSelector::getDataType1, std::placeholders::_1, std::placeholders::_2, 0u );
        return invokeDataRequest( bindFn, selector, returnValues );
    });
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    return safeCall( userId, [ this, &returnValues ]( const std::unique_ptr<IDataSelector>& selector )
    {
        auto memFn = std::mem_fn( &IDataSelector::getDataType2 );
        return invokeDataRequest( memFn, selector, returnValues );
    });
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    return safeCall( userId, [ this, &returnValues ]( const std::unique_ptr<IDataSelector>& selector )
    {
        auto memFn = std::mem_fn( &IDataSelector::getDataType3 );
        std::deque<size_t> unprocessedResults {};
        bool success = invokeDataRequest( memFn, selector, unprocessedResults );
        returnValues = process(unprocessedResults);
        return success;
    });
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
