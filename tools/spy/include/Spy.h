/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef SPY_H_
#define SPY_H_

#include "core/base/ConferenceClientModule.h"
#include "core/base/FIFOQueue.h"

namespace spy {

    using namespace std;

    /**
     * This class can be used to simply display data distributed
     * using a conference.
     */
    class Spy : public core::base::ConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Spy(const Spy &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Spy& operator=(const Spy &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Spy(const int32_t &argc, char **argv);

            virtual ~Spy();

            core::base::ModuleState::MODULE_EXITCODE body();

        private:
            core::base::FIFOQueue m_fifo;

            virtual void setUp();

            virtual void tearDown();
    };

} // spy

#endif /*SPY_H_*/
