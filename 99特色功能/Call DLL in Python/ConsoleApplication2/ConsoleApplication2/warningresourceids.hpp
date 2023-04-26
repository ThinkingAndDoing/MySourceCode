#ifndef WARNINGRESOURCEIDS_HPP
#define WARNINGRESOURCEIDS_HPP


#define DISABLE_WARNING_MODE


enum WarningMode
{
	WrnModeNone,
	Driving,
	Active,
	Convenience,
	Inactive,
	Abandoned
};

enum WarningIDs
{
//Telltales
    ABSLampTT = 0,
    ABSLampBlinkTT,
    BattChargeTT,
    BrakeRedLampTT,
    BrakeRedLampBlinkTT,
    BrakeRedLampUSTT,
    BrakeRedLampUSBlinkTT,
    BrakeYellowLampTT,
    BrakeYellowLampUSTT,
    BrakePadWearTT,
    BrakePadWearEUorUSTT,
    ESCLampTT,
    ESCLampBlinkTT,
    GenWarningTriTT,
    InforsignTT,
    AHBCErrLampTT,
    AHBCHiBeamTT,
    AHBCLowBeamTT,
    AHBCErrTT,
    HiBeamTT,
    PositionLightTT,
    PositionLightErrTT,
    LoBeamTT,
    RainSenTT,
    ParkBrakeTT,
    ParkBrakeBlinkTT,
    ParkBrakeUSTT,
    ParkBrakeUSBlinkTT,
    RearFogTT,
    ElectricalVehicleSystemErrorTT,
    EVReadyTT,
    SRSAirbagTT,
    SRSAirbagBlinkTT,
    TPMTT,
    TPMBlinkTT,
    TurnLeftTT,
    TurnRightTT,
    ForwardColWarnOFFTT,
    ForwardColWarnOFFBlinkTT,
    ForwardColWarnTT,
    ForwardColWarnBlinkTT,
    AEBErrorTT,
    SteerAssistFailTT,
    ChargeCablePlugTT,
    ChildLockActivateTT,
    ChildLockErrTT,
    TurnIndicatorWarnTT,
    NoTorqueAvailableTT,
    MaxSpeedReachTT,
    WiperFailureTT,
    BrakeLightFailureTT,
    HVBattWarnRedTT,
    HVBattWarnAmberTT,
    OpenDoorWarnTT,
    AVASErrorTT,
    HVLoBattLevelTT,
    HiBeamFaultTT,
    LoBeamFaultTT,
    AdjustHeadlampLevelErrTT,
    SeatBeltTT,
	AutoHoldTT,
	InvalidTelltaleID,//=61
//Warnings
	SteColLocFaiWrn,
	SteColLocTryagainWrn,
	SteColLocSerReqWrn,
	SteBloMoveAndTryWrn,
	RemoteImAndNoStartWrn,
	KeyLostSud,
	KeyLostWrn,
	KeyRmnIndSudWrn,
	BrakeFaiStopSafeWrn,
	ABSandESCserviceReqWrn,
	ABSandESCtempOffWrn,
	ESCserviceReqWrn,
	ESCtempOffWrn,
	TraContempOffWrn,
	BrakeSysServiceReqSysWrn,
	CurDriveModeResStabilityWrn,
	CheckBrakeFluWrn,
	ESCTrackWrn,
	ESCRaceWrn,
	FrontBrakeWearWrn,
	RearBrakeWearWrn,
	FrontBrakeWearIndWrn,
	RearBrakeWearIndWrn,
	BrakePedalcharWrn,
	BrakeSysServiceReqWrn,
	WiperSysErrWrn, //FunctionSaftyWarning-1
	RainSensorfaultServiceReqWrn,
	WasherFluLevelLoWrn,
	AutoBrakingActivatedWrn,
	LoVoltageTempReducedWrn,
	ChargefailureStopSafeWrn,
	BattService12VReqWrn,
	ParkBrakeNotReleaseWrn,
	ParkBrakeNotHoldWrn,
	ParkBrakeNotFullyReleaseWrn,
	ParkBrakeNotApplyWrn,
	PressBrakePedalParkWrn,
	ParkBrakeServiceReqAsilWrn,
	TempInterParkBrakeWrn,
	UseParkBrakeToReleaseWrn,
	ParkBrakeServiceReqWrn,
	ParkBrakeAutoApplyAdjustWrn,
	TurnOnIgnAndUseParkBrakeWrn,
	ParkBrakeRollerBenchWrn,
	ReleaseParkBrakeOrBeltAndDoorWrn,
	ParkBrakeOverheatWrn,
	EPBLockFailWrn,
	RemoteKeyBattLoWrn,
	HVBattStopImmeAndLeaveWrn,
	HVSystemSelfcheckWrn,
	PowSystemFaultNotDriWrn,
	PowSystemFaultStopSafeWrn,
	EdriSystemFaultStopSafeWrn,
	PowSystemFaultNotStartWrn,
	PowLimDriCareWrn,
	EdriSystemHarshBehavWrn,
	PowSystemFaultNotChargeWrn,
	PowSystemFaultWrn,
	HVBattFaultWrn,
	PowSystemFaultNotQuickChargeWrn,
	HomeSafeLightActiveWrn,
	FrontHiBeamFaultWrn,
	FrontLoBeamFaultWrn,
	RearPositionLightFaultWrn,
	FaultOnRearFogLightWrn,
	FrontOrRearLeftFaultWrn,
	FrontOrRearRightFaultWrn,
	FrontFogLightFaultWrn,
	ParkLightTurnLightClsdWrn,
	ParkLightTurnLightOpenedWrn,
	AFSSysFaultSerReqWrn,
	AdaptiveBendLightSerReqWrn,
	HeadLampFaultSerReqWrn,
	LeftLampEnableWrn,
	RightLampEnableWrn,
	VehicleStartPorNWrn,
	VehicleStartNeutralGearWrn,
	VehicleStartClutchPedalWrn,
	VehicleStartBrakePedalWrn,
	VehicleOffStartKnobWrn,
	VehicleOffStartButtonWrn,
	VehicleStartStartKnobWrn,
	VehicleStartStartButtonWrn,
	VehicleStartSysCheckWrn,
	VehicleTurnOffSelectPWrn,
	VehicleTurnOffStartKnobWrn,
	VehicleTurnOffStartButtonWrn,
	ChargeCableRemoveBeforeStartWrn,
	ChargeCableRemoveStartKnobWrn,
	ChargeCableRemoveStartButtonWrn,
	ChargeCableConnectRemoveWrn,
	VehiclePowDownWrn,
	BattLoChargeWrn,
	BattLoChargeSaveModeWrn,
	VehicleReadyToDriWrn,
	IgnitionOnWrn,
	EnterTowModeWrn,
	StartInProgressWrn,
	CrashModeWrn,
	FactoryModeWrn,
	FactoryStopModeWrn,
	TransportModeWrn,
	TransportStopModeWrn,
	NormalModeWrn,
	ChangeCarModeToDynoWrn,
	SafeFunctionDisableWrn,
	DynamometerChooseTypeWrn,
	ExitDynoModeWrn,
	SRSServiceUrgentWrn,
	BrkLightSysFaultWrn, //FunctionSaftyWarning-2
	DirIndcnMalfuctnWrn,//FunctionSaftyWarning-3
	NotiKeySharingWrn,
	CoolantSysWrn,
	EleDriveSysWrn,
	GearLvrRelsByBrkPedlWrn,
	GearLvrMovmtToManNotAllwdWrn,
	EngStrtNoPsblWrn,
	ChgOfVehMovmtDirNotPsblWrn,
	GearShiftSrvRqrdWrn,
	ManModActvdWrn,
	RetuenShifterToInitialStateWrn,
	ShiftToDOrMToAllowManualModWrn,
	StopPushingPButtonWrn,
	VehNotParkInfoWarnShifttoPWrn,
	VehNotParkInfoWarnOutofPWrn,
	SpdInterSud,
	SpdContiSud,
	LVsupplyAbnormalWrn,
	OldAutoHoldTT,//=190
	CentWhlInfoFailWrn,
	SteerWhlParkWarnTrueWrn,
	CentWhlAglReqReqWrn,
	SwipDoorDrvrAntiPinchSts1Wrn,
	SwipDoorPassAntiPinchSts1Wrn,
	SwipDoorLeReAntiPinchSts1Wrn,
	SwipDoorRiReAntiPinchSts1Wrn,
	PreConMetOverVehStdstillWrn,
	PreConMetOverFrntWhlStrWrn,
	PreConMetOverPitchRollOKWrn,
	SwipDrvrWarnEndNoSucWrn,
	SwipPassWarnIndEndNoSucWrn,
	SwipRiReWarnIndEndNotSucWrn,
	SwipLeReWarnIndEndNotSucWrn,
	SwipDrvrWarnIndFltngDoorWrn,
	SwipPassWarnIndFltngDoorWrn,
	SwipRiReWarnIndFltngDoorWrn,
	SwipLeReWarnIndFltngDoorWrn,
	SwipDrvrWarnIndDisDoorWrn,
	SwipPassWarnIndDisDoorWrn,
	SwipRiReWarnIndDisDoorWrn,
	SwipLeReWarnIndDisDoorWrn,
	SwipDoorDrvrOverheatWarn1Wrn,
	SwipDoorPassOverheatWarn1Wrn,
	SwipDoorRiReOverheatWarn1Wrn,
	SwipDoorLeReOverheatWrn,
	SwipDoorDrvrOverheatWarn2Wrn,
	SwipDoorPassOverheatWarn2Wrn,
	SwipDoorRiReOverheatWarn2Wrn,
	SwipDoorLeReOverheatWarn2Wrn,
	CentWhlRetnInfoFailWrn,
	SwipDoorRiBattLvlWarn1Wrn,
	SwipDoorLeBattLvlWarn1Wrn,
	SwipDoorDrvrSystErr1Wrn,
	SwipDoorPassSystErr1Wrn,
	SwipDoorRiReSystErr1Wrn,
	SwipDoorLeReSystErr1Wrn,
	SwipDoorDrvrNormSts3Wrn,
	SwipDoorPassNormSts3Wrn,
	SwipDoorRiReNormSts3Wrn,
	SwipDoorReLeNormSts3Wrn,
	SwipDoorDrvrNormSts2Wrn,
	SwipDoorPassNormSts2Wrn,
	SwipDoorRiReNormSts2Wrn,
	SwipDoorReLeNormSts2Wrn,
	DispMsgByVehHld2Wrn,
	DispMsgByVehHld3Wrn,
	DispMsgByVehHld4Wrn,
	BrkRelsWarnReqYesWrn,
	FallbackUnlatUsdWrn,
	SrvRmnWarning1Wrn,
	SrvRmnWarning2Wrn,
	SrvRmnWarning3Wrn,
	WarningID244,
	DoorOpnWrn,
    NumberOfWarnings
};



#endif
