#  找到最短包含所有字符的子串

def find_shorted_sub_string(target, dst):
  m = dict()
  for c in dst:
    if c not in m:
      m[c] = True
  for window_size in range(len(m), len(target)+1):
    window_m = dict()
    for l in range(window_size):
      c = target[l]
      if c in m:
        window_m[c] = window_m.get(c, 0)+1
    # print("window_m", window_m)
    start = 0
    while(True):
      # print("start: %s, window_m: %s, subtr: %s" % (start, window_m, target[start:start+window_size]))
      if len(window_m) == len(m):
        return target[start:start+window_size]
        
      start+=1
      end = start + window_size -1
      if end >= len(target):
          break
      todel = target[start-1]
      toadd = target[end]
      if todel in m:
        window_m[todel]-=1
        if(window_m[todel] == 0):
          window_m.pop(todel)
      if toadd in m:
        window_m[toadd] = window_m.get(toadd, 0)+1
  return ""


      
      


def main():
  target = "abcdedaabbdhgwere"
  dst = "dbwr"


  v = find_shorted_sub_string(target, dst)
  print(v)

main()