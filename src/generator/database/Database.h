#ifndef DATABASE_H_
#define DATABASE_H_

#include <pqxx/connection>
#include <pqxx/transaction>
#include <boost/shared_ptr.hpp>

class DatabaseTransaction;
class DatabaseQuery;

#include "config/Exception.h"

class Database {
private:
	pqxx::connection*	 m_connection;
	pqxx::work*		m_transaction;

	friend class DatabaseTransaction;
	friend class DatabaseQuery;

public:
	Database(const char *hostname = "localhost", const int port = 5432,
			const char *username = "postgres", const char *password = NULL,
			const char *database = "postgres", const char *socket = NULL) throw (util::DatabaseException);

	virtual ~Database();

	DatabaseTransaction transaction();

};

typedef	boost::shared_ptr<Database> DatabasePtr;

#endif /* DATABASE_H_ */
