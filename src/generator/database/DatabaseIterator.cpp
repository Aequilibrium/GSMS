#include "DatabaseIterator.h"
#include "DatabaseRow.h"

DatabaseIterator::DatabaseIterator() : pqxx::result::const_iterator()
{
}

DatabaseIterator::DatabaseIterator(const pqxx::result::const_iterator& iterator) : pqxx::result::const_iterator(iterator)
{
}

DatabaseRow DatabaseIterator::operator*()
{
	return DatabaseRow(*this);
}
