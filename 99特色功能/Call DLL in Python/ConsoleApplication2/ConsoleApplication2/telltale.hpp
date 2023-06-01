#ifndef TELLTALE_HPP
#define TELLTALE_HPP
#include "list"
#include "typedefine.hpp"


struct TelltaleView
{
	enum WarningIDs enTelltaleID;
	uint16 u16Priority;
};


typedef std::list<TelltaleView> TelltaleViewList;
typedef std::list<TelltaleView>::iterator itTelltaleView;


class TelltaleStrategy
{
public:
	TelltaleStrategy(){ lstTelltaleView.clear(); };
	~TelltaleStrategy(){ lstTelltaleView.clear(); };
	void RequestWarning(enum WarningIDs ttid);
	void ReleaseWarning(enum WarningIDs ttid);
	uint16 GetFirstTelltaleID(void);

private:
	TelltaleViewList lstTelltaleView;

	void AddNewTelltale(TelltaleView stNewTelltale);
	bool ListContainSameID(enum WarningIDs ttid);
};


#endif