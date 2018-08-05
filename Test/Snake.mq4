//+------------------------------------------------------------------+
//|                                                   Stochastic.mq4 |
//|                                http://www.goforexstrategies.com/ |
//|           Please see the website for entry and exit descriptions |
//+------------------------------------------------------------------+
#property link      "http://www.goforexstrategies.com/"

extern int magicNumber = 142536;
extern double lots = 0.1;

int MainTrend = 0; //-1表示下降，0表示横盘整理，1表示上升
int MainTimeframe = 15; //主周期为15分钟周期 PERIOD_M15
int SubTimeframe = 1; //子周期为1分钟周期 PERIOD_M1
int MinimalValue = 1; //up, down
int MaximalValue = 1; //up, down
int Deviation = 10; //将误差设置为10个点，如果相差10个点，则可认为已经反向。

//1，判断当前主周期趋势是上升，还是下降，或者横盘整理
//2，假如当前主趋势是下降，判断当前值是否是极小值，如果是，那么继续等待，如果不是，计算极小值。
//3，寻找极大值，在极大值处卖空。

int stopLoss = 0;
int slippage = 3;
double takeProfit = 0;
int ticket;
int counter;
datetime previousSignal = 0;
bool openOrder;
bool buySignal,sellSignal;
bool buyGate;
bool sellGate;
 
//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
{
   buyGate = false;
   sellGate = false;
   return(0);
}
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit()
{
   return(0);
}
//+------------------------------------------------------------------+
//| expert start function                                            |
//+------------------------------------------------------------------+
int start()
{
   openOrder = false;
   
   //monitor open trades
   for(counter=0;counter<OrdersTotal();counter++)   
   {
      OrderSelect(counter, SELECT_BY_POS, MODE_TRADES);     
      if (OrderMagicNumber() == magicNumber)
      {
         openOrder = true;
         if (OrderType() == OP_BUY && iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) >= 80)
         {
            closeBuyTrade();
         }
         else if (OrderType() == OP_SELL && iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) <= 20)
         {
            closeSellTrade();
         }
      }
   }
   
   //if there are no open orders, check for a signal
   if (!openOrder &&
       Time[0] != previousSignal)
   {
      generateSignals();
      if (buySignal)
         placeBuy();
      else if (sellSignal)
         placeSell();
      previousSignal = Time[0];
   }   
   return(0);
}

//+------------------------------------------------------------------+
//| ask main trend                                                   |
//+------------------------------------------------------------------+
void askMainTrend()
{
	int Trend = 0; // -1下降趋势，0横盘整理，1上升趋势
	double LEma;
	int ADXTrend = 0;  //1 = buy, 2 = sell
	
	RefreshRates();
	LEma = iMA(Symbol(), MainTimeframe, 0, 0, MODE_EMA, PRICE_MEDIAN, 0);
   
	//ADX Main Value
	double ADXMain = 0;
	ADXMain = iADX(Symbol(),0,ADX,PRICE_LOW,MODE_MAIN,0);
	double ADXMain1 = 0;
	ADXMain1 = iADX(Symbol(),0,ADX,PRICE_LOW,MODE_MAIN,1);
   
	//end ADX Main Value
	if (ADXMinus < ADXPlus && ADXMain > ADXMain1 && ADXMain1>20 && ADXMain1<40)
	{
		Trend = 1;
	}
	else if (ADXMinus > ADXPlus && ADXMain > ADXMain1 && ADXMain1>20 && ADXMain1<40) 
	{
		Trend = 2;
	}
	//end ADX
	return (Trend);
}
//+------------------------------------------------------------------+
//| place BUY trade                                                  |
//+------------------------------------------------------------------+
void placeBuy()
{
   RefreshRates();            
   ticket=OrderSend(Symbol(),OP_BUY,lots,Ask,slippage,stopLoss,takeProfit,"buy",magicNumber,0,Green);  
   if(ticket<0)
   {
      Print("BUY failed with error #",GetLastError()," at ",Ask);
      return;
   }
}
//+------------------------------------------------------------------+
//| place SELL trade                                                 |
//+------------------------------------------------------------------+
void placeSell()
{
   RefreshRates();            
   ticket=OrderSend(Symbol(),OP_SELL,lots,Bid,slippage,stopLoss,takeProfit,"sell",magicNumber,0,Red);  
   if(ticket<0)
   {
      Print("SELL failed with error #",GetLastError()," at ",Bid);
      return;
   }
}
//+------------------------------------------------------------------+
//| generate a buy & sell prices
//+------------------------------------------------------------------+
void generateSignals()
{
   buySignal = false;
   sellSignal = false;
   
 
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) <= 10)
      buyGate = true;
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) >= 20 && 
       buyGate == true &&
       iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) < 80)
   {
      buySignal = true;
      buyGate = false;
      return;
   }
      
      
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) >= 90)
      sellGate = true;
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) <= 80 && 
       sellGate == true &&
       iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) > 20)
   {
      sellSignal = true;
      sellGate = false;
      return;
   }
         
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) > 20 &&
       iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) < 80)
   {
      buyGate = false;
      sellGate = false;
   }
}
//+------------------------------------------------------------------+
//| calculate the trailing stop for a BUY trade
//+------------------------------------------------------------------+
void closeBuyTrade()
{
      RefreshRates();
      OrderClose(OrderTicket(),OrderLots(),Bid,slippage,Green);     
}
//+------------------------------------------------------------------+
//| calculate the trailing stop for a SELL trade
//+------------------------------------------------------------------+
void closeSellTrade()
{
      RefreshRates();
      OrderClose(OrderTicket(),OrderLots(),Ask,slippage,Red);  
}

