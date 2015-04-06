/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "Spy.h"

int32_t main(int32_t argc, char **argv) {
    spy::Spy s(argc, argv);
    return s.runModule();
}
