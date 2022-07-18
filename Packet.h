//Arat

	HEADER_CG_KEY_AGREEMENT						= 0xfb,

// Ustune Ekle Say©¥s©¥n©¥ Game Source Packet.h ile ayn©¥ olacak ?ekilde yap !

#ifdef ENABLE_NEW_PICKUP_SYSTEM
	HEADER_CG_ITEM_PICKUP_NEW				= 82,
#endif

//Arat

typedef struct command_item_pickup
{
	BYTE header;
	DWORD vid;
} TPacketCGItemPickUp;

//Alt©¥na Ekle

#ifdef ENABLE_NEW_PICKUP_SYSTEM
typedef struct command_item_pickup_new
{
	BYTE 	header;
	DWORD	vid;
	DWORD	dwType;
} TPacketCGItemPickupNew;
#endif