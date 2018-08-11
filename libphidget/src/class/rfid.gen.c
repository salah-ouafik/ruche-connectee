/* Generated: Thu Jul 12 2018 16:00:52 GMT-0600 (MDT) */

#include "device/rfiddevice.h"
static void CCONV PhidgetRFID_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static PhidgetReturnCode CCONV PhidgetRFID_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRFID_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRFID_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetRFID_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetRFID_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetRFID_fireInitialEvents(PhidgetChannelHandle phid);

struct _PhidgetRFID {
	struct _PhidgetChannel phid;
	char lastTagString[25];
	PhidgetRFID_Protocol lastTagProtocol;
	int antennaEnabled;
	int tagPresent;
	PhidgetRFID_OnTagCallback Tag;
	void *TagCtx;
	PhidgetRFID_OnTagLostCallback TagLost;
	void *TagLostCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRFIDHandle ch;
	int version;

	ch = (PhidgetRFIDHandle)phid;

	version = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (version != 1) {
		logerr("%"PRIphid": bad version %d != 1", phid, version);
		return (EPHIDGET_BADVERSION);
	}

	memcpy(&ch->lastTagString, getBridgePacketUInt8ArrayByName(bp, "lastTagString"),
	  sizeof (char) * 25);
	ch->antennaEnabled = getBridgePacketInt32ByName(bp, "antennaEnabled");
	ch->tagPresent = getBridgePacketInt32ByName(bp, "tagPresent");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetRFIDHandle ch;

	ch = (PhidgetRFIDHandle)phid;

	return (createBridgePacket(bp, 0, "_class_version_=%u"
	  ",lastTagString=%25R"
	  ",antennaEnabled=%d"
	  ",tagPresent=%d"
	  ,1 /* class version */
	  ,ch->lastTagString
	  ,ch->antennaEnabled
	  ,ch->tagPresent
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRFIDHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetRFIDHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_WRITE:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SETANTENNAON:
		TESTBOOL(getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK) {
			logerr("%"PRIphid": DEVBRIDGEINPUT() failed: %d", phid, res);
			break;
		}
		ch->antennaEnabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp))
			FIRE_PROPERTYCHANGE(ch, "AntennaEnabled");
		break;
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetRFIDDeviceHandle parentRFID;
	PhidgetRFIDHandle ch;
	PhidgetReturnCode ret;

	TESTPTRL(phid);
	ch = (PhidgetRFIDHandle)phid;

	ret = EPHIDGET_OK;

	parentRFID = (PhidgetRFIDDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1023_RFID_000:
		ch->antennaEnabled = 1;
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_104:
		ch->antennaEnabled = 1;
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_200:
		ch->antennaEnabled = 1;
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_201:
		ch->antennaEnabled = 1;
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_100:
		ch->antennaEnabled = 1;
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	memset(ch->lastTagString, '\0', 25);
	ch->lastTagProtocol = 0;

	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetRFIDHandle ch;
	PhidgetReturnCode ret;

	TESTPTRL(phid);

	ch = (PhidgetRFIDHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1023_RFID_000:
		break;
	case PHIDCHUID_1023_RFID_104:
		break;
	case PHIDCHUID_1023_RFID_200:
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK) {
			logerr("%"PRIphid": failed to set [antennaEnabled] default: %d", phid, ret);
			break;
		}
		break;
	case PHIDCHUID_1023_RFID_201:
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK) {
			logerr("%"PRIphid": failed to set [antennaEnabled] default: %d", phid, ret);
			break;
		}
		break;
	case PHIDCHUID_1024_RFID_100:
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK) {
			logerr("%"PRIphid": failed to set [antennaEnabled] default: %d", phid, ret);
			break;
		}
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	return (ret);
}

static void CCONV
_fireInitialEvents(PhidgetChannelHandle phid) {

}

static void CCONV
PhidgetRFID_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetRFID));
}

API_PRETURN
PhidgetRFID_create(PhidgetRFIDHandle *phidp) {

	CHANNELCREATE_BODY(RFID, PHIDCHCLASS_RFID);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_delete(PhidgetRFIDHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetRFID_write(PhidgetRFIDHandle ch, const char *tagString, PhidgetRFID_Protocol protocol,
  int lockTag) {

	TESTPTRL(ch);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);
	TESTATTACHEDL(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_WRITE, NULL, NULL, "%s%d%d", tagString,
	  protocol, lockTag);
}

API_PRETURN
PhidgetRFID_setAntennaEnabled(PhidgetRFIDHandle ch, int antennaEnabled) {

	TESTPTRL(ch);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);
	TESTATTACHEDL(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETANTENNAON, NULL, NULL, "%d",
	  antennaEnabled));
}

API_PRETURN
PhidgetRFID_getAntennaEnabled(PhidgetRFIDHandle ch, int *antennaEnabled) {

	TESTPTRL(ch);
	TESTPTRL(antennaEnabled);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);
	TESTATTACHEDL(ch);

	*antennaEnabled = ch->antennaEnabled;
	if (ch->antennaEnabled == (int)PUNK_BOOL)
		return (EPHIDGET_UNKNOWNVAL);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_getTagPresent(PhidgetRFIDHandle ch, int *tagPresent) {

	TESTPTRL(ch);
	TESTPTRL(tagPresent);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);
	TESTATTACHEDL(ch);

	*tagPresent = ch->tagPresent;
	if (ch->tagPresent == (int)PUNK_BOOL)
		return (EPHIDGET_UNKNOWNVAL);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_setOnTagHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagCallback fptr, void *ctx) {

	TESTPTRL(ch);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);

	ch->Tag = fptr;
	ch->TagCtx = ctx;

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_setOnTagLostHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagLostCallback fptr, void *ctx) {

	TESTPTRL(ch);
	TESTCHANNELCLASSL(ch, PHIDCHCLASS_RFID);

	ch->TagLost = fptr;
	ch->TagLostCtx = ctx;

	return (EPHIDGET_OK);
}
