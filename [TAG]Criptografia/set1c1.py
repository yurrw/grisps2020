#!/usr/bin/env python3.6
import base64
import textwrap
'''
https://cryptopals.com/sets/1/challenges/1
hex -> base64
hex: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
output : SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
'''
def validator(output):
    b64string = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
    if str(output) == b64string :
        print("FFrom hex to b64 with success!")
    else:
        print("Failed!")
    print(output)

    return None

B64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# decode base64
def b64encode(bin_str):
    ttt = textwrap.wrap(bin_str, 6)
    print("tttt")
    print(ttt)

    #fixing last house
    if len(ttt[len(ttt) -1]) == 2:
        if '1' in ttt[len(ttt) -1]:
            ttt[len(ttt) -1] += "0000=="
        else:
            ttt[len(ttt) -1] += "=="
    elif  len(ttt[len(ttt) -1]) == 4: 
        if '1' in ttt[len(ttt) -1]:
            ttt[len(ttt) -1] += "00="
        else:
            ttt[len(ttt) -1] += "="

    ans = ""
    for i in ttt:
        if not "=" in i :
            ans += B64[int(i,2)]
        else:
            i2  = i
            tmp = i2.replace('=', '')
            ans += B64[int(tmp,2)]


    print(ans)
    return None


def hex2bin(hex_str):
    int_ = int(hex_str,16)
    print(int_)
    # Code to convert hex to binary 
    bin_str = ''
    # while int_ > 0: 
    #     bin_str = str(int_ % 2) + bin_str
    #     int_ = int_ >> 1
    bin_str = str(bin(int_))
    b64encode(bin_str) 
  


def call():
    hex2bin("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")