// Arat

bool CPythonNetworkStream::SendItemPickUpPacket(DWORD vid)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGItemPickUp	itemPickUpPacket;
	itemPickUpPacket.header = HEADER_CG_ITEM_PICKUP;
	itemPickUpPacket.vid = vid;

	if (!Send(sizeof(TPacketCGItemPickUp), &itemPickUpPacket))
	{
		Tracen("SendItemPickUpPacket Error");
		return false;
	}

	return SendSequence();
}

// Alt©¥na Ekle

#ifdef ENABLE_NEW_PICKUP_SYSTEM
bool CPythonNetworkStream::SendItemPickUpNewPacket(DWORD vid, DWORD type)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGItemPickupNew	itemPickUpPacket;
	itemPickUpPacket.header = HEADER_CG_ITEM_PICKUP_NEW;
	itemPickUpPacket.vid = vid;
	itemPickUpPacket.dwType = type;

	if (!Send(sizeof(TPacketCGItemPickupNew), &itemPickUpPacket))
	{
		Tracen("SendItemPickUpPacket Error");
		return false;
	}

	return SendSequence();	
}
#endif