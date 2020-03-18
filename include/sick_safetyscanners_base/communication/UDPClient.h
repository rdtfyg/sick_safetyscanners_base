// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------

/*!
*  Copyright (C) 2018, SICK AG, Waldkirch
*  Copyright (C) 2018, FZI Forschungszentrum Informatik, Karlsruhe, Germany
*
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.

*/

// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!
 * \file AsyncUDPClient.h
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#ifndef SICK_SAFETYSCANNERS_BASE_COMMUNICATION_ASYNCUDPCLIENT_H
#define SICK_SAFETYSCANNERS_BASE_COMMUNICATION_ASYNCUDPCLIENT_H

//#include <ros/ros.h>
// #include <sick_safetyscanners_base/log.h>

#include <functional>
#include <iostream>
#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/cstdint.hpp>
#include <boost/function.hpp>

#include "sick_safetyscanners_base/datastructure/PacketBuffer.h"
#include "sick_safetyscanners_base/log.h"
#include "sick_safetyscanners_base/types.h"

namespace sick
{
namespace communication
{

/*!
 * \brief An asynchronous udp client.
 */
class UDPClient
{
public:
  // TODO typedefs fur globale typen auslagern
  /*!
   * \brief Typedef to a reference to a function. Will be used to process the incoming packets.
   */
  // typedef boost::function<void(const sick::datastructure::PacketBuffer &)> PacketHandler;
  using PacketHandler = std::function<void(const sick::datastructure::PacketBuffer &)>;

  /*!
   * \brief Constructor of the asynchronous udp client.
   *
   * \param packet_handler Function to handle incoming packets.
   * \param io_service Instance of the boost io_service.
   * \param local_port The local port, where the udp packets will arrive.
   */

  UDPClient(
      // const PacketHandler &packet_handler,
      boost::asio::ip::udp::socket &&socket,
      const boost::asio::ip::address_v4 &server_ip,
      uint16_t server_port = 0);
  UDPClient(
      // const PacketHandler &packet_handler,
      boost::asio::io_service &io_service,
      const boost::asio::ip::address_v4 &server_ip,
      uint16_t server_port = 0);

  UDPClient() = delete;
  UDPClient(const UDPClient &) = delete;
  UDPClient &operator=(const UDPClient &) = delete;

  /*!
   * \brief The destructor of the asynchronous udp client.
   */
  virtual ~UDPClient();

  // TODO Wat furn Service, bessere Namen
  /*!
   * \brief Start the listening loop for the udp data packets.
   */
  // void runService();

  void run(PacketHandler &handler);

  /*!
   * \brief Returns the actual port assigned to the local machine
   * \return Local port number
   */
  unsigned short getLocalPort();

private:
  datastructure::PacketBuffer::ArrayBuffer m_recv_buffer;
  PacketHandler m_packet_handler;
  std::shared_ptr<boost::asio::io_service::work> m_io_work_ptr;
  boost::asio::ip::udp::socket m_socket;
  boost::asio::ip::udp::endpoint m_remote_endpoint;

  void startReceive();

  // TODO error codes sind boese
  void handleReceive(const boost::system::error_code &error, const std::size_t &bytes_transferred);
};
} // namespace communication
} // namespace sick

#endif // SICK_SAFETYSCANNERS_BASE_COMMUNICATION_ASYNCUDPCLIENT_H