#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H



#define  uint32     unsigned long int
#define  uint16     unsigned int
#define  uint8      unsigned short int


enum VirtualKey
{
	VK_LEFT,
	VK_RIGHT,
	VK_DOWN,
	VK_UP,
	VK_OK,
	VK_LONG_OK
};



enum WarningAction
{
	WBRelease,
	WBIgnore,
	WBDisplace,
	WBDepend,
	WBInvalid
};


#endif
