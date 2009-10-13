/***************************************************************************
 *   Copyright (C) 2009 by P.Voylov   *
 *   pvoilov@aidoss.com   *
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

/*!\file Exception.h
 * \brief base GSMS exception class
 * \author pvoilov@aidoss.com
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

#include "typedefs.h"

#define __EXCEPTION(x)		util::Exception(__FILE__,__FUNCTION__,__LINE__,x)
#define __DB_EXCEPTION(x)	util::DatabaseException(__FILE__,__FUNCTION__,__LINE__,x)
#define __MATH_EXCEPTION(x)	util::MathException(__FILE__,__FUNCTION__,__LINE__,x)

/*!\namespace util
 *\brief GSMS utilities
 */
namespace util
{

/*!\class	Exception
 * \brief	GSMS exception
 */
class Exception : public std::exception
{
public:

	Exception(unsigned long code = 0L,std::string message = "Exception") : m_message(message),m_code(code),m_line(0L) { m_level = EL_Error;}
	Exception(std::string file, std::string func,unsigned long line,unsigned long code = 0L,std::string message = "Exception") : m_message(message),m_code(code),m_file(file),m_func(func),m_line(line) {}
	~Exception()	throw() {do_log();}
	const char*	what() const throw() {return m_message.c_str();}
	unsigned long	get_code()	{return m_code;}

protected:
	std::string	m_message;
	unsigned long	m_code;
	ErrorLevel	m_level;

	std::string	m_file;
	std::string	m_func;
	unsigned long	m_line;

	void do_log ( );
};

class DatabaseException : public Exception
{
public:
	DatabaseException(std::string message = "DatabaseException", unsigned int code = 0L) : Exception(code,message) {}
	DatabaseException(std::string file, std::string func,unsigned long line,unsigned long code = 0L, std::string message = "DatabaseException") : Exception(file,func,line,code,message) {}
};

class MathException : public Exception
{
public:
	MathException(std::string message = "MathException", unsigned int code = 0L) : Exception(code,message) {}
	MathException(std::string file, std::string func,unsigned long line,unsigned long code = 0L, std::string message = "MathException") : Exception(file,func,line,code,message) {}
};

} /*namespace util*/

#endif /* EXCEPTION_H */
