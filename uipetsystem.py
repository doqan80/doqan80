# importlara ekle

import uipetitem

#Arat

self.feedwind = uipetfeed.PetFeedWindow()

#EKLE

self.itemgui = uipetitem.PetItemWindow()

#Arat

	def PetSkillTooltipShow(self, slot):

#Üstüne Ekle

	def PetItemListesi(self, liste):
		self.itemgui.ClearToplaList()
		lt = len(liste)
		rests = liste[1:lt]
		for i in xrange(0,lt-1):
			self.itemgui.SetMyItemList(int(rests[i]))
		self.itemgui.ShowList()

	def Toplama(self):
		if constInfo.PET_TOPLAMA_AKTIF == 0:
			constInfo.PET_TOPLAMA_AKTIF = 1
		else:
			constInfo.PET_TOPLAMA_AKTIF = 0

#Arat

	def SetLevel(self, level):
		if int(level) == 40 or int(level) == 60 or int(level) == 80:
			constInfo.EVOLUTION = int(level)
		else:
			constInfo.EVOLUTION = 0
		self.petlevel.SetText(level)

#Altına Ekle

#Arat

		except:
			import exception
			exception.Abort("PetInformationWindow.LoadWindow.BindObject")

#Üstüne Ekle

			self.toplama.SetEvent(ui.__mem_func__(self.Toplama))
			self.toplama.Hide()

#Arat

self.boardclose = self.GetChild("CloseButton")

#Altına Ekle

self.toplama = self.GetChild("Topla")

## petinformationwindow.py aç Ve Ekle NOT: Kendine göre ayarla

				{
					"name" : "Topla",
					"type" : "button",

					"x" : 25-4,
					"y" : 55 + 12+29,

					"text" : "Topla",

					"default_image" : "d:/ymir work/ui/public/small_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/small_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/small_button_03.sub",
				},
