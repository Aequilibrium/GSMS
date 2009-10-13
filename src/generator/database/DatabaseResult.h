#ifndef DATABASERESULT_H_
#define DATABASERESULT_H_

#include <pqxx/result>

#include "typedefs.h"
#include "DatabaseIterator.h"

class DatabaseResult : public pqxx::result {
public:
	DatabaseResult();
	DatabaseResult(const pqxx::result&);
	DatabaseIterator begin();
	DatabaseIterator end();
};

#endif /* DATABASERESULT_H_ */
