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
 * \file arp_proxy.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief An ARP proxy class.
 */

#ifndef ASIOTAP_OSI_ARP_PROXY_HPP
#define ASIOTAP_OSI_ARP_PROXY_HPP

#include "ethernet_filter.hpp"
#include "arp_filter.hpp"
#include "arp_builder.hpp"

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <map>

namespace asiotap
{
	namespace osi
	{
		/**
		 * \brief An ARP proxy class.
		 */
		class arp_proxy
		{
			public:

				/**
				 * \brief The Ethernet address type.
				 */
				typedef boost::array<uint8_t, ETHERNET_ADDRESS_SIZE> ethernet_address_type;

				/**
				 * \brief The entry type.
				 */
				typedef std::pair<boost::asio::ip::address_v4, ethernet_address_type> entry_type;

				/**
				 * \brief Create a new ARP proxy.
				 * \param ethernet_filter The Ethernet filter to use.
				 */
				arp_proxy(ethernet_filter& ethernet_filter);

				/**
				 * \brief Add a proxy entry.
				 * \param entry The entry to add.
				 * \return If an entry for the specified software address already exists, nothing is done and the call returns false. Otherwise, the call returns true.
				 */
				bool add_entry(const entry_type& entry);

				/**
				 * \brief Add a proxy entry.
				 * \param software_address The software address.
				 * \param hardware_address The hardware address.
				 * \return If an entry for the specified software address already exists, nothing is done and the call returns false. Otherwise, the call returns true.
				 */
				bool add_entry(const boost::asio::ip::address_v4& software_address, const ethernet_address_type& hardware_address);

				/**
				 * \brief Delete a proxy entry.
				 * \param software_address The software address.
				 * \return If an entry was deleted, true is returned. Otherwise, the call returns false.
				 */
				bool remove_entry(const boost::asio::ip::address_v4& software_address);

			private:

				ethernet_filter& m_ethernet_filter;
				arp_filter<ethernet_filter> m_arp_filter;
				std::map<boost::asio::ip::address_v4, ethernet_address_type> m_entry_map;
		};
		
		inline arp_proxy::arp_proxy(ethernet_filter& _ethernet_filter) :
			m_ethernet_filter(_ethernet_filter),
			m_arp_filter(m_ethernet_filter)
		{
		}
		
		inline bool arp_proxy::add_entry(const entry_type& entry)
		{
			return m_entry_map.insert(entry).second;
		}
		
		inline bool arp_proxy::add_entry(const boost::asio::ip::address_v4& software_address, const ethernet_address_type& hardware_address)
		{
			return add_entry(std::make_pair(software_address, hardware_address));
		}
		
		inline bool arp_proxy::remove_entry(const boost::asio::ip::address_v4& software_address)
		{
			return (m_entry_map.erase(software_address) > 0);
		}
	}
}

#endif /* ASIOTAP_ARP_PROXY_HPP */

