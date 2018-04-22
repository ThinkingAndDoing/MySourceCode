/*
   Generated by EX4-TO-MQ4 decompiler V4.0.224.1 []
   Website: http://purebeam.biz
   E-mail : purebeam@gmail.com

*/
#property copyright "CaspianEA.com, Ehsan Parsa"
#property link      "http://www.caspianea.com"

//OrdersTotal() 只包括未平仓单和挂单
//OrderSelect() 选择一个单
//OrderSymbol() 获取当前选择的单的符号名
//Symbol() 获取当前图表的符号
//OrderMagicNumber() 魔法号，用作区分手动开仓和自动开仓的单，以及不同EA开的单
//OrderType() 买单，卖单，挂单等
//OrderTicket()	当前选中的定单的编号 
//OrderClose()	平仓操作
//OrderLots()	获取当前被选择的单的手数
//OrderOpenPrice()  当前选中的定单的建仓价
//NormalizeDouble()	计算止损、止盈、挂单建仓价时，必须用本函数处理过的数字  


#import "CaspianEA.CHF.dll"
   void calculateIndi(double& a0[], double& a1[], double& a2[]);
   void setOrder(int a0, int& a1[], double& a2[], double& a3[], int& a4[], int a5);
   void setHarga(double a0, double a1, double a2, double a3, int a4, int a5, double a6, double a7, double a8);
   void setFilter(int a0, int a1);
   void setBuy(int a0);
   void setSell(int a0);
   void setBuy2(int a0);
   void setSell2(int a0);
   void updateFilter();
   double executeOrder(int a0);
   double TrailingStop(int a0, double a1, double a2);
   int getTime();
   int GetCloseCommand(double a0, double a1, double a2, double a3, int a4);
   int GetTiket1();
   int GetTiket2();
   int GetTiket3();
   int GetTiket4();
#import


extern string PartOne = "Trading Configurations";
extern double CaspianFactor = 3.0;  //3点目标值，取了名为里海因子，只是个名字而已
extern bool BuyPositions = TRUE; 
extern bool SellPositions = TRUE; 
extern int MaxTrades = 3; //最多开3单
extern double TakeProfit = 10.0;	// 止盈
extern int StopLoss = 50;	// 止损
extern bool UseHedging = TRUE;
extern int MagicNumber = 777;
extern int Slippage = 3;
extern string PartTwo = "Money Management Configurations";
extern bool UseMoneyManagement = TRUE;
extern int Risk = 50;	//风险指数
extern double Lots = 0.1;	// 交易手数
extern int LotsDigit = 1;
extern string PartThree = "Time Configurations";
extern int StartHour = 23;	//起始交易时间，澳大利亚与中国的时差是5小时，对应的中国时间是凌晨4点
extern int EndHour = 2;	//终止交易时间，澳大利亚与中国的时差是5小时，对应的中国时间是早上7点
string gs_unused_172 = "CaspianEA.CHF";
bool gi_180 = TRUE;
bool gi_184 = TRUE;
int gi_188 = 100;
bool gi_192 = TRUE;
double gd_196 = 250.0;
double gd_204 = 1000.0;
bool gi_212 = FALSE;
double gd_216 = 2.0;
int gi_224 = 3;
double gd_228 = 0.0;
int g_count_236 = 0;
double gd_unused_240 = 0.0;
double gd_248 = 0.0;
double g_point_256 = 0.01;  //每单位（点）的价格
double gd_264 = 0.0;
int gi_272 = 0;
int gi_unused_276 = 0;
int gi_unused_280 = 0;
double gda_284[101];
double gda_288[101];
double gda_292[101];
int gi_296 = 0;
int gi_unused_300 = 0;
int gi_unused_304 = 0;
int gia_308[4];
int gia_312[4];
int gia_316[4];
int gia_320[4];
double gda_324[4];
double gda_328[4];
double gda_332[4];
double gda_336[4];
double g_price_340 = 0.0;
double g_price_348 = 0.0;
int gi_356 = D'01.06.2009 02:00';
int gi_360;
int gi_364;
int gi_368;
int gi_372;
int gi_376;
int gi_380;
int gi_384;
int gi_388 = 0;
int gi_392;
int gi_396;
int gi_400;
int gi_404;
int gi_408;
int gi_412;
int gi_416;
int gi_420 = 0;
int gi_424;
int gi_428;
int gi_432;
int gi_436 = 0;
int gi_440;
int gi_444;
int gi_448;
int gi_452 = 0;
int gi_456;
int gi_460;
int gi_464;
int gi_468 = 0;

