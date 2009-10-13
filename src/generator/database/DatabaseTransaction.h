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
