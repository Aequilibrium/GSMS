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

#ifndef DATABASEQUERY_H_
#define DATABASEQUERY_H_

#include <vector>
#include <pqxx/transaction>

#include "DatabaseTransaction.h"
#include "DatabaseResult.h"

#include "config/Exception.h"


class DatabaseQuery {
private:
	DatabaseTransaction*		m_transaction;

	std::string			m_operator;
	std::string			m_query;
	std::string			m_executed_query;
	std::vector<std::string>	m_arg;
	std::vector<bool>		m_quotes;
	std::vector<bool>		m_null;

	void prepare();

	friend class DatabaseTransaction;

public:
	/**
	 * Query constructor
	 *
	 * @param[in] Database *db
	 * @param[in] const std::string query
	 * @return DatabaseQuery
	 */
	DatabaseQuery();
	DatabaseQuery(DatabaseTransaction *transaction, const std::string &query);

	~DatabaseQuery();

	DatabaseQuery& operator=(const DatabaseQuery &);

	DatabaseQuery& operator()();

	template<typename T> DatabaseQuery& num(const T &v)
	{
		m_arg.push_back(pqxx::to_string(v));
		m_null.push_back(false);
		m_quotes.push_back(false);
		return *this;
	}

	template<typename T> DatabaseQuery& str(const T &v)
	{
		m_arg.push_back(m_transaction->m_transaction->esc(pqxx::to_string(v)));
		m_null.push_back(false);
		m_quotes.push_back(true);
		return *this;
	}

	DatabaseQuery& raw(const std::string &v);

	size_t exec();
	size_t exec(DatabaseResult &res) throw (util::DatabaseException);

	std::string query();
};


#endif /* DATABASEQUERY_H_ */
