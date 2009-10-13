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
