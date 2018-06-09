//+------------------------------------------------------------------+
//|                                                   Stochastic.mq4 |
//|                                http://www.goforexstrategies.com/ |
//|           Please see the website for entry and exit descriptions |
//+------------------------------------------------------------------+
#property link      "http://www.goforexstrategies.com/"
 
extern int magicNumber = 1234;
extern double lots = 0.1;
 
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

