#!/usr/bin/env python3
#-*-coding:utf-8-*-

import csv


def parse(csv_data):

	l_csv_data = list(csv_data)
	parse_result = []

	i = 1
	while i< len(l_csv_data):
		
		start_date = l_csv_data[i][0]
		end_date = l_csv_data[i][7]
		
		j = i
		sum_profit = 0
		while j< len(l_csv_data) and l_csv_data[j][0] <= end_date:
			sum_profit += float(l_csv_data[j][11])
			j += 1
		parse_result.append([start_date, end_date, sum_profit])
		
		i = j
	
	return parse_result

if __name__ == '__main__':

	f = csv.reader(open('977940.history.csv','r'))
	result = parse(f)
	for line in sorted(result, key=lambda item: item[2]):
		print(line)
	
	