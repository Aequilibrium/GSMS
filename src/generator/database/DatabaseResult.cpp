#include "DatabaseResult.h"
#include "DatabaseRow.h"

DatabaseResult::DatabaseResult() : pqxx::result()
{
}

DatabaseResult::DatabaseResult(const pqxx::result& result) : pqxx::result(result)
{
}

DatabaseIterator DatabaseResult::begin()
{
	return DatabaseIterator(pqxx::result::begin());
}

DatabaseIterator DatabaseResult::end()
{
	return DatabaseIterator(pqxx::result::end());
}
