//Arat

PyObject* netSendItemPickUpPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemPickUpPacket(vid);
	return Py_BuildNone();
}

//Alt©¥na Ekle

#ifdef ENABLE_NEW_PICKUP_SYSTEM
PyObject* netSendItemPickUpNewPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();
	
	int type;
	if (!PyTuple_GetInteger(poArgs, 1, &type))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemPickUpNewPacket(vid, type);
	return Py_BuildNone();
}
#endif

//Arat

		{ "SendItemPickUpPacket",				netSendItemPickUpPacket,				METH_VARARGS },

//Alt©¥na Ekle

#ifdef ENABLE_NEW_PICKUP_SYSTEM
		{ "SendItemPickUpNewPacket",			netSendItemPickUpNewPacket,				METH_VARARGS },
#endif
