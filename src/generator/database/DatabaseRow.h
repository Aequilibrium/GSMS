#ifndef DATABASEROW_H_
#define DATABASEROW_H_

#include <pqxx/result>

#include "typedefs.h"

typedef pqxx::result::tuple DatabaseRow;
//typedef pqxx::result::const_iterator DatabaseIterator;

#endif /* DATABASEROW_H_ */
