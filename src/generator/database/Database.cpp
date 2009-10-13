#include <sstream>
#include "Database.h"
#include "DatabaseTransaction.h"
#include <pqxx/binarystring>

#include "database_exception.h"

using namespace util;

Database::Database(const char *hostname, const int port,
		const char *username, const char *password,
		const char *database, const char *socket) throw (DatabaseException)
{


	if(hostname == NULL)
		throw __DB_EXCEPTION(__ERR_DB_HOST_MISSING);
	if(database == NULL)
		throw __DB_EXCEPTION(__ERR_DB_DATABASE_MISSING);
	if(username == NULL)
		throw __DB_EXCEPTION(__ERR_DB_USERNAME_MISSING);

	std::stringstream dbi;
	int nport = port;
	if(nport == 0)
		nport = 5432;
	dbi << "host=" << hostname << " port=";

	if(socket != NULL)
		dbi << socket;
	else
		dbi << nport;

	dbi << " dbname=" << database << " user=" << username;
	if(password != NULL)
		dbi << " password=" << password;

	try {
		
		m_connection = new pqxx::connection(dbi.str());
		if(!m_connection->is_open())
			m_connection->activate();
	} catch(pqxx::broken_connection &error) {
		throw __DB_EXCEPTION(__ERR_DB_BROKEN_CONN);
	}

	m_transaction = NULL;
}

Database::~Database() {

	if(m_connection)
		delete m_connection;
	if(m_transaction)
		delete m_transaction;
}

DatabaseTransaction Database::transaction() {
	return DatabaseTransaction(this);
}
