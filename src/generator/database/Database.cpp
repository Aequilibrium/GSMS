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
