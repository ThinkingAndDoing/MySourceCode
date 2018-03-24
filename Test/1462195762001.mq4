//+----------------------------------------------------------------------------------------------+
//|本EA具有自动计算开单和自动计算平仓，大部分内容都已经汉化，程序内容简单明了，非常简练实用。    +
//|程序核心已经具备资金管理、双止盈、单止损、时间控制、手数控制、盈利自动增加控制、秒获利平仓、  +
//|快速做单快速盈利功能，程序简练，简洁有效。    开发人：廉峰   QQ:389911138  电话：13325074595  +
//|使用说明：本ea用在固定点差平台最好，点差是1的更好，在波动不大比较稳定的时候做单盈利很好的，   +
//|美元代表你的资金基数，波动就是滑点，开始就是时间开始，资管就是资金最少多少就不开单了，在这里  +
//|没有使用止盈，用了更先进的止盈更快更好。大家使用一定先模拟再实盘，充分掌握了原理后再实盘，    +
//|实盘有风险，投资需谨慎，建议大家先开美分户测试再实盘，不要赌!                                 +
//+----------------------------------------------------------------------------------------------+
extern double    美元 = 2000;
extern double    止损 = 6;
extern double    止盈 = 888;
extern double    开始 = 0;
extern double    结束 = 24;
extern double    波动 = 3;
extern double    飞点 = 2;
extern    int    获利 = 10.0;
extern    int    资管 = 150;
extern double    A, B; 
//-----------------------EA主程序----------------------------------------------------------------+
int start()
{
	A=Ask;//如果变量Ask没有显性初始化，其值可为任何值。
	B=Bid; 
	if(AccountBalance()>资管&&TimeHour(TimeCurrent())>=开始&&TimeHour(TimeCurrent())<结束&&开始<结束)
	{   
		if (Ask-A>=波动*Point) 
		{
			OrderSend(Symbol(),OP_SELL,GetLots(),Bid,飞点,Bid+止损*Point,Bid-止盈*Point,"",0,CLR_NONE,Green);
		} 
		if (B-Bid>=波动*Point) 
		{
			OrderSend(Symbol(),OP_BUY,GetLots(),Ask,飞点,Ask-止损*Point,Ask+止盈*Point,"",0,CLR_NONE,Red);
		} 
	}        
	int total = OrdersTotal();
	for(int i=total-1;i>=0;i--)
	{
		OrderSelect(i, SELECT_BY_POS);
		int type    = OrderType();
		bool result = false;  
		switch(type)
		{
			case OP_BUY  : if( OrderProfit() >= (获利*GetLots())) result = OrderClose( OrderTicket(), OrderLots(), MarketInfo(OrderSymbol(), MODE_BID), 5, Red );
				break;
			case OP_SELL : if( OrderProfit() >= (获利*GetLots())) result = OrderClose( OrderTicket(), OrderLots(), MarketInfo(OrderSymbol(), MODE_ASK), 5, Red );
				break;
		}
		if(result == false)
		{
			Sleep(3);
		}
	}     
	return(0); 
}  

//------------------------资金管理程序-----------------------------------------------------------+
double GetLots() {
	return (NormalizeDouble(AccountFreeMargin()/美元,1));  
} 
//------------------------全部程序结束-----------------------------------------------------------+