#ifndef DATABASEITERATOR_H_
#define DATABASEITERATOR_H_

#include <pqxx/result>
#include "DatabaseRow.h"

class DatabaseIterator : public pqxx::result::const_iterator {
public:
	DatabaseIterator();
	DatabaseIterator(const pqxx::result::const_iterator&);

	DatabaseRow operator*();
};

#endif /* DATABASEITERATOR_H_ */
