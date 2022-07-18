//Arat 

	Set(HEADER_CG_MYSHOP, sizeof(TPacketCGMyShop), "MyShop", false);

//Altına Ekle

#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
	Set(HEADER_CG_ITEM_PICKUP_NEW,	sizeof(TPacketCGItemPickupNew),	"PickupItemNew",	false);
#endif