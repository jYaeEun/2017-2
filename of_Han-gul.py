'''UTF8 한글 초성만 추출, 자소 단위로 분리/결합
1.한글 초성만 출력
2.한글 초성/중성/종성을 자소단위로 분리하여 출력
3.자소 단위로 분리한 파일을 입력으로 하여 음절 단위로 조합하여 출력

example)이 입력은 한글입니다.
->1.ㅇㅇㄹㅇㅎㄱㅇㄴㄷ ->2.ㅇㅣ ㅇㅣㅂㄹㅕㄱㅇㅡㄴ ㅎㅏㄴㄱㅡㄹㅇㅣㅂㄴㅣㄷㅏ. ->3.이 입력은 한글입니다.'''

import math
import os
import sys
import codecs
import binascii

f=[] #input.txt내용을 받아오는 리스트
a=[] #특수문자를 제외한 오직 한글만을 저장하는 리스트
b=[] #utf-8에서 유니코드로 변환하기 위해 필요한 리스트
c=[] #변환한 유니코드를 저장
a2 = [] #특수문자를 저장
a3 = [] #특수문자의 위치를 저장

#input.txt파일을 엽니다.
f=open(os.getcwd()+'\input.txt',mode = 'r').read().encode('utf-8')

'''1번'''
for i in range(0,len(f)):
            if(f[i]>127):                   #오직 한글만 a에 저장합니다.
                a.append((bin(f[i])))
            else:
                a2.append(f[i])             #특수문자를 a2에 저장합니다.
                a3.append(i)                #특수문자의 index를 a3에 저장합니다.

for i in range(0,len(a)):
            if i % 3  == 0 :
                a[i]=a[i].replace('0b1110','')  
            else:
                a[i]=a[i].replace('0b10','')       #utf-8방식으로 저장된 값에서 유니코드로 변환하기 위해 필요한 부분만을 replace함수를 이용하여 남기고 나머지는 없애줍니다. (4비트 -6비트 -6비트 씩만을 남깁니다.) 

for i in range(0,len(a)):        
            if i%3 == 2:
                b.append(a[i-2] + a[i-1] + a[i])   #유니코드로 바꾸기 위해 값들을 3개씩 묶어줍니다. (ex) a[0] = 1000 ,a[1] = 100000, a[2] = 100000 형식이므로 3개씩 묶어서 한값당 총 16비트로 만듭니다.)
for i in range(0,len(b)):
                c.append("%X" % int(b[i],2))       #유니코드로 변환 (ex) 1100011101110100 -> c774), 이 값들을 c에다가 저장해줍니다.      


cho_base=['ㄱ','ㄲ','ㄴ','ㄷ','ㄸ','ㄹ','ㅁ','ㅂ','ㅃ','ㅅ','ㅆ','ㅇ','ㅈ','ㅉ','ㅊ','ㅋ','ㅌ','ㅍ','ㅎ']
jung_base=['ㅏ','ㅐ','ㅑ','ㅒ','ㅓ','ㅔ','ㅕ','ㅖ','ㅗ','ㅘ','ㅙ','ㅚ','ㅛ','ㅜ','ㅝ','ㅞ','ㅟ','ㅠ','ㅡ','ㅢ','ㅣ']
jong_base=['','ㄱ','ㄲ','ㄳ','ㄴ','ㄵ','ㄶ','ㄷ','ㄹ','ㄺ','ㄻ','ㄼ','ㄽ','ㄾ','ㄿ','ㅀ','ㅁ','ㅂ','ㅄ','ㅅ','ㅆ','ㅇ','ㅈ','ㅊ','ㅋ','ㅌ','ㅍ','ㅎ']
#초성만을 출력합니다.
for i in range(0,len(c)):
                x = ((int(c[i],16)-int('AC00',16))//(28*21))%19
                print(cho_base[x],end='')
print()
"""2번"""
print_to=[] #2번에서 출력되는 값을 리스트로 저장해서 3번의 입력값으로 넣어주기 위해 사용되는 리스트입니다. 

#아까 제외 시켰던 특수문자들을 다시 c에다가 한글과 함께 저장해줍니다. 
for i in range(0,len(a2)):
                c.insert(a3[i]//3+i,a2[i])
#초성,중성,종성을 분리하기위한 프로그램입니다.
for j in range(0,len(c)):                               
        if type(c[j]) == str:                           #만약 리스트의 값이 한글이면 초성,중성,종성을 따로 출력해줍니다.
                        x = ((int(c[j],16)-int('AC00',16))//(28*21))%19
                        print(cho_base[x],end='')
                        print_to.append(x)
                        y = ((int(c[j],16)-int('AC00',16))//(28))%21
                        print(jung_base[y],end='')
                        print_to.append(y)
                        z = ((int(c[j],16)-int('AC00',16))%(28))
                        print(jong_base[z],end='')
                        print_to.append(z)
        else:                                           #만약 리스트의 값이 특수문자이면 그 특수문자 그대로 출력해줍니다.
            print(chr(c[j]),end='')
"""3번"""
print()
print_final=[]  #분리되어 들어온 초성,중성,종성을 다시 합치기 위해 사용되는 리스트입니다.

for i in range(0,len(print_to)):        
            if i%3 == 2:
                print_final.append(chr(((print_to[i-2] * 21)+print_to[i-1])*28+print_to[i]+0xAC00))  #한글의 초성,중성,종성을 합친 값을 chr함수를 이용하여 원래 문자로 바꾸어 줍니다.
                                                                                                     #(지금은 특수문자를 제외한 한글의 초성,중성,종성만이 리스트에 저장되어 있습니다.)
for i in range(0,len(a2)):
                print_final.insert(a3[i]//3+i,chr(a2[i]))                                            #제외시켰던 특수문자를 리스트에 넣어줍니다.

for each_item in print_final:
                print(each_item,end='')                                                              #리스트의 각 값들을 출력합니다.


                                
                




