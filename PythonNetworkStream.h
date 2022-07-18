// Arat

		bool SendItemPickUpPacket(DWORD vid);

//Alt©¥na EKLE

#ifdef ENABLE_NEW_PICKUP_SYSTEM
		bool SendItemPickUpNewPacket(DWORD vid, DWORD type);
#endif