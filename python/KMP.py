def KMPSearch(pat, txt):
    M = len(txt)
    N = len(pat)
    lps = lps_arr(pat, N)
  
    initial_point = []
    i=0
    j=0
  
    while i!= M:

        if txt[i] == pat[j]:
            i+=1
            j+=1
        else:
            j=lps[j-1]
       
        if j==N:
            initial_point.append(i-j)
            print('found at index number',i-j)
            j= lps[j-1]
        elif j==0:
            i+= 1

def lps_arr(pat, b):
    lps = [0]*b
    n=0
    m=1
    while m != b:
        if pat[m] == pat[n]:
            n += 1
            lps[m] = n
            m += 1
        elif n != 0:
                n = lps[n-1]
        else:
            lps[m] = 0
            m += 1
    return lps


string = input("string :")
pat = input("pattern :")
KMPSearch(pat, string)