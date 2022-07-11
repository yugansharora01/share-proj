#from stocksymbol import StockSymbol
import requests
import json

_UNAUTHORIZED_ = 401
_NOT_FOUND_ = 404
_INVALID_KEY_ = 'Invalid API Key'
_SERVER_ERROR_ = 'Something is wrong. Please contact the creator'

def get_symbols_list(market=None):
    headers = {'x-api-key': 'e35c7b99-dd47-4278-b7b2-bfa52e700943'}
    try:
      params = {'market': market}
      r = requests.get('https://stock-symbol.herokuapp.com/api/symbols', params=params, headers=headers)
      
      if r.status_code == _UNAUTHORIZED_:
        raise ValueError(_INVALID_KEY_)
      if r.status_code == _NOT_FOUND_:
        raise ValueError(r.json()['error'])
      data = r.json()
      return data
    except ValueError:
      raise
    except:
      raise Exception(_SERVER_ERROR_)

symbol_data_us = get_symbols_list(market = "US")

with open('src/Assets/symbols/USData.json', 'w') as f:
    json.dump(symbol_data_us, f)


symbol_data_in = get_symbols_list(market = "INDIA")

with open('src/Assets/symbols/INDIAData.json', 'w') as f:
    json.dump(symbol_data_in, f)
