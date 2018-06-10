//+------------------------------------------------------------------+
//|                                  Double-Stochastic-Crossover.mq4 |
//|                                http://www.goforexstrategies.com/ |
//|           Please see the website for entry and exit descriptions |
//+------------------------------------------------------------------+
#property link      "http://www.goforexstrategies.com/"

extern int magicNumber = 1234;
extern double lots = 0.1;

int slippage = 3;
double takeProfit = 0;
double stopLoss = 0;
int ticket;
int counter;
bool openOrder;
bool buySignal1,sellSignal1;
bool buySignal2,sellSignal2;

//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
{
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
   generateSignals();
   
   //monitor open trades
   for(counter=0;counter<OrdersTotal();counter++)   
   {
      OrderSelect(counter, SELECT_BY_POS, MODE_TRADES);     
      if (OrderMagicNumber() == magicNumber)
      {
         openOrder = true;
         if (OrderType() == OP_BUY && (sellSignal1 || sellSignal2))
         {
            closeBuyTrade();
            openOrder = false;
         }
         else if (OrderType() == OP_SELL && (buySignal1 || buySignal2))
         {
            closeSellTrade();
            openOrder = false;
         }
      }
   }
   
   //if there are no open orders, check for a signal
   if (!openOrder)
   {
      if (buySignal1 && buySignal2)
         placeBuy();
      else if (sellSignal1 && sellSignal2)
         placeSell();
   }   
   return(0);
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
//| generate a buy or sell signal
//+------------------------------------------------------------------+
void generateSignals()
{
   buySignal1 = false;
   sellSignal1 = false;
   buySignal2 = false;
   sellSignal2 = false;
   
   //K线值大于D线值，卖出，否则买入；两种周期震荡指标判断
   if (iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_MAIN,1) > iStochastic(NULL,0,5,3,3,MODE_SMA,0,MODE_SIGNAL,1))
      buySignal1 = true;
   else
      sellSignal1 = true;

   if (iStochastic(NULL,0,21,9,9,MODE_SMA,0,MODE_MAIN,1) > iStochastic(NULL,0,21,9,9,MODE_SMA,0,MODE_SIGNAL,1))
      buySignal2 = true;
   else
      sellSignal2 = true;
}
//+------------------------------------------------------------------+
//| close BUY trade
//+------------------------------------------------------------------+
void closeBuyTrade()
{
      RefreshRates();
      OrderClose(OrderTicket(),OrderLots(),Bid,slippage,Green);     
}
//+------------------------------------------------------------------+
//| close SELL trade
//+------------------------------------------------------------------+
void closeSellTrade()
{
      RefreshRates();
      OrderClose(OrderTicket(),OrderLots(),Ask,slippage,Red);  
}