int init() {
   ArrayInitialize(gda_284, 0);
   ArrayInitialize(gda_288, 0);
   ArrayInitialize(gda_292, 0);
   gi_272 = Bars - 1;
   if (BuyPositions) setBuy(1);
   else setBuy(0);
   if (SellPositions) setSell(1);
   else setSell(0);
   setBuy2(1);
   setSell2(1);
   setFilter(0, MaxTrades);
   gi_296 = getTime();
   return (0);
}

int deinit() {
   return (0);
}

int start() {
   int l_acc_number_0;
   int l_period_12;
   double ld_16;
   double ld_24;
   double l_irsi_32;
   double l_icustom_40;
   double l_ima_48;
   double l_icustom_56;
   int li_72;
   double l_icustom_76;
   double l_icustom_84;
   double ld_96;
   int l_ticket_104;
   double ld_108;
   double ld_116;
   if (TimeCurrent() <= gi_356) return (-1);
   gi_224 = EndHour + 1;
   if (gi_224 > 24) gi_224 -= 24;
   if (Digits == 3) {
      g_point_256 = 0.01;
      gd_248 = MarketInfo(Symbol(), MODE_SPREAD) / 10.0;
      gd_264 = MarketInfo(Symbol(), MODE_STOPLEVEL) / 10.0;
   } else {
      if (Digits == 5) {
         g_point_256 = 0.0001;
         gd_248 = MarketInfo(Symbol(), MODE_SPREAD) / 10.0;
         gd_264 = MarketInfo(Symbol(), MODE_STOPLEVEL) / 10.0;
      } else {
         g_point_256 = Point;
         gd_248 = MarketInfo(Symbol(), MODE_SPREAD);
         gd_264 = MarketInfo(Symbol(), MODE_STOPLEVEL);
      }
   }
   if (gi_212 && gd_216 < gd_248) gd_248 = gd_216;
   if (GetLastError() > 1/* NO_RESULT */) Sleep(1000);
   if (MaxTrades > 4) MaxTrades = 4;
   double l_iwpr_4 = iWPR(Symbol(), PERIOD_M1, 20, 0);
   if (Bars >= 101) {
      l_period_12 = 10.0 * NormalizeDouble(CaspianFactor, 1);
      ld_16 = iATR(Symbol(), PERIOD_D1, 5, 0) / g_point_256;
      ld_24 = iATR(Symbol(), 0, l_period_12, 0) / g_point_256;
      l_irsi_32 = iRSI(Symbol(), 0, 12, PRICE_CLOSE, 0);
      l_icustom_40 = iCustom(Symbol(), 0, "EFF", 0, 10, 5, 5, 0, 0, 0, 0);
      l_ima_48 = iMA(Symbol(), 0, 7, 0, MODE_SMA, PRICE_MEDIAN, 0);
      l_icustom_56 = iCustom(Symbol(), 0, "Channel", 14, 0, 0);
      if (gi_272 != Bars) {
         g_count_236 = 0;
         setFilter(0, MaxTrades);
         if (gi_192) {
            for (int li_64 = 0; li_64 < 101; li_64++) {
               gda_284[li_64] = iMA(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, li_64);
               gda_288[li_64] = iStdDev(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, li_64);
               gda_292[li_64] = iCustom(Symbol(), 0, "ATR", l_period_12, 0, 0, li_64);
            }
         } else {
            for (int li_68 = 0; li_68 < 101; li_68++) {
               gda_284[li_68] = iMA(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, li_68);
               gda_288[li_68] = iStdDev(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, li_68);
               gda_292[li_68] = iATR(Symbol(), 0, l_period_12, li_68);
            }
         }
         gi_272 = Bars;
      }
      if (StopLoss <= 0) Comment(" CaspianEA.CHF is not working, your stoploss is less or equal to 0");
      else {
         CloseLossOrder(MagicNumber, OP_BUY, -1 * StopLoss);
         CloseLossOrder(MagicNumber, OP_SELL, -1 * StopLoss);
         if (gi_180) {
            if (g_price_340 > 0.0 && Bid < g_price_340) {
               ForceCloseAll(MagicNumber, OP_BUY, Green);
               g_price_340 = 0;
            }
            if (g_price_348 > 0.0 && Ask > g_price_348) {
               ForceCloseAll(MagicNumber, OP_SELL, Green);
               g_price_348 = 0;
            }
         }
         mycomment();
         if (gd_228 > 0.0 && AccountEquity() >= gd_228) {
            ForceCloseAll(MagicNumber, OP_BUY, Green);
            ForceCloseAll(MagicNumber, OP_SELL, Green);
            setSell(0);
            setBuy(0);
         }
         li_72 = 0;
         l_icustom_76 = iCustom(Symbol(), 0, "MarketMovement", 5, 50, 0, 1);
         l_icustom_84 = iCustom(Symbol(), 0, "MarketMovement", 5, 50, 0, 0);
         oneStopLoop();
         li_72 = GetCloseCommand(High[1], Low[1], l_icustom_76, l_icustom_84, Tradetime());
         switch (li_72) {
         case 0: break;
         case 1:
            gi_360 += CloseByTiket(1);
            break;
         case 2:
            gi_392 += CloseByTiket(1);
            break;
         case 11:
            ForceCloseAll(MagicNumber, OP_SELL, DarkGreen);
            gi_364++;
            break;
         case 22:
            ForceCloseAll(MagicNumber, OP_BUY, DarkGreen);
            gi_396++;
            break;
         case 111:
            ForceCloseAll(MagicNumber, OP_SELL, Indigo);
            gi_368++;
            break;
         case 110:
            gi_384 += CloseByTiket(1);
            break;
         case 222:
            ForceCloseAll(MagicNumber, OP_BUY, Indigo);
            gi_400++;
            break;
         case 220:
            gi_416 += CloseByTiket(1);
            break;
         case 2222:
            ForceCloseAll(MagicNumber, OP_BUY, Maroon);
            gi_404++;
            break;
         case 1111:
            ForceCloseAll(MagicNumber, OP_SELL, Maroon);
            gi_372++;
            break;
         case 22222:
            gi_408 += CloseByTiket(1);
            break;
         case 22220:
            ForceCloseAll(MagicNumber, OP_BUY, Violet);
            gi_420++;
            break;
         case 11111:
            gi_376 += CloseByTiket(1);
            break;
         case 11110:
            ForceCloseAll(MagicNumber, OP_SELL, Violet);
            gi_388++;
            break;
         case 111111:
            ForceCloseAll(MagicNumber, OP_SELL, Aqua);
            gi_380++;
            break;
         case 222222:
            ForceCloseAll(MagicNumber, OP_BUY, Aqua);
            gi_412++;
            break;
         case 33:
            gi_424 += CloseByTiket(1);
            break;
         case 44:
            gi_428 += CloseByTiket(1);
            break;
         case 55:
            gi_432 += CloseByTiket(1);
            break;
         case 66:
            gi_436 += CloseByTiket(1);
            break;
         case 333:
            gi_440 += CloseByTiket(1);
            break;
         case 444:
            gi_444 += CloseByTiket(1);
            break;
         case 555:
            gi_448 += CloseByTiket(1);
            break;
         case 666:
            gi_452 += CloseByTiket(1);
            break;
         case 3333:
            ForceCloseAll(MagicNumber, OP_BUY, White);
            gi_456++;
            break;
         case 4444:
            gi_460 += CloseByTiket(1);
            break;
         case 5555:
            ForceCloseAll(MagicNumber, OP_BUY, Snow);
            gi_464++;
            break;
         case 6666:
            gi_468 += CloseByTiket(1);
         }
         if (Hour() == EndHour) {
            if (Minute() > 30) {
               if (TotalOrder(MagicNumber, OP_BUY) < 1) setBuy(0);
               if (TotalOrder(MagicNumber, OP_SELL) < 1) setSell(0);
            }
         }
         if (Tradetime() == 0) {
            setBuy(1);
            setSell(1);
            setBuy2(1);
            setSell2(1);
            if (Close[0] > iMA(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, 0) && l_iwpr_4 < -80.0 && TotalProfit(MagicNumber, OP_SELL) >= -5.0) CloseProfitOrder(MagicNumber, OP_SELL, -5, 6 * Period(), 30000000);
            if (Close[0] < iMA(Symbol(), 0, l_period_12, 0, MODE_SMA, PRICE_MEDIAN, 0) && l_iwpr_4 > -20.0 && TotalProfit(MagicNumber, OP_BUY) >= -5.0) CloseProfitOrder(MagicNumber, OP_BUY, -5, 6 * Period(), 30000000);
         } else updateFilter();
         ld_96 = 0;
         if (gi_180) {
            ld_96 = TrailingStop(0, l_icustom_76, l_icustom_84);
            if (ld_96 > 0.0) Trail(MagicNumber, OP_BUY, ld_96);
            ld_96 = TrailingStop(1, l_icustom_76, l_icustom_84);
            if (ld_96 > 0.0) Trail(MagicNumber, OP_SELL, ld_96);
         }
         if (Tradetime() == 1) {
            if (AccountFreeMarginCheck(Symbol(), OP_BUY, GetLots(0)) <= 0.0 || GetLastError() == 134/* NOT_ENOUGH_MONEY */) {
               Print("Not Enough Money ");
               return (0);
            }
            if (ld_16 >= gd_196) return;
            l_ticket_104 = 0;
            ld_108 = 0;
            oneStopLoop();
            ld_108 = executeOrder(1);
            if (ld_108 > 0.0 && g_count_236 < MaxTrades && TotalOrder(MagicNumber, OP_SELL) < MaxTrades) {
               if (!UseHedging && TotalOrder(MagicNumber, OP_BUY) > 0) return;
               l_ticket_104 = OrderSend(Symbol(), OP_SELL, GetLots(1), Bid, Slippage, 0, 0, "CaspianEA.CHF" + Symbol(), MagicNumber, 0, Red);
               Sleep(3000);
               if (l_ticket_104 > 0 && StopLoss >= gd_264) {
                  if (OrderSelect(l_ticket_104, SELECT_BY_TICKET, MODE_TRADES)) OrderModify(OrderTicket(), OrderOpenPrice(), OrderOpenPrice() + StopLoss * g_point_256, OrderTakeProfit(), 0, Red);
                  g_price_348 = 0;
                  g_count_236++;
                  setFilter(g_count_236, MaxTrades);
                  setBuy2(1);
                  PlaySound("alert.wav");
                  return;
               }
            }
            ld_116 = 0;
            oneStopLoop();
            ld_116 = executeOrder(0);
            if (ld_116 > 0.0 && g_count_236 < MaxTrades && TotalOrder(MagicNumber, OP_BUY) < MaxTrades) {
               if (!UseHedging && TotalOrder(MagicNumber, OP_SELL) > 0) return;
               l_ticket_104 = OrderSend(Symbol(), OP_BUY, GetLots(0), Ask, Slippage, 0, 0, "CaspianEA.CHF" + Symbol(), MagicNumber, 0, Blue);
               Sleep(3000);
               if (l_ticket_104 > 0 && StopLoss >= gd_264) {
                  if (OrderSelect(l_ticket_104, SELECT_BY_TICKET, MODE_TRADES)) OrderModify(OrderTicket(), OrderOpenPrice(), OrderOpenPrice() - StopLoss * g_point_256, OrderTakeProfit(), 0, Red);
                  g_price_340 = 0;
                  g_count_236++;
                  setFilter(g_count_236, MaxTrades);
                  setSell2(1);
                  PlaySound("alert.wav");
               }
            }
         }
      }
   }
   return (0);
}

