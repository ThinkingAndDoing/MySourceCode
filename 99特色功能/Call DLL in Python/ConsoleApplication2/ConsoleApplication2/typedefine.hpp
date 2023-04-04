#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H


#define  uint32     unsigned long int
#define  uint16     unsigned int
#define  uint8      unsigned short int


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
