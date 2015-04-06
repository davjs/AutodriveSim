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

#ifndef OPENDAVINCI_CORE_WRAPPER_STATICINSTANCEFACTORY_H_
#define OPENDAVINCI_CORE_WRAPPER_STATICINSTANCEFACTORY_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

namespace core {
    namespace wrapper {

        // Compile-time factory.
        template <
                  typename product,
                  template <product> class worker,
                  template <typename> class configuration
                 >
        struct OPENDAVINCI_API StaticInstanceFactory
        {
            // Product type created by factory
            typedef product product_type;

            // Configuration for factory.
            typedef typename configuration<product_type>::configuration configuration_value;

            // Factory method to create a concrete product
            typedef worker<configuration_value::value> worker_type;

            // Wrapper to realize run-time factory.
            static worker_type& getInstance() { return instance; }

            protected:
                // Wrapper to realize run-time factory.
                static worker_type instance;
        };

    }
} // core::wrapper

#endif /*OPENDAVINCI_CORE_WRAPPER_STATICINSTANCEFACTORY_H_*/
