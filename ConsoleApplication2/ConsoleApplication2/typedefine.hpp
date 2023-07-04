#ifndef TYPEDEFINE_HPP
#define TYPEDEFINE_HPP


#define  uint32     unsigned int
#define  uint16     unsigned short int
#define  uint8     unsigned char


enum VirtualKey
{
	VKY_LEFT,
	VKY_RIGHT,
	VKY_DOWN,
	VKY_UP,
	VKY_OK,
	VKY_LONG_OK
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
