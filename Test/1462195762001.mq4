//+----------------------------------------------------------------------------------------------+
//|��EA�����Զ����㿪�����Զ�����ƽ�֣��󲿷����ݶ��Ѿ��������������ݼ����ˣ��ǳ�����ʵ�á�    +
//|��������Ѿ��߱��ʽ����˫ֹӯ����ֹ��ʱ����ơ��������ơ�ӯ���Զ����ӿ��ơ������ƽ�֡�  +
//|������������ӯ�����ܣ���������������Ч��    �����ˣ�����   QQ:389911138  �绰��13325074595  +
//|ʹ��˵������ea���ڹ̶����ƽ̨��ã������1�ĸ��ã��ڲ�������Ƚ��ȶ���ʱ������ӯ���ܺõģ�   +
//|��Ԫ��������ʽ�������������ǻ��㣬��ʼ����ʱ�俪ʼ���ʹܾ����ʽ����ٶ��پͲ������ˣ�������  +
//|û��ʹ��ֹӯ�����˸��Ƚ���ֹӯ������á����ʹ��һ����ģ����ʵ�̣����������ԭ�����ʵ�̣�    +
//|ʵ���з��գ�Ͷ����������������ȿ����ֻ�������ʵ�̣���Ҫ��!                                 +
//+----------------------------------------------------------------------------------------------+
extern double    ��Ԫ = 2000;
extern double    ֹ�� = 6;
extern double    ֹӯ = 888;
extern double    ��ʼ = 0;
extern double    ���� = 24;
extern double    ���� = 3;
extern double    �ɵ� = 2;
extern    int    ���� = 10.0;
extern    int    �ʹ� = 150;
extern double    A, B; 
//-----------------------EA������----------------------------------------------------------------+
int start()
{
	A=Ask;//�������Askû�����Գ�ʼ������ֵ��Ϊ�κ�ֵ��
	B=Bid; 
	if(AccountBalance()>�ʹ�&&TimeHour(TimeCurrent())>=��ʼ&&TimeHour(TimeCurrent())<����&&��ʼ<����)
	{   
		if (Ask-A>=����*Point) 
		{
			OrderSend(Symbol(),OP_SELL,GetLots(),Bid,�ɵ�,Bid+ֹ��*Point,Bid-ֹӯ*Point,"",0,CLR_NONE,Green);
		} 
		if (B-Bid>=����*Point) 
		{
			OrderSend(Symbol(),OP_BUY,GetLots(),Ask,�ɵ�,Ask-ֹ��*Point,Ask+ֹӯ*Point,"",0,CLR_NONE,Red);
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
			case OP_BUY  : if( OrderProfit() >= (����*GetLots())) result = OrderClose( OrderTicket(), OrderLots(), MarketInfo(OrderSymbol(), MODE_BID), 5, Red );
				break;
			case OP_SELL : if( OrderProfit() >= (����*GetLots())) result = OrderClose( OrderTicket(), OrderLots(), MarketInfo(OrderSymbol(), MODE_ASK), 5, Red );
				break;
		}
		if(result == false)
		{
			Sleep(3);
		}
	}     
	return(0); 
}  

//------------------------�ʽ�������-----------------------------------------------------------+
double GetLots() {
	return (NormalizeDouble(AccountFreeMargin()/��Ԫ,1));  
} 
//------------------------ȫ���������-----------------------------------------------------------+