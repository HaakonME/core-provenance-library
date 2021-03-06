/*
 * cpl-odbc-private.h
 * Core Provenance Library
 *
 * Copyright 2011
 *      The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Contributor(s): Peter Macko
 */

#ifndef __CPL_ODBC_PRIVATE_H__
#define __CPL_ODBC_PRIVATE_H__

#include <backends/cpl-odbc.h>
#include <private/cpl-platform.h>
#include <cplxx.h>

#include <sql.h>
#include <sqlext.h>

#include <string>



/***************************************************************************/
/** ODBC Database Backend                                                 **/
/***************************************************************************/

/**
 * The ODBC database backend
 */
typedef struct {

	/**
	 * The backend interface (must be first)
	 */
	cpl_db_backend_t backend;

	/**
	 * The ODBC environment
	 */
	SQLHENV db_environment;

	/**
	 * The ODBC database connection handle
	 */
	SQLHDBC db_connection;

	/**
	 * The database type
	 */
	int db_type;

	/**
	 * The connection string
	 */
	std::string connection_string;

	/**
	 * Lock for session creation
	 */
	mutex_t create_session_lock;

	/**
	 * The insert statement for session creation
	 */
	SQLHSTMT create_session_insert_stmt;

	/**
	 * Lock for object creation
	 */
	mutex_t create_object_lock;

	/**
	 * The insert statement for object creation
	 */
	SQLHSTMT create_object_insert_stmt;

	/**
	 * The insert statement for object creation - with container
	 */
	SQLHSTMT create_object_insert_container_stmt;

	/**
	 * Insert a new 0th version to the versions table (to be used while
	 * creating a new object)
	 */
	SQLHSTMT create_object_insert_version_stmt;

	/**
	 * The lock for lookup_object
	 */
	mutex_t lookup_object_lock;

	/**
	 * The statement for looking up an object by name (including originator
	 * and type)
	 */
	SQLHSTMT lookup_object_stmt;

	/**
	 * The lock for lookup_object_ext
	 */
	mutex_t lookup_object_ext_lock;

	/**
	 * The statement for looking up an object by name (including originator
	 * and type)
	 */
	SQLHSTMT lookup_object_ext_stmt;

	/**
	 * Lock for version creation
	 */
	mutex_t create_version_lock;

	/**
	 * The insert statement for version creation
	 */
	SQLHSTMT create_version_stmt;

	/**
	 * The lock for get_version
	 */
	mutex_t get_version_lock;

	/**
	 * The statement that determines the version of an object given its ID
	 */
	SQLHSTMT get_version_stmt;

	/**
	 * The lock for add_ancestry_edge
	 */
	mutex_t add_ancestry_edge_lock;

	/**
	 * The statement that adds a new ancestry edge
	 */
	SQLHSTMT add_ancestry_edge_stmt;

	/**
	 * The lock for has_immediate_ancestor
	 */
	mutex_t has_immediate_ancestor_lock;

	/**
	 * The statement that determines whether the given object is present
	 * in the immediate ancestry
	 */
	SQLHSTMT has_immediate_ancestor_stmt;

	/**
	 * The statement that determines whether the given object is present
	 * in the immediate ancestry -- also considering the version of the object
	 */
	SQLHSTMT has_immediate_ancestor_with_ver_stmt;

	/**
	 * The lock for add_property
	 */
	mutex_t add_property_lock;

	/**
	 * The statement that adds a new property
	 */
	SQLHSTMT add_property_stmt;

	/**
	 * The lock for get_session_info
	 */
	mutex_t get_session_info_lock;

	/**
	 * The statement that returns information about a provenance session
	 */
	SQLHSTMT get_session_info_stmt;

	/**
	 * The lock for get_all_objects
	 */
	mutex_t get_all_objects_lock;

	/**
	 * The statement that returns information about all provenance objects
	 */
	SQLHSTMT get_all_objects_stmt;

	/**
	 * The statement that returns information about all provenance objects,
     * including the creation session
	 */
	SQLHSTMT get_all_objects_with_session_stmt;

	/**
	 * The lock for get_object_info
	 */
	mutex_t get_object_info_lock;

	/**
	 * The statement that returns information about a provenance object
	 */
	SQLHSTMT get_object_info_stmt;

	/**
	 * The lock for get_version_info
	 */
	mutex_t get_version_info_lock;

	/**
	 * The statement that returns information about a specific version
	 * of the provenance object
	 */
	SQLHSTMT get_version_info_stmt;

	/**
	 * The mutex for get_object_ancestry
	 */
	mutex_t get_object_ancestry_lock;

	/**
	 * The statement for listing ancestors
	 */
	SQLHSTMT get_object_ancestors_stmt;

	/**
	 * The statement for listing ancestors of a specific version of the object
	 */
	SQLHSTMT get_object_ancestors_with_ver_stmt;

	/**
	 * The statement for listing descendants
	 */
	SQLHSTMT get_object_descendants_stmt;

	/**
	 * The statement for listing descendants of a specific version of the object
	 */
	SQLHSTMT get_object_descendants_with_ver_stmt;

	/**
	 * The mutex for get_properties
	 */
	mutex_t get_properties_lock;

	/**
	 * The statement for listing properties
	 */
	SQLHSTMT get_properties_stmt;

	/**
	 * The statement for listing properties of a specific version of the object
	 */
	SQLHSTMT get_properties_with_ver_stmt;

	/**
	 * The statement for listing specific properties
	 */
	SQLHSTMT get_properties_with_key_stmt;

	/**
	 * The statement for listing specific properties of a version of the object
	 */
	SQLHSTMT get_properties_with_key_ver_stmt;

	/**
	 * The mutex for lookup_by_property
	 */
	mutex_t lookup_by_property_lock;

	/**
	 * The statement for looking up by a property value
	 */
	SQLHSTMT lookup_by_property_stmt;

} cpl_odbc_t;


/**
 * The ODBC interface
 */
extern const cpl_db_backend_t CPL_ODBC_BACKEND;



/***************************************************************************/
/** Miscellaneous                                                         **/
/***************************************************************************/

/**
 * ODBC error record
 */
typedef struct {

	SQLSMALLINT index;
	SQLINTEGER native;
	SQLCHAR state[7];
	SQLCHAR text[256];
	SQLSMALLINT length;

} cpl_odbc_error_record_t;


#endif

