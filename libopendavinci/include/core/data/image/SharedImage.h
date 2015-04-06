/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_DATA_IMAGE_SHAREDIMAGE_H_
#define OPENDAVINCI_CORE_DATA_IMAGE_SHAREDIMAGE_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SharedData.h"

namespace core {
    namespace data {
        namespace image {

            using namespace std;

            /**
             * This class provides information about a shared image using shared memory
             * segments. This class can be used to exchange information about
             * accessing this image. It can be used as follows:
             *
             * @code
             * // Server:
             * ... m_image = new XYZ...;
             * SharedPointer<core::wrapper::SharedMemory> memory = core::wrapper::SharedMemoryFactory::createSharedMemory("NameOfSharedMemory", 1024);
             * if (memory->isValid()) {
             *     SharedImage si;
             *     si.setName(memory->getName());
             *     si.setWidth(m_image->getWidth());
             *     si.setHeight(m_image->getHeight());
             *     si.setBytesPerPixel(m_image->getBytesPerPixel());
             *
             *     Container c(Container::SHARED_IMAGE, si);
             *     getConference().send(c);
             *
             *     // Write something to shared memory.
             *     memory->lock();
             *     memcpy(memory->getAddress(), m_image->getRawData(), 1024);
             *     memory->unlock();
             *     ...
             * }
             *
             *
             * // Client:
             * Container c = myFifo.leave();
             * if (c.getDataType() == Container::SHARED_IMAGE) {
             *     SharedImage si = c.getData<SharedImage>();
             *     SharedPointer<core::wrapper::SharedMemory> memory = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
             *     if (memory->isValid()) {
             *         memory->lock();
             *         ...
             *         memory->unlock();
             *     }
             * }
             * @endcode
             */
            class OPENDAVINCI_API SharedImage : public core::data::SharedData {
                public:
                    SharedImage();

                    virtual ~SharedImage();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    SharedImage(const SharedImage &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    SharedImage& operator=(const SharedImage &obj);

                    /**
                     * This method returns the image's width.
                     *
                     * @return Image's width.
                     */
                    uint32_t getWidth() const;

                    /**
                     * This method sets the image's width.
                     *
                     * @param width Image's width.
                     */
                    void setWidth(const uint32_t &width);

                    /**
                     * This method returns the image's height.
                     *
                     * @return Image's height.
                     */
                    uint32_t getHeight() const;

                    /**
                     * This method sets the image's height.
                     *
                     * @param height Image's height.
                     */
                    void setHeight(const uint32_t &height);

                    /**
                     * This method returns the image's bytes per pixel.
                     *
                     * @return Image's bytes per pixel.
                     */
                    uint32_t getBytesPerPixel() const;

                    /**
                     * This method sets the image's bytes per pixel.
                     *
                     * @param bytesPerPixel Image's bytes per pixel.
                     */
                    void setBytesPerPixel(const uint32_t &bytesPerPixel);

                    virtual uint32_t getSize() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_width;
                    uint32_t m_height;
                    uint32_t m_bytesPerPixel;
            };
        }
    }
} // core::data::image

#endif /*OPENDAVINCI_CORE_DATA_IMAGE_SHAREDIMAGE_H_*/
