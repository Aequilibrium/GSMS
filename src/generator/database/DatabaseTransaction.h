#ifndef DATABASETRANSACTION_H_
#define DATABASETRANSACTION_H_

#include <pqxx/transaction>
#include "DatabaseField.h"

#include <boost/shared_ptr.hpp>

class Database;
class DatabaseQuery;

#include "config/Exception.h"

class DatabaseTransaction {
private:
	pqxx::work	*m_transaction;

	friend class DatabaseQuery;
public:
	DatabaseTransaction();
	DatabaseTransaction(Database *database);
	virtual ~DatabaseTransaction();

	DatabaseTransaction &operator=(DatabaseTransaction &);
	DatabaseQuery query(const std::string &query) throw (util::DatabaseException);
	void commit();
	void rollback();

	std::string unescape_byte(DatabaseField &field);
};

typedef boost::shared_ptr<DatabaseTransaction>	DatabaseTransactionPtr;

#endif /* DATABASETRANSACTION_H_ */