//强制平仓所有卖单或者买单
void ForceCloseAll(int a_magic_0, int a_cmd_4, color a_color_8) {
   for (int l_pos_12 = OrdersTotal() - 1; l_pos_12 >= 0; l_pos_12--) {
      OrderSelect(l_pos_12, SELECT_BY_POS, MODE_TRADES);
      if (OrderSymbol() == Symbol() && OrderMagicNumber() == a_magic_0) {
         if (OrderType() == a_cmd_4) {
            OrderClose(OrderTicket(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), 3, a_color_8);
            Sleep(1000);
         }
      }
   }
}

//判断当前时间是否为交易时间
int Tradetime() {
   bool li_ret_0 = FALSE;
   if (StartHour > EndHour)
      if (Hour() <= EndHour || Hour() >= StartHour) li_ret_0 = TRUE;
   if (StartHour < EndHour)
      if (Hour() >= StartHour && Hour() <= EndHour) li_ret_0 = TRUE;
   if (StartHour == EndHour)
      if (Hour() == StartHour) li_ret_0 = TRUE;
   if (DayOfWeek() >= 5 && Hour() > 18) li_ret_0 = FALSE;
   if (DayOfWeek() == 1 && Hour() < gi_224) li_ret_0 = FALSE;
   if (DayOfYear() < 7) li_ret_0 = FALSE;
   if (Month() == 12 && Day() > 20) li_ret_0 = FALSE;
   return (li_ret_0);
}

