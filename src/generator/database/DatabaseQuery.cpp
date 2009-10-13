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

#include <iostream>

#include <algorithm>
#include <pqxx/prepared_statement>

#include "DatabaseQuery.h"


#include "DatabaseResult.h"
#include "DatabaseTransaction.h"
#include "database_exception.h"

DatabaseQuery::DatabaseQuery() {
	m_transaction = NULL;
}

DatabaseQuery::DatabaseQuery(DatabaseTransaction *transaction,
		const std::string &query) :
	m_query(query) {
	m_transaction = transaction;
	prepare();
}

DatabaseQuery::~DatabaseQuery() {
}

void DatabaseQuery::prepare() {
	m_operator = std::string(m_query);
	size_t pos = m_operator.find_first_not_of(" ");
	if (pos != std::string::npos)
		m_operator.erase(0, int(pos));
	pos = m_operator.find(" ");
	if (pos != std::string::npos)
		m_operator.erase(pos);
	std::transform(m_operator.begin(), m_operator.end(), m_operator.begin(),
			toupper);
}

DatabaseQuery &DatabaseQuery::operator=(const DatabaseQuery &rhs) {
	if (m_transaction != rhs.m_transaction)
		m_transaction = rhs.m_transaction;
	m_query = std::string(rhs.m_query);
	m_arg = rhs.m_arg;
	m_null = rhs.m_null;
	m_quotes = rhs.m_quotes;
	prepare();
	return *this;
}

size_t DatabaseQuery::exec(DatabaseResult &result) throw (util::DatabaseException)
{
	if (m_transaction == NULL)
		throw __DB_EXCEPTION(__ERR_DB_NULL_TRANSACTION);
	size_t rows = 0;
	std::string query = std::string(m_query);
	std::vector<std::string::size_type> pos;
	std::string::size_type p = -1;
	do {
		p = query.find("?", p + 1);
		if (p != std::string::npos)
			pos.push_back(p);
	} while (p != std::string::npos);
	if (pos.size() != m_arg.size()) {
		throw __DB_EXCEPTION(__ERR_DB_ARGUMENT_COUNT);
	}
	while (pos.size() > 0) {
		p = pos.back();
		if (m_null.back() == true) {
			query.replace(p, 1, "NULL");
		} else {
			query.replace(p, 1, m_quotes.back() ? "'" + m_arg.back() + "'"
					: m_arg.back());
		}
		pos.pop_back();
		m_quotes.pop_back();
		m_null.pop_back();
		m_arg.pop_back();
	}

	m_executed_query = query;

	try {
		std::cerr << query << std::endl;
		result = DatabaseResult(m_transaction->m_transaction->exec(query));
		if (m_operator == "SELECT") {
			rows = result.size();
		} else if (m_operator == "UPDATE" || m_operator == "DELETE"
				|| m_operator == "INSERT") {
			rows = result.affected_rows();
		}
		m_arg.clear();
		m_null.clear();
		m_quotes.clear();
		return rows;
	} catch (pqxx::broken_connection &error) {
		throw __DB_EXCEPTION(__ERR_DB_BROKEN_CONN);
	} catch (pqxx::sql_error &error) {
		throw __DB_EXCEPTION(__ERR_DB_SQL_MALFORMED);
	}
	return rows;
}

size_t DatabaseQuery::exec()
{
	DatabaseResult result;
	return exec(result);
}

DatabaseQuery::DatabaseQuery& DatabaseQuery::operator()() {
	m_arg.push_back("");
	m_null.push_back(true);
	m_quotes.push_back(false);
	return *this;
}

DatabaseQuery::DatabaseQuery& DatabaseQuery::raw(const std::string &v) {
	std::ostringstream value;
	value << "E'" << m_transaction->m_transaction->esc_raw(v) << "'";
	m_arg.push_back(value.str());
	m_null.push_back(false);
	m_quotes.push_back(false);
	return *this;
}

std::string DatabaseQuery::query() {
	return m_executed_query;
}
