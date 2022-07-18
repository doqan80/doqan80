//Arat

void CInputMain::ItemPickup(LPCHARACTER ch, const char * data)
{
	struct command_item_pickup * pinfo = (struct command_item_pickup*) data;
	if (ch)
	{
		ch->PickupItem(pinfo->vid);
	}
}

//Alt©¥na Ekle

#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
void CInputMain::ItemPickupNew(LPCHARACTER ch, const char * data)
{
	struct command_item_pickup_new * pinfo = (struct command_item_pickup_new*) data;
	if (ch)
	{
		ch->PickupItemNew(pinfo->vid, pinfo->dwType);
	}
}
#endif

//Arat

		case HEADER_CG_ITEM_PICKUP:
			if (!ch->IsObserverMode())
				ItemPickup(ch, c_pData);
			break;

//Alt©¥na Ekle

#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
		case HEADER_CG_ITEM_PICKUP_NEW:
			if (!ch->IsObserverMode())
				ItemPickupNew(ch, c_pData);
			break;
#endif