double GetLots(int ai_0) {
   double ld_ret_4;
   int li_52;
   double l_lotsize_44 = MarketInfo(Symbol(), MODE_LOTSIZE);
   double ld_12 = NormalizeDouble(MarketInfo(Symbol(), MODE_LOTSTEP), 2);
   double ld_20 = NormalizeDouble(MarketInfo(Symbol(), MODE_MARGINREQUIRED), 4);
   double ld_28 = 100.0 * (ld_20 + 5.0);
   if (gi_188 > 100) gi_188 = 100;
   double ld_56 = AccountFreeMargin() * (gi_188 / 100);
   if (LotsDigit == 0) {
      if (ld_12 < 0.1) li_52 = 2;
      else li_52 = 1;
      LotsDigit = li_52;
   }
   if (UseMoneyManagement == TRUE) {
      ld_ret_4 = NormalizeDouble(10.0 * (ld_56 * Risk) / l_lotsize_44, LotsDigit);
      if (gi_184) ld_ret_4 = ld_ret_4 * (10 * (TotalOrder(MagicNumber, ai_0) + 1)) / 100.0;
      else ld_ret_4 /= MaxTrades;
   } else ld_ret_4 = Lots;
   double ld_36 = NormalizeDouble(MarketInfo(Symbol(), MODE_MINLOT), LotsDigit);
   double ld_64 = NormalizeDouble(MarketInfo(Symbol(), MODE_MAXLOT), LotsDigit);
   ld_ret_4 -= MathMod(ld_ret_4, MarketInfo(Symbol(), MODE_LOTSTEP));
   if (ld_ret_4 < ld_36) ld_ret_4 = ld_36;
   if (ld_ret_4 > ld_64) ld_ret_4 = ld_64;
   return (ld_ret_4);
}

