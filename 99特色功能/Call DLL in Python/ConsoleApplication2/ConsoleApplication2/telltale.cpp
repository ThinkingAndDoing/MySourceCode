
#include "telltale.hpp"
#include "warningresourceids.hpp"
#include "stdio.h"


struct TelltaleView stTelltalePriorityArray[] = {
	{ ABSLampTT, 1 },
	{ ABSLampBlinkTT, 1 },
	{ BattChargeTT, 1 },
	{ BrakeRedLampTT, 1 },
	{ BrakeRedLampBlinkTT, 1 },
	{ BrakeRedLampUSTT, 1 },
	{ BrakeRedLampUSBlinkTT, 1 },
	{ BrakeYellowLampTT, 1 },
	{ BrakeYellowLampUSTT, 1 },
	{ BrakePadWearTT, 1 },
	{ BrakePadWearEUorUSTT, 1 },
	{ ESCLampTT, 1 },
	{ ESCLampBlinkTT, 1 },
	{ GenWarningTriTT, 1 },
	{ InforsignTT, 2 },
	{ AHBCErrLampTT, 3 },
	{ AHBCHiBeamTT, 1 },
	{ AHBCLowBeamTT, 2 },
	{ AHBCErrTT, 1 },
	{ HiBeamTT, 3 },
	{ PositionLightTT, 1 },
	{ PositionLightErrTT, 2 },
	{ LoBeamTT, 4 },
	{ RainSenTT, 1 },
	{ ParkBrakeTT, 1 },
	{ ParkBrakeBlinkTT, 1 },
	{ ParkBrakeUSTT, 1 },
	{ ParkBrakeUSBlinkTT, 1 },
	{ RearFogTT, 1 },
	{ ElectricalVehicleSystemErrorTT, 1 },
	{ EVReadyTT, 1 },
	{ SRSAirbagTT, 1 },
	{ SRSAirbagBlinkTT, 1 },
	{ TPMTT, 1 },
	{ TPMBlinkTT, 1 },
	{ TurnLeftTT, 1 },
	{ TurnRightTT, 1 },
	{ ForwardColWarnOFFTT, 1 },
	{ ForwardColWarnOFFBlinkTT, 1 },
	{ ForwardColWarnTT, 1 },
	{ ForwardColWarnBlinkTT, 1 },
	{ AEBErrorTT, 1 },
	{ SteerAssistFailTT, 1 },
	{ ChargeCablePlugTT, 1 },
	{ ChildLockActivateTT, 2 },
	{ ChildLockErrTT, 1 },
	{ TurnIndicatorWarnTT, 2 },
	{ NoTorqueAvailableTT, 1 },
	{ MaxSpeedReachTT, 2 },
	{ WiperFailureTT, 3 },
	{ BrakeLightFailureTT, 1 },
	{ HVBattWarnRedTT, 1 },
	{ HVBattWarnAmberTT, 1 },
	{ OpenDoorWarnTT, 1 },
	{ OpenDoorWarnBlinkTT, 1 },
	{ HVLoBattLevelTT, 1 },
	{ HiBeamFaultTT, 2 },
	{ LoBeamFaultTT, 1 },
	{ AdjustHeadlampLevelErrTT, 1 },
	{ SeatBeltTT, 1 },
	{ AutoHoldTT, 1 },
};


TelltaleStrategy::TelltaleStrategy(void)
{ 
	m_lstTelltaleView.clear();
}


TelltaleStrategy::~TelltaleStrategy()
{ 
	m_lstTelltaleView.clear();
}


bool TelltaleStrategy::ListContainSameID(enum WarningIDs enTelltaleID)
{
	for (itTelltaleView it = m_lstTelltaleView.begin(); it != m_lstTelltaleView.end(); ++it)
	{
		if (it->enTelltaleID == enTelltaleID)
		{
			return true;
		}
	}
	return false;
}


void TelltaleStrategy::RequestTelltale(enum WarningIDs enID)
{
	for (int i = 0; i < sizeof(stTelltalePriorityArray) / sizeof(TelltaleView); i++)
	{
		if (i == enID)
		{
			if (ListContainSameID(enID) == false)
			{
				AddTelltaleToList(stTelltalePriorityArray[i]);
				return ;
			}
		}
	}
}


void TelltaleStrategy::ReleaseTelltale(enum WarningIDs enID)
{
	for (itTelltaleView it = m_lstTelltaleView.begin(); it != m_lstTelltaleView.end(); ++it)
	{
		if (enID == it->enTelltaleID)
		{
			m_lstTelltaleView.erase(it);
			return ;
		}
	}
}


uint16 TelltaleStrategy::GetFirstTelltaleID(void)
{
	if (m_lstTelltaleView.empty())
	{
		return InvalidTelltaleID;
	}
	else
	{
		return (uint16)m_lstTelltaleView.front().enTelltaleID;
	}
}


void TelltaleStrategy::AddTelltaleToList(TelltaleView stNewTelltale)
{

	for (itTelltaleView it = m_lstTelltaleView.begin(); it != m_lstTelltaleView.end(); ++it)
	{
		if (stNewTelltale.u16Priority <= it->u16Priority)
		{
			m_lstTelltaleView.insert(it, stNewTelltale);
			return;
		}
	}

	m_lstTelltaleView.push_back(stNewTelltale);
}