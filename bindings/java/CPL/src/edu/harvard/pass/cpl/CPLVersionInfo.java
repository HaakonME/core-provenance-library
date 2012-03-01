package edu.harvard.pass.cpl;

/*
 * CPLVersionInfo.java
 * Core Provenance Library
 *
 * Copyright 2012
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


import swig.direct.CPLDirect.*;


/**
 * An information about a specific version of a provenance object
 *
 * @author Peter Macko
 */
public class CPLVersionInfo {

	/// The provenance object
	private CPLObject object;

	/// The version number
	private int version;

	/// The session that created this version
	private CPLSession session;

	/// The creation time of this version
	private long creationTime;


	/**
	 * Create an instance of CPLVersionInfo
	 *
	 * @param object the provenance object
	 * @param version the version number
	 */
	CPLVersionInfo(CPLObject object, int version) {
		this.object = object;
		this.version = version;
		fetchInfo();
	}


	/**
	 * Create an instance of CPLVersionInfo
	 *
	 * @param object the provenance object
	 */
	CPLVersionInfo(CPLObject object) {
		this(object, object.getVersion());
	}


	/**
	 * Determine whether this and the other object are equal
	 *
	 * @param other the other object
	 * @return true if they are equal
	 */
	@Override
	public boolean equals(Object other) {
		if (other instanceof CPLVersionInfo) {
			CPLVersionInfo o = (CPLVersionInfo) other;
			return o.object.equals(object) && o.version == version;
		}
		else {
			return false;
		}
	}


	/**
	 * Compute the hash code of this object
	 *
	 * @return the hash code
	 */
	@Override
	public int hashCode() {
		return (object.hashCode() << 8) ^ version;
	}


	/**
	 * Return a string representation of the object. Note that this is based
	 * on the internal object ID, since the name might not be known.
	 *
	 * @return the string representation
	 */
	@Override
	public String toString() {
		return object.toString() + "-" + version;
	}


	/**
	 * Fetch the session info if it is not already present
	 */
	protected void fetchInfo() {

		// Fetch the info from CPL
		
		SWIGTYPE_p_p_cpl_version_info_t ppInfo
			= CPLDirect.new_cpl_version_info_tpp();

		try {
			int r = CPLDirect.cpl_get_version_info(object.id, version,
					CPLDirect.cpl_convert_pp_cpl_version_info_t(ppInfo));
			CPLException.assertSuccess(r);

			cpl_version_info_t info
				= CPLDirect.cpl_dereference_pp_cpl_version_info_t(ppInfo);

			version = info.getVersion();
			session = new CPLSession(info.getSession());
			creationTime = info.getCreation_time();

			CPLDirect.cpl_free_version_info(info);
		}
		finally {
			CPLDirect.delete_cpl_version_info_tpp(ppInfo);
		}
	}


	/**
	 * Get the provenance object
	 *
	 * @return the provenance object
	 */
	public CPLObject getObject() {
		return object;
	}


	/**
	 * Get the version number
	 *
	 * @return the version number
	 */
	public int getVersion() {
		return version;
	}


	/**
	 * Get the session that created this version
	 *
	 * @return the session
	 */
	public CPLSession getSession() {
		return session;
	}


	/**
	 * Get the time this version was created
	 *
	 * @return the time expressed as Unix time
	 */
	public long getCreationTime() {
		return creationTime;
	}


	/**
	 * Create a more detailed string representation of the object
	 *
	 * @param detail whether to provide even more detail
	 * @return a multi-line string describing the object
	 */
	public String toString(boolean detail) {

		StringBuilder sb = new StringBuilder();

		sb.append("Version number: ");
		sb.append(getVersion());
		sb.append("\n");

		if (detail) {
			sb.append("Session       : ");
			sb.append(getSession());
			sb.append("\n");
		}

		sb.append("Creation time : ");
		sb.append(new java.sql.Date(1000L * getCreationTime()));
		sb.append(" ");
		sb.append(new java.sql.Time(1000L * getCreationTime()));
		sb.append("\n");

		return sb.toString();
	}
}