//关闭盈利点数超过ai_8的单子
int CloseProfitOrder(int a_magic_0, int a_cmd_4, int ai_8, double ad_12, double ad_20) {
   int li_40;
   bool l_ord_close_28 = FALSE;
   int li_unused_32 = 0;
   for (int l_pos_36 = OrdersTotal() - 1; l_pos_36 >= 0; l_pos_36--) {
      li_40 = 0;
      if (OrderSelect(l_pos_36, SELECT_BY_POS, MODE_TRADES)) {
         if (OrderType() == a_cmd_4 && OrderMagicNumber() == a_magic_0 && OrderSymbol() == Symbol()) {
            if (OrderType() == OP_BUY) li_40 = (OrderClosePrice() - OrderOpenPrice()) / g_point_256;
            if (OrderType() == OP_SELL) li_40 = (OrderOpenPrice() - OrderClosePrice()) / g_point_256;
            if (li_40 >= ai_8 && TimeCurrent() - OrderOpenTime() >= 60.0 * ad_12 && TimeCurrent() - OrderOpenTime() <= 60.0 * ad_20) l_ord_close_28 = OrderClose(OrderTicket(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), 3, CLR_NONE);
         }
      }
   }
   return (l_ord_close_28);
}

//关闭亏损超过ai_8的单子
int CloseLossOrder(int a_magic_0, int a_cmd_4, int ai_8) {
   bool l_ord_close_12 = FALSE;
   int li_unused_16 = 0;
   int li_20 = 0;
   for (int l_pos_24 = OrdersTotal() - 1; l_pos_24 >= 0; l_pos_24--) {
      if (OrderSelect(l_pos_24, SELECT_BY_POS, MODE_TRADES)) {
         if (OrderType() == a_cmd_4 && OrderMagicNumber() == a_magic_0 && OrderSymbol() == Symbol()) {
            if (OrderType() == OP_BUY) li_20 = (OrderClosePrice() - OrderOpenPrice()) / g_point_256;
            if (OrderType() == OP_SELL) li_20 = (OrderOpenPrice() - OrderClosePrice()) / g_point_256;
            if (li_20 <= ai_8) l_ord_close_12 = OrderClose(OrderTicket(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), 3, CLR_NONE);
         }
      }
   }
   return (l_ord_close_12);
}

