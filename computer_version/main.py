def find_common(root, n1, n2):
  """
  寻找公共节点
  """
  if root.left:
    v = find_common(root.left, n1, n2)
    if v:
      return v
  if root.right:
    v = find_common(root.right, n1, n2)
    if v:
      return v
    
  


def create_tree():
  pass