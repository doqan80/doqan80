//Arat 
bool CHARACTER::SwapItem(UINT bCell, UINT bDestCell)


//Ustune ekle yok ise bool CHARACTER arat ustune ekle
#ifdef __ENABLE_NEW_PICKUP_SYSTEM__
bool CHARACTER::PickupItemNew(DWORD dwVID, DWORD dwType)
{
	LPITEM item = ITEM_MANAGER::instance().FindByVID(dwVID);

	if (IsObserverMode())
		return false;

	if (!item || !item->GetSectree())
		return false;
	
	if (item->DistanceValid(this))
	{
		if (item->IsOwnership(this))
		{
			switch (dwType)
			{
				case 169999:
					if (item->GetType() != ITEM_METIN)
						return false;
					break;
				case 169998:
					if (item->GetType() != ITEM_WEAPON)
						return false;
					break;
				case 169997:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_BODY)
						return false;
					break;
				case 169996:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_EAR)
						return false;
					break;
				case 169995:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_SHIELD)
						return false;
					break;
				case 169994:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_NECK)
						return false;
					break;
				case 169993:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_FOOTS)
						return false;
					break;
				case 169992:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_HEAD)
						return false;
					break;
				case 169991:
					if (item->GetType() != ITEM_ARMOR && item->GetSubType() != ARMOR_WRIST)
						return false;
				default:
					if (item->GetVnum() != dwType)
						return false;
			}
			// 만약 주으려 하는 아이템이 엘크라면
			if (item->GetType() == ITEM_ELK)
			{
				GiveGold(item->GetCount());
				item->RemoveFromGround();

				M2_DESTROY_ITEM(item);

				Save();
			}
			// 평범한 아이템이라면
			else
			{
				if (item->IsStackable() && !IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_STACK))
				{
					BYTE bCount = item->GetCount();
					
					if (item->IsSkillBook())
					{
						for (int i = 0; i < SKILL_BOOK_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetSkillBookInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}
					}
					else if (item->IsUpgradeItem())
					{
						for (int i = 0; i < UPGRADE_ITEMS_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetUpgradeItemsInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}					
					}
					else if (item->IsStone())
					{
						for (int i = 0; i < STONE_ITEMS_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetStoneItemsInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}					
					}
					
					item->SetCount(bCount);
				}

				int iEmptyCell;
				if (item->IsDragonSoul())
				{
					if ((iEmptyCell = GetEmptyDragonSoulInventory(item)) == -1)
					{
						sys_log(0, "No empty ds inventory pid %u size %ud itemid %u", GetPlayerID(), item->GetSize(), item->GetID());
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
						return false;
					}
				}
				else
				{
					if ((iEmptyCell = GetEmptyInventory(item->GetSize())) == -1)
					{
						sys_log(0, "No empty inventory pid %u size %ud itemid %u", GetPlayerID(), item->GetSize(), item->GetID());
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
						return false;
					}
				}

				item->RemoveFromGround();
				
				if (item->IsDragonSoul())
					item->AddToCharacter(this, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyCell));
				else
					item->AddToCharacter(this, TItemPos(INVENTORY, iEmptyCell));

				char szHint[32+1];
				snprintf(szHint, sizeof(szHint), "%s %u %u", item->GetName(), item->GetCount(), item->GetOriginalVnum());
				LogManager::instance().ItemLog(this, item, "GET", szHint);
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item->GetName());

				if (item->GetType() == ITEM_QUEST)
					quest::CQuestManager::instance().PickupItem (GetPlayerID(), item);
			}

			//Motion(MOTION_PICKUP);
			return true;
		}
		else if (!IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_GIVE | ITEM_ANTIFLAG_DROP) && GetParty())
		{
			// 다른 파티원 소유권 아이템을 주으려고 한다면
			NPartyPickupDistribute::FFindOwnership funcFindOwnership(item);

			GetParty()->ForEachOnlineMember(funcFindOwnership);

			LPCHARACTER owner = funcFindOwnership.owner;

			if (!owner)
				return false;
			
            if (owner)
            {
			if (item->IsStackable() && !IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_STACK))
			{
				BYTE bCount = item->GetCount();
				
					if (item->IsSkillBook())
					{
						for (int i = 0; i < SKILL_BOOK_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetSkillBookInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}
					}
					else if (item->IsUpgradeItem())
					{
						for (int i = 0; i < UPGRADE_ITEMS_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetUpgradeItemsInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}					
					}
					else if (item->IsStone())
					{
						for (int i = 0; i < STONE_ITEMS_INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetStoneItemsInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = GetInventoryItem(i);

							if (!item2)
								continue;

							if (item2->GetVnum() == item->GetVnum())
							{
								int j;

								for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

								if (j != ITEM_SOCKET_MAX_NUM)
									continue;

								BYTE bCount2 = MIN(200 - item2->GetCount(), bCount);
								bCount -= bCount2;

								item2->SetCount(item2->GetCount() + bCount2);

								if (bCount == 0)
								{
									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item2->GetName());
									M2_DESTROY_ITEM(item);
									if (item2->GetType() == ITEM_QUEST)
										quest::CQuestManager::instance().PickupItem(GetPlayerID(), item2);
									return true;
								}
							}
						}					
					}
					
                    item->SetCount(bCount);

                }

            }

			int iEmptyCell;

			if (item->IsDragonSoul())
			{
				if (!(owner && (iEmptyCell = owner->GetEmptyDragonSoulInventory(item)) != -1))
				{
					owner = this;

					if ((iEmptyCell = GetEmptyDragonSoulInventory(item)) == -1)
					{
						owner->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
						return false;
					}
				}
			}
			else
			{
				if (!(owner && (iEmptyCell = owner->GetEmptyInventory(item->GetSize())) != -1))
				{
					owner = this;

					if ((iEmptyCell = GetEmptyInventory(item->GetSize())) == -1)
					{
						owner->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
						return false;
					}
				}
			}

			item->RemoveFromGround();

			if (item->IsDragonSoul())
				item->AddToCharacter(owner, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyCell));
			else
				item->AddToCharacter(owner, TItemPos(INVENTORY, iEmptyCell));

			char szHint[32+1];
			snprintf(szHint, sizeof(szHint), "%s %u %u", item->GetName(), item->GetCount(), item->GetOriginalVnum());
			LogManager::instance().ItemLog(owner, item, "GET", szHint);

			if (owner == this)
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s"), item->GetName());
			else
			{
				owner->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 획득: %s 님으로부터 %s"), GetName(), item->GetName());
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("아이템 전달: %s 님에게 %s"), owner->GetName(), item->GetName());
			}

			if (item->GetType() == ITEM_QUEST)
				quest::CQuestManager::instance().PickupItem (owner->GetPlayerID(), item);

			return true;
		}
	}

	return false;
}
#endif