import pythonApi
player = __import__(pythonApi.GetModuleName("player"))
net = __import__(pythonApi.GetModuleName("net"))
app = __import__(pythonApi.GetModuleName("app"))
item = __import__(pythonApi.GetModuleName("item"))
chat = __import__(pythonApi.GetModuleName("chat"))
ime = __import__(pythonApi.GetModuleName("ime"))
import os
import ui
import mouseModule
import uiCommon
import snd
import grp
import uiScriptLocale
import uiToolTip
import localeInfo
import constInfo
import wndMgr
import translate
import dbg
from ui_wrapper import _ui

FILE_NAME_LEN = 40 
DEFAULT = "Nesne eklenmemiþ"
class PopupDialog(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.__Load()
		self.__Bind()
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	def __Load(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/PopupDialog.py")
		except:
			import exception
			exception.Abort("PopupDialog.__Load")
	def __Bind(self):
		try:
			self.textLine=self.GetChild("message")
			self.okButton=self.GetChild("accept")
		except:
			import exception
			exception.Abort("PopupDialog.__Bind")
		self.okButton.SAFE_SetEvent(self.__OnOK)
	def Open(self, msg):
		self.textLine.SetText(msg)
		self.SetCenterPosition()
		self.Show()
		self.SetTop()
	def __OnOK(self):
		self.Hide()
class Item(ui.ListBoxEx.Item):
	def __init__(self, itemName, vnum):
		ui.ListBoxEx.Item.__init__(self)
		self.canLoad=0
		self.text=itemName
		self.vnum=vnum
		self.textLine=self.__CreateTextLine(itemName[:FILE_NAME_LEN])
	def __del__(self):
		ui.ListBoxEx.Item.__del__(self)
	def GetText(self):
		return self.text
	def GetVnum(self):
		return self.vnum
	def SetSize(self, width, height):
		ui.ListBoxEx.Item.SetSize(self, 6*len(self.textLine.GetText()) + 4, height)
	def __CreateTextLine(self, itemName):
		textLine=ui.TextLine()
		textLine.SetParent(self)
		textLine.SetPosition(0, 0)

		textLine.SetText(itemName)
		textLine.Show()
		return textLine
class PetItemWindow(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.toplananlar=[]
		self.fileListBox=None
		self.fileListBox2=None
		self.toolTip = uiToolTip.ToolTip()
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)
	def Show(self):
		ui.ScriptWindow.Show(self)
		self.SetTop()
	def Close(self):
		if self.toolTip:
			self.toolTip.Hide()
		self.Hide()
	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/petitem.py")
		except:
			import exception
			exception.Abort("PetItemWindow.LoadWindow")			
		try:
			self.petfeed = self.GetChild("board")
			self.closebtn = self.GetChild("TitleBarPet")
			self.TitleName = self.GetChild("TitleName")
			self.TitleName.SetText("Pet Toplama Ayarlarý")
			self.okButton = self.GetChild("okButton")
			self.delButton = self.GetChild("delButton")
			self.button3 = self.GetChild("button3")
			self.okButton.SAFE_SetEvent(self.__OnOK)
			self.delButton.SAFE_SetEvent(self.__OnDel)
			self.fileListBox = self.GetChild("ListBox")
			self.fileListBox2 = self.GetChild("ListBox2")
			self.thinboard = self.GetChild("thinboard")
			self.thinname = self.GetChild("thinname")
			self.thinname.SetText("Toplanan Nesneler")
			self.thinboard2 = self.GetChild("thinboard2")
			self.thinname2 = self.GetChild("thinname2")
			self.thinname2.SetText("Nesne Listesi")
			self.button3.SAFE_SetEvent(self.Close)
		except:
			import exception
			exception.Abort("PetItemWindow.LoadWindow")

		self.popupDialog=PopupDialog(self)
		self.okButton.ShowToolTip = lambda arg=1: self.__OverInButtonMenu(arg)
		self.okButton.HideToolTip = lambda arg=1: self.__OverOutButtonMenu()
		self.delButton.ShowToolTip = lambda arg=2: self.__OverInButtonMenu(arg)
		self.delButton.HideToolTip = lambda arg=2: self.__OverOutButtonMenu()
		self.fileListBox.SetScrollBar(self.GetChild("ScrollBar"))
		self.fileListBox2.SetScrollBar(self.GetChild("ScrollBar2"))
		self.itemler = pack_open("locale/tr/pet_item_list.txt", "28101993", "05111999", "01011999", "01011995","r").readlines()
		if len(self.itemler)>0:
			for i in xrange(len(self.itemler)):
				parcala = self.itemler[i][:-1].split("\t")
				self.__AppendItem2(str(parcala[1]),int(parcala[0]))
		self.SetTop()
		self.SetCenterPosition()
	def SetMyItemList(self,vnum):
		self.toplananlar.append(vnum)
	def ShowList(self):
		if not self.toplananlar:
			self.__AppendItem("Nesne eklenmemiþ",0)
		for it in self.toplananlar:
			item.SelectItem(int(it))
			if int(it) == 169999:
				self.__AppendItem("Taþlar (+0 > +4)",int(it))
			elif int(it) == 169998:
				self.__AppendItem("Silahlar",int(it))
			elif int(it) == 169997:
				self.__AppendItem("Zýrhlar",int(it))
			elif int(it) == 169996:
				self.__AppendItem("Küpeler",int(it))
			elif int(it) == 169995:
				self.__AppendItem("Kalkanlar",int(it))
			elif int(it) == 169994:
				self.__AppendItem("Kolyeler",int(it))
			elif int(it) == 169993:
				self.__AppendItem("Ayakkabýlar",int(it))
			elif int(it) == 169992:
				self.__AppendItem("Bilezikler",int(it))
			elif int(it) == 169991:
				self.__AppendItem("Kasklar",int(it))
			else:
				self.__AppendItem(item.GetItemName(),int(it))

	def __OnOK(self):
		selItem=self.fileListBox2.GetSelectedItem()
		if selItem:
			if int(len(self.toplananlar)) >= 58:
				self.__PopupMessage("Toplanabilecek maksimum nesne sayýsýna ulaþýldý !")
			elif selItem.GetVnum() in constInfo.PET_TOPLANANLAR:
				return
			else:
				constInfo.PET_TOPLANANLAR.append(selItem.GetVnum())
				self.ClearToplaList()
				for i in constInfo.PET_TOPLANANLAR:
					self.SetMyItemList(i)
					dbg.TraceError("{0}".format(int(i)))
				self.ShowList()
		else:
			self.__PopupMessage("Sað taraftan nesne seçmelisin !")
	def __OnDel(self):
		selItem=self.fileListBox.GetSelectedItem()
		if selItem and int(selItem.GetVnum()) > 0:
			constInfo.PET_TOPLANANLAR.remove(selItem.GetVnum())
			self.ClearToplaList()
			for i in constInfo.PET_TOPLANANLAR:
				self.SetMyItemList(i)
			self.ShowList()
		else:
			self.__PopupMessage("Sol taraftan nesne seçmelisin !")

	def __RefreshList(self):
		self.ClearToplaList()
	def ClearToplaList(self):
		self.toplananlar=[]
		self.fileListBox.RemoveAllItems()
	def __AppendItem(self, itemName, vnum):
		self.fileListBox.AppendItem(Item(itemName,vnum))
	def __AppendItem2(self, itemName, vnum):
		self.fileListBox2.AppendItem(Item(itemName,vnum))
	def __PopupMessage(self, msg):
		self.popupDialog.Open(msg)
	def __ShowMenuToolTip(self, msg):
		self.toolTip.ClearToolTip()
		self.toolTip.AppendTextLine(msg)
		self.toolTip.Show()
	def __OverInButtonMenu(self, num):
		if num == 1:
			self.__ShowMenuToolTip("Listeye Ekle")
		if num == 2:
			self.__ShowMenuToolTip("Listeden Kaldýr")
	def __OverOutButtonMenu(self):
		self.toolTip.Hide()
	def OnPressEscapeKey(self):
		self.Close()
		return True
	def OnUpdate(self):
		if constInfo.PET_TOPLAMA_AKTIF == 1:
			for i in range(len(constInfo.PET_TOPLANANLAR)):
				player.PickCloseAutoItem(i)
		