//计算当前EA所开的全部单子数量
int TotalOrder(int a_magic_0, int a_cmd_4) {
   int l_count_8 = 0;
   for (int l_pos_12 = OrdersTotal() - 1; l_pos_12 >= 0; l_pos_12--) {
      OrderSelect(l_pos_12, SELECT_BY_POS, MODE_TRADES);
      if (OrderSymbol() == Symbol() && OrderMagicNumber() == a_magic_0)
         if (a_cmd_4 == OrderType()) l_count_8++;
   }
   return (l_count_8);
}

void Trail(int a_magic_0, int a_cmd_4, double a_price_8) {
   for (int l_pos_16 = OrdersTotal() - 1; l_pos_16 >= 0; l_pos_16--) {
      OrderSelect(l_pos_16, SELECT_BY_POS, MODE_TRADES);
      if (OrderSymbol() == Symbol() && OrderMagicNumber() == a_magic_0 && OrderType() == a_cmd_4) {
         if (a_cmd_4 == OP_BUY) {
            if (NormalizeDouble(OrderStopLoss(), Digits) < NormalizeDouble(a_price_8, Digits)) {
               OrderModify(OrderTicket(), OrderOpenPrice(), a_price_8, OrderTakeProfit(), 0, Gold);
               g_price_340 = a_price_8;
            }
            Sleep(1000);
         }
         if (a_cmd_4 == OP_SELL) {
            if (NormalizeDouble(OrderStopLoss(), Digits) > NormalizeDouble(a_price_8, Digits) || OrderStopLoss() == 0.0) {
               OrderModify(OrderTicket(), OrderOpenPrice(), a_price_8, OrderTakeProfit(), 0, Gold);
               g_price_348 = a_price_8;
            }
            Sleep(1000);
         }
      }
   }
}

void oneStopLoop() {
   int l_count_0 = 0;
   ArrayInitialize(gia_312, 0);
   ArrayInitialize(gia_316, 0);
   ArrayInitialize(gda_332, 0);
   ArrayInitialize(gda_336, 0);
   ArrayInitialize(gia_308, 0);
   ArrayInitialize(gda_328, 0);
   ArrayInitialize(gda_324, 0);
   ArrayInitialize(gia_320, 0);
   int l_count_4 = 0;
   int l_count_8 = 0;
   int li_unused_12 = -1;
   int l_pos_16 = 0;
   double ld_unused_20 = 0;
   double ld_unused_28 = 0;
   double ld_unused_36 = 0;
   double ld_unused_44 = 0;
   bool li_52 = FALSE;
   bool li_56 = TRUE;
   int l_period_60 = 10.0 * NormalizeDouble(CaspianFactor, 1);
   for (l_pos_16 = OrdersTotal() - 1; l_pos_16 >= 0; l_pos_16--) {
      OrderSelect(l_pos_16, SELECT_BY_POS, MODE_TRADES);
      if (OrderSymbol() == Symbol() && OrderMagicNumber() == MagicNumber) {
         l_count_8++;
         if (OrderType() == OP_BUY) {
            if (l_count_0 > 3) continue;
            l_count_0++;
            gia_312[l_count_0 - 1] = OrderTicket();
            gda_336[l_count_0 - 1] = OrderOpenPrice();
            gda_332[l_count_0 - 1] = OrderClosePrice();
            gia_308[l_count_0 - 1] = OrderOpenTime();
         }
         if (OrderType() == OP_SELL) {
            if (l_count_4 <= 3) {
               l_count_4++;
               gia_316[l_count_4 - 1] = OrderTicket();
               gda_324[l_count_4 - 1] = OrderOpenPrice();
               gda_328[l_count_4 - 1] = OrderClosePrice();
               gia_320[l_count_4 - 1] = OrderOpenTime();
            }
         }
      }
   }
   setOrder(li_56, gia_316, gda_324, gda_328, gia_320, l_count_4);
   setOrder(li_52, gia_312, gda_336, gda_332, gia_308, l_count_0);
   gda_284[0] = iMA(Symbol(), 0, l_period_60, 0, MODE_SMA, PRICE_MEDIAN, 0);
   gda_288[0] = iStdDev(Symbol(), 0, l_period_60, 0, MODE_SMA, PRICE_MEDIAN, 0);
   if (gi_192) gda_292[0] = iCustom(Symbol(), 0, "ATR", l_period_60, 0, 0, 0);
   else gda_292[0] = iATR(Symbol(), 0, l_period_60, 0);
   setHarga(Bid, Ask, gd_248, g_point_256, TimeCurrent(), Period(), iWPR(Symbol(), PERIOD_M1, l_period_60, 0), gd_204, TakeProfit);
   calculateIndi(gda_284, gda_288, gda_292);
}

