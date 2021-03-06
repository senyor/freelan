/*
 * libasiotap - A portable TAP adapter extension for Boost::ASIO.
 * Copyright (C) 2010-2011 Julien KAUFFMANN <julien.kauffmann@freelan.org>
 *
 * This file is part of libasiotap.
 *
 * libasiotap is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libasiotap is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libasiotap in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file udp_builder.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief An UDP frame builder class.
 */

#ifndef ASIOTAP_OSI_UDP_BUILDER_HPP
#define ASIOTAP_OSI_UDP_BUILDER_HPP

#include "builder.hpp"
#include "udp_frame.hpp"
#include "ipv4_frame.hpp"

#include <boost/asio.hpp>

namespace asiotap
{
	namespace osi
	{
		/**
		 * \brief An udp frame builder class.
		 */
		template <>
		class builder<udp_frame> : public _base_builder<udp_frame>
		{
			public:

				/**
				 * \brief Create a builder.
				 * \param buf The buffer to use.
				 * \param payload_size The size of the payload.
				 */
				builder(boost::asio::mutable_buffer buf, size_t payload_size);

				/**
				 * \brief Write the frame.
				 * \param source The source port.
				 * \param destination The destination port.
				 * \return The total size of the written frame, including its payload.
				 */
				size_t write(
				    uint16_t source,
				    uint16_t destination
				) const;

				/**
				 * \brief Update the checksum.
				 * \param parent_frame The parent frame.
				 */
				void update_checksum(const_helper<ipv4_frame> parent_frame);
		};

		inline builder<udp_frame>::builder(boost::asio::mutable_buffer buf, size_t payload_size) :
			_base_builder<udp_frame>(buf, payload_size)
		{
		}
	}
}

#endif /* ASIOTAP_UDP_BUILDER_HPP */

