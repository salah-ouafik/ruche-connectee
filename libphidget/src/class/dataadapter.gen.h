#ifndef _DATAADAPTER_H_
#define _DATAADAPTER_H_

/* Generated by WriteClassHeaderVisitor: Thu Jul 12 2018 16:00:52 GMT-0600 (MDT) */

#ifdef INCLUDE_PRIVATE
typedef struct _PhidgetDataAdapter *PhidgetDataAdapterHandle;

/* Methods */
API_PRETURN_HDR PhidgetDataAdapter_create(PhidgetDataAdapterHandle *ch);
API_PRETURN_HDR PhidgetDataAdapter_delete(PhidgetDataAdapterHandle *ch);
API_PRETURN_HDR PhidgetDataAdapter_sendPacket(PhidgetDataAdapterHandle ch, const uint8_t *data,
  size_t dataLen);
API_VRETURN_HDR PhidgetDataAdapter_sendPacket_async(PhidgetDataAdapterHandle ch, const uint8_t *data,
  size_t dataLen, Phidget_AsyncCallback fptr, void *ctx);

/* Properties */
API_PRETURN_HDR PhidgetDataAdapter_getMaxPacketLength(PhidgetDataAdapterHandle ch,
  uint32_t *maxPacketLength);

/* Events */
typedef void (CCONV *PhidgetDataAdapter_OnPacketCallback)(PhidgetDataAdapterHandle ch, void *ctx,
  const uint8_t *data, size_t dataLen, int overrun);

API_PRETURN_HDR PhidgetDataAdapter_setOnPacketHandler(PhidgetDataAdapterHandle ch,
  PhidgetDataAdapter_OnPacketCallback fptr, void *ctx);

#endif /* INCLUDE_PRIVATE */
#endif /* _DATAADAPTER_H_ */