int CloseByTiket(int ai_unused_0) {
   int l_ord_close_4;
   int l_ord_close_8;
   int l_ord_close_12;
   int l_ord_close_16 = 0;
   if (OrderSelect(GetTiket1(), SELECT_BY_TICKET, MODE_TRADES))
      if (OrderMagicNumber() == MagicNumber && OrderSymbol() == Symbol()) l_ord_close_4 = OrderClose(GetTiket1(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), Slippage, CLR_NONE);
   if (OrderSelect(GetTiket2(), SELECT_BY_TICKET, MODE_TRADES))
      if (OrderMagicNumber() == MagicNumber && OrderSymbol() == Symbol()) l_ord_close_8 = OrderClose(GetTiket2(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), Slippage, CLR_NONE);
   if (OrderSelect(GetTiket3(), SELECT_BY_TICKET, MODE_TRADES))
      if (OrderMagicNumber() == MagicNumber && OrderSymbol() == Symbol()) l_ord_close_12 = OrderClose(GetTiket3(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), Slippage, CLR_NONE);
   if (OrderSelect(GetTiket4(), SELECT_BY_TICKET, MODE_TRADES))
      if (OrderMagicNumber() == MagicNumber && OrderSymbol() == Symbol()) l_ord_close_16 = OrderClose(GetTiket4(), OrderLots(), NormalizeDouble(OrderClosePrice(), Digits), Slippage, CLR_NONE);
   return (l_ord_close_4 + l_ord_close_8 + l_ord_close_12 + l_ord_close_16);
}

//在屏幕左上角输出文字
void mycomment() {
   string ls_0 = "\n" 
   + "    CaspianEA.CHF V2.1" + " \n" + " \n" + "   *******************" + " \n" + "    Current Time:     " + TimeToStr(TimeCurrent(), TIME_MINUTES) + " \n" + " \n" + "    Working Hours:" + "   Start: " + StartHour + " \n" + "                           " + " End: " + EndHour + " \n" + " \n" + "   *******************" + " \n" + "    Spread:  " + DoubleToStr(gd_248, 2) + " \n" + "    Balance: " + DoubleToStr(AccountBalance(), 2) + " \n" + "    Equity:  " + DoubleToStr(AccountEquity(), 2);
   Comment(ls_0);
}

//统计当前EA所有买单或者卖单的收益
double TotalProfit(int a_magic_0, int a_cmd_4) {
   double ld_ret_8 = 0;
   for (int l_pos_24 = OrdersTotal() - 1; l_pos_24 >= 0; l_pos_24--) {
      OrderSelect(l_pos_24, SELECT_BY_POS, MODE_TRADES);
      if (OrderSymbol() == Symbol() && OrderMagicNumber() == a_magic_0) {
         if (a_cmd_4 == OP_BUY && a_cmd_4 == OrderType()) ld_ret_8 += (OrderClosePrice() - OrderOpenPrice()) / g_point_256;
         if (a_cmd_4 == OP_SELL && a_cmd_4 == OrderType()) ld_ret_8 += (OrderOpenPrice() - OrderClosePrice()) / g_point_256;
      }
   }
   return (ld_ret_8);
}