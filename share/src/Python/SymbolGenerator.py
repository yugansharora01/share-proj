from stocksymbol import StockSymbol

api_key = 'e35c7b99-dd47-4278-b7b2-bfa52e700943'
ss = StockSymbol(api_key)

symbol_list_us = ss.get_symbol_list(market="US")

f = open("../Assets/symbols/US_symbols.txt", "a")
for item in symbol_list_us:
    f.write("%s\n" % item)
    
symbol_list_in = ss.get_symbol_list(market="INDIA")

f = open("../Assets/symbols/INDIA_symbols.txt", "a")
for item in symbol_list_in:
    f.write("%s\n" % item)