#ifndef TELLTALE_HPP
#define TELLTALE_HPP
#include "list"
#include "typedefine.hpp"

enum TelltaleIDs
{
	AutoHold,
	TurnLeft,
	TurnRight,
	LowFuel,
	SftyBelt,
	FrontFog,
	RearFog,
	AFSFailure,
	InvalidTelltaleID
};

struct TelltaleView
{
	enum TelltaleIDs enTelltaleID;
	uint16 u16Priority;
};


typedef std::list<TelltaleView> TelltaleViewList;
typedef std::list<TelltaleView>::iterator itTelltaleView;


class TelltaleStrategy
{
public:
	TelltaleStrategy(){ lstTelltaleView.clear(); };
	~TelltaleStrategy(){ lstTelltaleView.clear(); };
	void RequestWarning(enum TelltaleIDs ttid);
	void ReleaseWarning(enum TelltaleIDs ttid);
	uint16 GetFirstTelltaleID(void);

private:
	TelltaleViewList lstTelltaleView;

	void AddNewTelltale(TelltaleView stNewTelltale);
	bool boIDAlreadyInList(enum TelltaleIDs ttid);
};


#endif