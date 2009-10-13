#include "DatabaseTransaction.h"
#include "DatabaseQuery.h"
#include "DatabaseField.h"
#include "Database.h"
#include <pqxx/binarystring>

#include "database_exception.h"

DatabaseTransaction::DatabaseTransaction() {
	m_transaction = NULL;
}

DatabaseTransaction::DatabaseTransaction(Database *database) {
	m_transaction = new pqxx::work(*database->m_connection);
}

DatabaseTransaction::~DatabaseTransaction() {
	if(m_transaction != NULL) {
		m_transaction->abort();
		delete m_transaction;
	}
}

DatabaseTransaction &DatabaseTransaction::operator=(DatabaseTransaction &rhs) {
	if(m_transaction != rhs.m_transaction);
		m_transaction = rhs.m_transaction;
		return *this;
}

DatabaseQuery DatabaseTransaction::query(const std::string &query) throw (util::DatabaseException)
{
	if(m_transaction != NULL)
		return DatabaseQuery(this, query);
	else
		throw __DB_EXCEPTION(__ERR_DB_NULL_TRANSACTION);
}

void DatabaseTransaction::commit()
{
	m_transaction->commit();
	delete m_transaction;
	m_transaction = NULL;
}

void DatabaseTransaction::rollback()
{
	m_transaction->abort();
	delete m_transaction;
	m_transaction = NULL;
}


std::string DatabaseTransaction::unescape_byte(DatabaseField &field) {
	pqxx::binarystring converter(field);
	std::ostringstream buf;
	buf.write(converter.c_ptr(), converter.size());
	return buf.str();
}
