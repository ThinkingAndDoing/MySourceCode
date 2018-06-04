//+------------------------------------------------------------------+
//| SampleEA.mq4                                                     |
//| Copyright ?2008, MetaQuotes Software Corp.                       |
//| QQ:XXX                                                           |
//+------------------------------------------------------------------+
#property link  XXX
//---- input parameters
extern   double TakeProfit = 20; //止盈
extern   double StopLoss = 30; //止损
extern   double Lots = 2; //手数
extern   double TrailingStop = 50;
extern   int ShortEma = 5;
extern   int LongEma = 60;

//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init() 
{
    //----

    //----
    return (0);
}
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit() 
{
    //----

    //----
    return (0);
}

//+------------------------------------------------------------------+
//| expert start function                                            |
//+------------------------------------------------------------------+
int start() 
{
	int cnt, ticket, total;
	double SEma, LEma;
//----
	if (Bars < 100) 
	{
		Print("bars less than 100");
		return (0);
	}

	if (TakeProfit < 10) 
	{
		Print("TakeProfit less than 10");
		return (0); // check TakeProfit
	}

	SEma = iMA(NULL, 0, ShortEma, 0, MODE_EMA, PRICE_CLOSE, 0);
	LEma = iMA(NULL, 0, LongEma, 0, MODE_EMA, PRICE_CLOSE, 0);

	static int isCrossed = 0;
	isCrossed = Crossed(LEma, SEma);

	total = OrdersTotal();
	if (total < 1) 
	{
		if (isCrossed == 1) // 满足空仓条件，开空仓
		{
			ticket = OrderSend(Symbol(), OP_SELL, Lots, Bid, 3, Bid + StopLoss * Point,
                Bid - TakeProfit * Point, "EMA_CROSS", 12345, 0, Green);
			if (ticket > 0) 
			{
				if (OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
					Print("SELL order opened : ", OrderOpenPrice());
			} else Print("Error opening SELL order : ", GetLastError());
			return (0);
		}
		if (isCrossed == 2) // 满足多仓条件，开多仓
		{
			ticket = OrderSend(Symbol(), OP_BUY, Lots, Ask, 3, Ask - StopLoss * Point,
                Ask + TakeProfit * Point, "EMA_CROSS", 12345, 0, Red);
			if (ticket > 0) 
			{
				if (OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
					Print("BUY order opened : ", OrderOpenPrice());
				} else Print("Error opening BUY order : ", GetLastError());
				return (0);
			}
			return (0);
		}
//---- 订单修改，实现动态止盈止损跟踪
		for (cnt = 0; cnt < total; cnt++) 
		{
			OrderSelect(cnt, SELECT_BY_POS, MODE_TRADES);
			if (OrderType() <= OP_SELL && OrderSymbol() == Symbol()) 
			{
				if (OrderType() == OP_SELL) // long position is opened
				{
// check for trailing stop
					if (TrailingStop > 0) 
					{
						if (Bid - OrderOpenPrice() > Point * TrailingStop) 
						{
							if (OrderStopLoss() < Bid - Point * TrailingStop) 
							{
								OrderModify(OrderTicket(), OrderOpenPrice(),
									Bid - Point * TrailingStop,
									OrderTakeProfit(), 0, Green);
								return (0);
							}
						}
					}
				} else // go to short position
				{
// check for trailing stop
					if (TrailingStop > 0) 
					{
						if ((OrderOpenPrice() - Ask) > (Point * TrailingStop)) 
						{
							if ((OrderStopLoss() > (Ask + Point * TrailingStop))) 
							{
								OrderModify(OrderTicket(), OrderOpenPrice(),
									Ask + Point * TrailingStop,
									OrderTakeProfit(), 0, Red);
								return (0);
							}
						}
					}
				}
			}
		}
	}
	return (0);
}
//+------------------------------------------------------------------+
// 移动平均线多空条件判断，
//+------------------------------------------------------------------+
int Crossed(double line1, double line2) 
{
	static int last_direction = 0;
	static int current_direction = 0;
//Don't work in the first load, wait for the first cross!
	static bool first_time = true;
	if (first_time == true) 
	{
		first_time = false;
		return (0);
	}

	if (line1 > line2)
		current_direction = 2; //up 多头市场 上穿做多
	if (line1 < line2)
		current_direction = 1; //down 空头市场 下穿做空

	if (current_direction != last_direction) //changed 多空改变 
	{
		last_direction = current_direction;
		return (last_direction);
	}
	else return (0); //not changed
}

