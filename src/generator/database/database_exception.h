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


/*!\file database_exception.h
 * \brief additional exception codes for database programming
 * \author pvoilov@aidoss.com
 */

#define	__ERR_DB_CONNECT		1L
#define	__ERR_DB_NULL_TRANSACTION	10L
#define	__ERR_DB_SQL_MALFORMED		20L
#define	__ERR_DB_BROKEN_CONN		50L
#define	__ERR_DB_ARGUMENT_COUNT		60L
#define	__ERR_DB_HOST_MISSING		100L
#define	__ERR_DB_DATABASE_MISSING	101L
#define	__ERR_DB_USERNAME_MISSING	102L

////

#define	__NTC_DB_LINK_EXISTS		10601L
#define	__NTC_DB_LINK_NOT_FOUND		10602L
#define	__NTC_DB_LINK_NOT_UNIQUE	10603L

#define	__NTC_DB_DATA_EXISTS		10701L
#define	__NTC_DB_DATA_NOT_FOUND		10702L
#define	__NTC_DB_DATA_NOT_UNIQUE	10703L
