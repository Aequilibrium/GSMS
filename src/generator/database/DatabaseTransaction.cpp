/***************************************************************************
 *   Copyright (C) 2009 by P.Voylov                                        *
 *   pvoilov@aidoss.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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

DatabaseTransaction a;
DatabaseTransaction b;
a = b

DatabaseTransaction& DatabaseTransaction::operator=(DatabaseTransaction &rhs) {
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
