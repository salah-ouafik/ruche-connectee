/* Generated: Mon Oct 03 2016 12:02:29 GMT-0600 (Mountain Daylight Time) */
/* Will not be regenerated. */

#include "phidgetbase.h"
#include "class/phsensor.gen.h"
#include "class/phsensor.gen.c"

static void CCONV
PhidgetPHSensor_errorHandler(PhidgetChannelHandle phid, Phidget_ErrorEventCode code) {
}

static PhidgetReturnCode CCONV
PhidgetPHSensor_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_setStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetPHSensor_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	return (_getStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetPHSensor_initAfterOpen(PhidgetChannelHandle phid) {
	return (_initAfterOpen(phid));
}

static PhidgetReturnCode CCONV
PhidgetPHSensor_setDefaults(PhidgetChannelHandle phid) {
	return (_setDefaults(phid));
}

static PhidgetReturnCode
PhidgetPHSensor_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_bridgeInput(phid, bp));
}

static void CCONV
PhidgetPHSensor_fireInitialEvents(PhidgetChannelHandle phid) {
	_fireInitialEvents(phid);
}
