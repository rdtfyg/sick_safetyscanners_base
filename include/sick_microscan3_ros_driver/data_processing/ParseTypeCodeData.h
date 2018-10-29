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
 * \file ParseTypeCodeData.h
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-10-16
 */
//----------------------------------------------------------------------

#ifndef SICK_MICROSCAN3_ROS_DRIVER_DATA_PROCESSING_PARSETYPECODEDATA_H
#define SICK_MICROSCAN3_ROS_DRIVER_DATA_PROCESSING_PARSETYPECODEDATA_H

#include <sick_microscan3_ros_driver/datastructure/Data.h>
#include <sick_microscan3_ros_driver/datastructure/PacketBuffer.h>
#include <sick_microscan3_ros_driver/datastructure/TypeCode.h>

#include <sick_microscan3_ros_driver/data_processing/ReadWriteHelper.h>

namespace sick {

namespace data_processing {


  /*!
   * \brief Parser to read the type code of a tcp sequence.
   */
class ParseTypeCodeData
{
public:
  /*!
   * \brief Constructor of the parser.
   */
  ParseTypeCodeData();

  /*!
   * \brief Parses a tcp sequence to read the type code of the sensor.
   *
   * \param buffer The incoming tcp sequence.
   * \param type_code Reference to the type code, which will be written while parsing.
   *
   * \returns If parsing was successful.
   */
  bool parseTCPSequence(const datastructure::PacketBuffer& buffer,
                        datastructure::TypeCode& type_code) const;

private:
  std::shared_ptr<sick::data_processing::ReadWriteHelper> m_reader_ptr;
  uint8_t readInterfaceType(const uint8_t*& data_ptr) const;
  float readMaxRange(const uint8_t*& data_ptr) const;
};

} // namespace data_processing
} // namespace sick

#endif // SICK_MICROSCAN3_ROS_DRIVER_DATA_PROCESSING_PARSETYPECODEDATA_H
