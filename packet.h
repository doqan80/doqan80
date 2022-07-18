//Arat

HEADER_CG_CLIENT_VERSION

//Ustune Ekle Say©¥y©¥ kendine gore ayarla ve ayn©¥ i?lemi client source deki packet.h icinde yap©¥n!

#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
	HEADER_CG_ITEM_PICKUP_NEW				= 82,
#endif

//Arat

typedef struct command_item_pickup

// Alt©¥na Ekle

#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
typedef struct command_item_pickup_new
{
	BYTE 	header;
	DWORD	vid;
	DWORD	dwType;
} TPacketCGItemPickupNew;
#endif